#!/Users/zmhoppinen/miniforge3/envs/science/bin/python

import sys
from shapely.geometry import Point

def main():
    if len(sys.argv) != 3:
        print("Usage: coord2wkt.py <lat> <lon>")
        sys.exit(1)

    try:
        lat = float(sys.argv[1])
        lon = float(sys.argv[2])
    except ValueError:
        print("Latitude and longitude must be numbers")
        sys.exit(1)

    # Create a WGS84 Point (order: lon, lat)
    point = Point(lon, lat)

    print(point.wkt)

if __name__ == "__main__":
    main()

