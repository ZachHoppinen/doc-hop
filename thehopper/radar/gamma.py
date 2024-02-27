Functions to open and read gamma binary files

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
