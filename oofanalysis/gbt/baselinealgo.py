# Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
#
# Initial version May 2008
#
# Back to baseline removal algorithms.
#
# No I/O, visualisation code in this file -- just the algorihtms

import numpy

def circleCut(dx, dy, cx, cy, rad):
    return ((dx-cx)**2+ (dy-cy)**2)< rad**2

def circleMask(cx, cy, rad):
    """
    Returns a function which takes (dx,dy) and returns mask of points
    lying within the circle radious rad and centre cx,cy
    """
    return lambda dx, dy : circleCut(dx,dy, cx,cy,rad)


def rmBase(dx, dy,
           fnu,
           maskfn):
    """
    Remove baseline from signal fnu.

    :param maskfn: function that thakes(dx,dy) and defines which
    points have real signal (True) or just noise (False).

    :return:
    
    """

    mask=maskfn(dx,dy)

    return fnu, mask

