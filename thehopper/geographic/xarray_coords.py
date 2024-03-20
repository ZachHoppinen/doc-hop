import numpy as np

def reproject_to_1d(da):
    xout = np.linspace(np.min(da.x), np.max(da.x), da.shape[0])
    yout = np.linspace(np.min(da.y), np.max(da.y), da.shape[1])

    xm,ym = np.meshgrid(xout,yout)
    zo = griddata((da.x.values.ravel(),da.y.values.ravel()),da.values.ravel(), (xm, ym), 'nearest')

    da_new = xr.DataArray(zo, coords = {'y': yout, 'x' : xout})
    return da_new
