import requests
import urllib
import pandas as pd
from geopy.distance import geodesic

import math

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
