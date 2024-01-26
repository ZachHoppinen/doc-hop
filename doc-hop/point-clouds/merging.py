# need to add cl_call from file-parsing
from os.path import join, isdir

def mosaic_laz(in_dir, las_extra_byte_format, log, out_fp = 'unaligned_merged.laz', laz_prefix = ''):
    """
    Generates and run PDAL mosaic command.

    Parameters:
    in_dir (str): fp to directory full of .laz files to mosaic
    out_fp (str) [optional]: out filepath to save [default: ./merge.laz]
    laz_prefix (str) [optional]: prefix to append in case there are .laz files 
    to avoid mosaicing [default: ""]
    Returns:
    mosaic_fp (str): filepath to mosaic output file
    """
    assert isdir(in_dir), f'{in_dir} is not a directory'
    # generate searching command
    if las_extra_byte_format is True:
        in_str = ' '.join(glob(join(in_dir, f'{laz_prefix}*.las')))
    else:
        in_str = ' '.join(glob(join(in_dir, f'{laz_prefix}*.laz')))
    # out fp to save to
    mosaic_fp = join(in_dir, out_fp)
    # set up mosaic command
    mosaic_cmd = f'pdal merge {in_str} {mosaic_fp}'
    log.debug(f"Using mosaic command: {mosaic_cmd}")
    # run mosaic command
    cl_call(mosaic_cmd, log)
    
    return mosaic_fp