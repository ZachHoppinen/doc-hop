import requests
import urllib
import pandas as pd
from geopy.distance import geodesic

import math

def DecimalDegreestoMeters(decdeg, latitude):
    return (111.32 * 1000 * np.cos(latitude * (np.pi / 180))) * decdeg
    
def MetersToDecimalDegrees(meters, latitude):
    return meters / (111.32 * 1000 * np.cos(latitude * (np.pi / 180)))

def decimal_degree_to_meters(lat1, lon1, lat2, lon2):  # generally used geo measurement function
    """
    Can be used to calculate distance in meters between two coordinates.
    https://stackoverflow.com/questions/639695/how-to-convert-latitude-or-longitude-to-meters
    """
    R = 6378.137 # Radius of earth in KM
    dLat = lat2 * math.pi / 180 - lat1 * math.pi / 180
    dLon = lon2 * math.pi / 180 - lon1 * math.pi / 180
    a = math.sin(dLat/2) * math.sin(dLat/2) + math.cos(lat1 * math.pi / 180) * math.cos(lat2 * math.pi / 180) * math.sin(dLon/2) * math.sin(dLon/2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    d = R * c
    return d * 1000; # meters

def convert_3d_to_2d(gdf):
    _drop_z = lambda geom: wkb.loads(wkb.dumps(geom, output_dimension=2))
    gdf.geometry = gdf.geometry.transform(_drop_z)


def convert_coord_decimal_to_degree(coord: float):
    """ 
    Convert decimal degree to decimal minutes
    """
    return f"{int(coord)}°{int(coord % int(coord) * 60)}'"

def convert_coord_degree_to_decimal(coord: float):
    """
    Convert decimal minutes to decimal degree
    """
    if 'n' in coord.lower(): direction = 'n'
    elif 's' in coord.lower(): direction = 's'
    elif 'e' in coord.lower(): direction = 'e'
    elif 'w' in coord.lower(): direction = 'w'
    else: direction = ''


    coord_split = coord.strip(direction).strip().split('°')
    
    if len(coord_split) == 2:
        coord = int(coord_split[0]) + float(int(coord_split[1].strip("'"))/60)
    elif len(coord_split) == 3:
        raise NotImplementedError("Can't handle decimal degree seconds")
        # coord = int(coord_split[0]) + float(int(coord_split[1].strip("'"))/60) + float(float(int(coord_split[2].strip('"'))/3600))
    else:
        raise ValueError(f"Unable to convert {coord}")
    
    if direction == 'w' or direction == 's':
        return -coord
    else:
        return coord

def resolution_to_meters(resolution_deg, ul_lat):
    """
    Calculation resolution in meters from a resolution in degrees/pixel
    """

    from geopy.distance import geodesic

    resolution_deg = float(resolution_deg)
    ul_lat = float(ul_lat)

    origin = (ul_lat, 0)  # (latitude, longitude) don't confuse
    dist = (ul_lat + 1, 0)

    ms_per_deg = geodesic(origin, dist).meters

    resolution_m = resolution_deg * ms_per_deg

    return resolution_m

def pd_add_elevation(df, lat_column: str, lon_column: str):
    """
    Query service using lat, lon. add the elevation values as a new column.
    https://gis.stackexchange.com/questions/338392/getting-elevation-for-multiple-lat-long-coordinates-in-python

    Args:
    df: pd.dataframe
    lat_column: name of column
    lon_column: name of column
    """
    url = r'https://epqs.nationalmap.gov/v1/json?'

    elevations = []
    for lat, lon in zip(df[lat_column], df[lon_column]):
                
        # define rest query params
        params = {
            'output': 'json',
            'x': lon,
            'y': lat,
            'units': 'Meters'
        }
        
        # format query string and return query value
        result = requests.get((url + urllib.parse.urlencode(params)))
        #elevations.append(result.json()['USGS_Elevation_Point_Query_Service']['Elevation_Query']['Elevation'])
        #new 2023:
        elevations.append(result.json()['value'])

    df['elev_meters'] = elevations

def triangle(x, y):
    """
    Calculate distance between two points using triangle method
    """
    return np.sqrt(x*x + y*y)

def cartesian_to_geoid(X, Y , Z ):
    """
    Convert from X, Y, Z geoid Earth Centered Earth Fixed to longitude, latitude, height
    """
    A_ELLIPSOID = 6378137.0
    F_ELLIPSOID = 1.0/298.257223560
    MU          = 3.986004418e14
    OMEGA       = np.array([0.0, 0.0, 0.0])

    DEG = np.pi/180
    EPS = 1E-8
    MAXIT = 10
    f     = F_ELLIPSOID    # WGS84
    eEarth2= (2.0*f-f*f)
    a      = A_ELLIPSOID   #(m) major semiaxis WGS84

    rb     = a*(1-f)
    # rb is only used to calculate an initial value for 'H'
    rho = np.linalg.norm([X, Y], 2)
    if rho != 0.0:
        tanPHI = Z/rho
    else:
        tanPHI = 10e20
    r = np.linalg.norm([X, Y, Z], 2)
    H = r - rb
    b = np.arcsin(Z/r)
    k = a*(1-eEarth2)
    i = 0
    b0 = 10E10
    H0 = 10E10

    while (((abs(b-b0) >= EPS)) | ((abs(H-H0) >= EPS))) & (i <= MAXIT):
        b0 = b
        H0 = H
        l = a/np.sqrt(1.0-eEarth2*np.sin(b0)**2)
        if (abs(b) < EPS):
            b = 0.0
            H = rho - a
        else:
            b = np.arctan2(tanPHI*(l+H),(1-eEarth2)*l+H0)
            H = Z/np.sin(b) - k/np.sqrt(1.0- eEarth2*np.sin(b)**2)
        i = i+1
    if i > MAXIT:
        lat = 0.0
        lon = 0.0
        H = 0.0
    else:
        lat = b
        lon = np.arctan2(Y, X)
    return np.rad2deg(lon), np.rad2deg(lat), H

import pyproj
def convert_x_y_z(lon, lat, height):
    transformer = pyproj.Transformer.from_crs("EPSG:4326", "EPSG:32611", always_xy = True)
    posx, posy, posz = transformer.transform(lon, lat, height)
