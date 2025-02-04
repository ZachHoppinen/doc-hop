import py_gamma as pg
from contextlib import redirect_stdout
import io
import re

import py3dep
from shapely.geometry import box, Polygon


class corner:
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

def get_slc_corners(par):
    f = io.StringIO()
    with redirect_stdout(f):
        pg.SLC_corners(par)
    s = f.getvalue().split('\n')

    corners = s[2:6]
    corners = [re.split('\\s+', c) for c in corners]
    corners = [corner(y = c[2], x = c[5]) for c in corners]

    return corners

def get_bbox_from_corners(corners):
    P = Polygon([[c.x, c.y] for c in corners])
    box1 = box(*P.bounds)
    return box1

corners = get_slc_corners(list(mli_dir.glob('*vv.mli.par'))[0])
box1 = get_bbox_from_corners(corners)
