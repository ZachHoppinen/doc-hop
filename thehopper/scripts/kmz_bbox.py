#! /Users/zmhoppinen/miniforge3/envs/nga/bin/python

import zipfile
import xml.etree.ElementTree as ET
import sys
from pathlib import Path

def kmz_to_bbox(kmz_path):
    kmz_path = Path(kmz_path)

    # Unzip KMZ
    with zipfile.ZipFile(kmz_path, 'r') as z:
        # Assume first KML file found
        kml_files = [f for f in z.namelist() if f.endswith('.kml')]
        if not kml_files:
            raise ValueError("No KML file found inside KMZ")
        kml_content = z.read(kml_files[0])

    # Parse KML
    root = ET.fromstring(kml_content)

    # KML namespace
    ns = {"kml": "http://www.opengis.net/kml/2.2"}

    coords = []
    for elem in root.findall(".//kml:coordinates", ns):
        text = elem.text.strip()
        for pair in text.split():
            lon, lat, *_ = map(float, pair.split(","))
            coords.append((lon, lat))

    if not coords:
        raise ValueError("No coordinates found in KML")

    # Compute bounding box
    lons, lats = zip(*coords)
    min_lon, max_lon = min(lons), max(lons)
    min_lat, max_lat = min(lats), max(lats)

    return min_lon, min_lat, max_lon, max_lat


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python kmz_bbox.py file.kmz")
        sys.exit(1)

    bbox = kmz_to_bbox(sys.argv[1])
    print("Bounding Box (min_lon, min_lat, max_lon, max_lat):")
    print(bbox)

