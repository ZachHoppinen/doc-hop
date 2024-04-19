# Functions to open and read gamma binary files

def dem_to_np(fp):
    with open(clean_suffixes(fp).with_suffix('.diff_par'), 'r') as f:
        lns = f.readlines()
    par = {l.split()[0]:l.split()[1] for l in lns if len(l.split()) == 2}
    arr = np.fromfile(fp, '>f4').reshape(int(par['az_samp_1:']), int(par['range_samp_1:']))
    return arr

def cor_to_np(fp, par_fp):
    if not par_fp:
        with open(clean_suffixes(fp).with_suffix('.diff_par'), 'r') as f:
            lns = f.readlines()
    else:
        with open(par_fp, 'r') as f:
            lns = f.readlines()
    par = {l.split()[0]:l.split()[1] for l in lns if len(l.split()) == 2}
    par = dict({(k, float(v)) for k,v in par.items()})
    arr = np.fromfile(fp, '>f4').reshape(int(par['interferogram_azimuth_lines:']), int(par['interferogram_width:']))
    return arr

import numpy as np
import xarray as xr
import contextlib

def parse_par(par_fp):
    with open(par_fp, 'r') as f:
        lns = f.readlines()
    par = {l.split()[0].strip(':'):l.split()[1] for l in lns if len(l) > 2}

    for k, v in par.items():
        try: par[k] = float(v)
        except: par[k] = v
    return par

def get_width(par):
    cols = [k for k in par.keys() if ('range_samp' in k) or ('width' in k)]
    width = par[cols[0]]
    return width

def gamma_to_numpy(fp, par_fp):
    par = parse_par(par_fp)
    width = get_width(par)
    arr = np.fromfile(fp, '>f4').reshape(-1, int(width))

    return arr, par

def gamma_to_xarray(fp, par_fp):
    arr, par = gamma_to_numpy(fp, par_fp)
    dx, dy = par['post_lon'], par['post_lat']
    xs = np.linspace(par['corner_lon'], par['corner_lon'] + dx* arr.shape[1], arr.shape[1])
    ys = np.linspace(par['corner_lat'], par['corner_lat'] + dy* arr.shape[0], arr.shape[0])
    da = xr.DataArray(arr, dims = {'x', 'y'}, coords = {'y': ys, 'x': xs})
    return da.where((da > 0) & (da < 1)).dropna('x', how = 'all').dropna('y', how = 'all')
