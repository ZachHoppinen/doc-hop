import numpy as np
import pandas as pd
import datetime
import matplotlib.pyplot as plt
import xarray as xr
import rioxarray as rxr
import pystac_client
import planetary_computer
import geopandas as gpd
from shapely.geometry import shape
import odc.stac
import rioxarray as rxr
from rioxarray.merge import merge_arrays
import rasterio as rio

def weights_inc(inc, k = 0.5):
    if inc < 20: return 1.0
    elif inc > 45: return k
    else: return k * (1  + (45 - inc) / (45 - 20))

def ufunc_weights(inc, k = 0.5):
    return xr.apply_ufunc(weights_inc, inc)

def compute_cr(ds_orbit):
    orbit = ds_orbit.relative_orbit.values[0]  # group is all one orbit
    vv_ratio = ds_orbit['vv'] / ds_orbit[f'{orbit}_vv_ref']
    vh_ratio = ds_orbit['vh'] / ds_orbit[f'{orbit}_vh_ref']
    w = ds_orbit['weights'].sel(orbit=orbit)
    cr = w * vh_ratio + (1 - w) * vv_ratio
    # convert to db
    return 10*np.log10(cr)

def make_orbit_mask(ds_orbit):
    """Make layover+shadow mask for one orbit group."""
    orbit = ds_orbit.relative_orbit.values[0]
    
    # Grab the 2D incidence array for this orbit
    inc_2d = snowon_s1_ds['inc'].sel(orbit=orbit)
    
    # Boolean mask: layover > 75 OR shadow < 15
    mask_2d = (inc_2d > 75) | (inc_2d < 15)
    
    # Expand to have time dimension (all timesteps same mask)
    mask_3d = mask_2d.broadcast_like(ds_orbit['vv'])
    
    return xr.DataArray(
        mask_3d,
        dims=ds_orbit['vv'].dims,
        coords=ds_orbit['vv'].coords
    )

def season_mask(time, season):
    """
    Create a boolean mask for a month-day season.

    Parameters
    ----------
    time : xr.DataArray or pandas.DatetimeIndex
    season : ((int, int), (int, int))

    Returns
    -------
    xr.DataArray[bool]
    """
    start, end = season

    md = time.dt.month * 100 + time.dt.day
    start_md = start[0] * 100 + start[1]
    end_md   = end[0] * 100 + end[1]

    if start_md <= end_md:
        return (md >= start_md) & (md <= end_md)
    else:
        return (md >= start_md) | (md <= end_md)
