#!/usr/bin/env /home/ubuntu/miniconda3/envs/gsl/bin/python

from pathlib import Path

import numpy as np
import pandas as pd

import py_gamma as pg

def get_width(par_fp: Path):
    """
    get width of gamma image from par file
    """
    par = pg.ParFile(str(par_fp))
    if 'range_samples' in par.par_keys:
        width = int(par.get_dict()['range_samples'][0])
    elif 'width' in par.par_keys:
        width = int(par.get_dict()['width'][0])
    elif 'range_samp_1' in par.par_keys:
        width = int(par.get_dict()['range_samp_1'][0])
    elif 'interferogram_width' in par.par_keys:
        width = int(par.get_dict()['interferogram_width'][0])
    return width

# assign names to DEM, DEM_par, shaded relief intensity image
# dem = Path("/data/carsar/mcs/DEM/mcs.wgs.dem")
# dem_par = Path("/data/carsar/mcs/DEM/mcs.wgs.dem_par")

def make_dem_shade(dem, dem_par, overwrite = False):
    shade = dem.parent / f"{dem.name}.shd"
    dem_width = get_width(dem_par)

    par = (pg.ParFile(str(dem_par))).par_dict

    # get posting in x and y
    # for decimal degress
    if par['DEM_projection'][0] == 'EQA':
        post_x=par['post_lon'][0]
        post_y=par['post_lat'][0]
    #TODO figure out other CRSs to specifically get meters for posting from...
    else: # for meters
        post_x=3
        post_y=3

    # illumination elveation angle in degrees
    illum_theta = '-' # - for 45

    # phi0 illumination orientation angle in degrees default = 135
    phi0 = '-'

    # dem dtype (0 = float, 1 = short)
    dem_dtype = 0

    # edge protection (reduce artificats at edges and near no-data values)
    # default is no and we get core dumps in the c code if we leave this on
    edge_protection = 0

    if not shade.exists():
        pg.mapshd(dem, dem_width, post_x, post_y, illum_theta, phi0, shade, dem_dtype, 0, 1, 3, edge_protection)

def make_interferogram(slc1, slc2, dem_par, out_dir, pol = None, d1 = None, d2 = None, pol_dict = {'R1': 'H', 'R2': 'V', 'R3': 'V'}):
    if type(slc1) == str: slc1 = Path(slc1)
    if type(slc2) == str: slc2 = Path(slc2)
    if type(out_dir) == str: out_dir = Path(out_dir)

    if d1 == None: d1 = pd.to_datetime('T'.join(slc1.stem.split('_')[4:6])).strftime('%Y-%m-%dT%H-%M')
    if d2 == None: d2 = pd.to_datetime('T'.join(slc2.stem.split('_')[4:6])).strftime('%Y-%m-%dT%H-%M')
    if pol == None:
        T_pol = slc1.stem.split('_')[2]
        R_pol = pol_dict[slc1.stem.split('_')[7]]
        pol = T_pol + R_pol

    out_format = out_dir.joinpath(f'{d1}_{d2}.{pol}')
    interferogram = out_format.parent / f"{out_format.name}.int"
    coherence = out_format.parent / f"{out_format.name}.cc"
    int_par = out_format.parent / f"{out_format.name}.geo.par"

    mli_images = ['-', '-']
    # easting, northing decimation factors
    dec_fac = [1, 1]
    # easting, northing window width
    window = [7, 7]
    # window weight
    # 0 = rectangular, 1 = kaiser, 2 = circular guassian
    wind_weight = 0

    pg.SLC_intf_geo2(slc1, slc2, dem_par, interferogram, *mli_images, coherence, int_par, *dec_fac, *window, wind_weight)

    return interferogram, coherence, int_par

def make_interferogram_images(inteferogram, coherence, shade, dem_par, int_par, image_dir):
    if type(image_dir) == str: image_dir = Path(image_dir)

    dem_width = get_width(dem_par)

    # start and end at the beginning and end
    s, e = '-', '-'
    # no averaging
    ave, avn = 1, 1

    min, max = 0.1, 1
    out_fp = image_dir / f"{coherence.name}.bmp"
    kml_fp = image_dir / f"{coherence.name}.kml"
    pg.rasdt_pwr(coherence, shade, dem_width, s, e, ave, avn, min, max, 0, 'cc.cm', out_fp)
    pg.mk_kml(int_par, out_fp, kml_fp)

    out_fp = image_dir / f"{inteferogram.name}.bmp"
    kml_fp = image_dir / f"{inteferogram.name}.kml"
    # intensity display sacle factor default = 1. set to 1.5 sometimes
    scale = 1
    # intensity display exponent default = 0.35 set to 1. somethings
    dis_exp = 0.35
    pg.rasmph_pwr(inteferogram, shade, dem_width, s, e, ave, avn, 'rmg.cm', out_fp, scale, dis_exp, 24)
    pg.mk_kml(int_par, out_fp, kml_fp)


# slc1='/data/carsar/mcs/20240116/RAW/processed/SP_200MHz_H_6_20240116_233012_H_R1_1_H.slc'
# slc2='/data/carsar/mcs/20240313/RAW/processed/SP_200MHz_H_6_20240313_202546_H_R1_1_H.slc'

# out_dir = '/home/ubuntu/mcs/test'
# image_dir = '/home/ubuntu/mcs/test'

# inter, cc, int_par = make_interferogram(slc1, slc2, dem_par, out_dir)

# make_interferogram_images(inter, cc, shade, dem_par, int_par, image_dir)
