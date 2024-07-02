from pathlib import Path
import numpy as np
import pandas as pd
import geopandas as gpd
from shapely.geometry import Point, Polygon
import xarray as xr
import rioxarray as rxa
from sarxarray import complex_coherence

from uavsar_pytools.convert.tiff_conversion import read_annotation, grd_tiff_convert

import matplotlib.pyplot as plt

def generate_bound_polygon(ann):
    cs = []
    for segment in range(1, 4):
            for corner in range(1, 5):
                c = Point(reversed(ann[f'segment {segment} data approximate corner {corner}']['value'].split(', ')))
                cs.append(c)
    import math
    cent=Point(sum([p.x for p in cs])/len(cs),sum([p.y for p in cs])/len(cs))
    cs.sort(key=lambda p: math.atan2(p.y-cent.y,p.x-cent.x))
    geometry = Polygon(cs)

    return geometry

for ann_fp in data_dir.glob('*.ann'):
    ann = read_annotation(ann_fp)
    date = ann['start time of acquisition']['value']

    tracks = []
    for track in range(1,4):
        nrows, ncols = ann[f'slc_{track}_2x8 rows']['value'], ann[f'slc_{track}_2x8 columns']['value']

        llh = list(data_dir.glob(f'*_s{track}_*.llh'))
        assert len(llh) == 1
        lat, long, height = [np.fromfile(llh[0], np.float32)[i::3].reshape(nrows, ncols) for i in range(3)]

        fps = list(data_dir.glob(f'{ann_fp.stem}_s{track}*'))
        assert len(fps) == 1
        arr = np.fromfile(fps[0], dtype = np.complex64).reshape(nrows, ncols)
        da = xr.DataArray(arr, dims = ['x','y'] , coords = {'long': (['x','y'], long), 'lat': (['x','y'], lat)})
        da = da.where(np.abs(da) != 0)

        tracks.append(da)

    
    #TODO note remove slices
    combo = xr.concat(tracks, dim = 'x').isel(x = slice(0, -1, 20), y = slice(0, -1, 5))
    
    new_da = reproject_to_1d(combo).rio.write_crs('EPSG:4326')
    # this cleans up the edges from reprojecting
    new_da = new_da.rio.clip([generate_bound_polygon(ann)])

    new_da = new_da.expand_dims(time = [date]).rename({'x':'azimuth', 'y':'range'})
    break
