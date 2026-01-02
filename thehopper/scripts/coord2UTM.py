#! /Users/zmhoppinen/miniforge3/envs/nga/bin/python

import sys
from pyproj import CRS, Transformer

def latlon_to_zone(lat, lon):
    """Return UTM zone number and hemisphere from lat/lon."""
    zone_number = int((lon + 180) / 6) + 1
    hemisphere = "north" if lat >= 0 else "south"
    return zone_number, hemisphere

def main():
    args = sys.argv[1:]

    if len(args) == 2:
        # WGS84 (lat, lon) → UTM (easting, northing, zone, hemisphere)
        try:
            lat, lon = map(float, args)
        except ValueError:
            print("Latitude and longitude must be numbers")
            sys.exit(1)

        zone, hemi = latlon_to_zone(lat, lon)

        # Define CRS
        crs_wgs84 = CRS.from_epsg(4326)
        crs_utm = CRS.from_proj4(
            f"+proj=utm +zone={zone} +{'north' if hemi == 'north' else 'south'} +ellps=WGS84 +datum=WGS84 +units=m +no_defs"
        )

        transformer = Transformer.from_crs(crs_wgs84, crs_utm, always_xy=True)
        easting, northing = transformer.transform(lon, lat)

        print(f"Input: Latitude={lat}, Longitude={lon}")
        print(f"UTM Zone: {zone} Hemisphere: {hemi}")
        print(f"Easting: {easting:.3f}, Northing: {northing:.3f}")

    elif len(args) == 4:
        # UTM → WGS84
        try:
            easting, northing = map(float, args[:2])
            zone = int(args[2])
            hemi = args[3].lower()
        except ValueError:
            print("Usage: coord2UTM.py <easting> <northing> <zone> <north|south>")
            sys.exit(1)

        # Define CRS
        crs_utm = CRS.from_proj4(
            f"+proj=utm +zone={zone} +{'north' if hemi == 'north' else 'south'} +ellps=WGS84 +datum=WGS84 +units=m +no_defs"
        )
        crs_wgs84 = CRS.from_epsg(4326)

        transformer = Transformer.from_crs(crs_utm, crs_wgs84, always_xy=True)
        lon, lat = transformer.transform(easting, northing)

        print(f"Input: Easting={easting}, Northing={northing}, Zone={zone}, Hemisphere={hemi}")
        print(f"Latitude: {lat:.6f}, Longitude: {lon:.6f}")

    else:
        print("Usage:")
        print("  coord2UTM.py <lat> <lon>")
        print("  coord2UTM.py <easting> <northing> <zone> <north|south>")
        sys.exit(1)


if __name__ == "__main__":
    main()

