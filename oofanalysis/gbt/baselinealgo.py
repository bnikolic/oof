# Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
#
# Initial version May 2008
#
# Back to baseline removal algorithms...
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


def baseEndPts(mask):
    """Compute the endpoints of each baseline by calculating where the
    mask changes
    """
    # Where does the mask change from True to False and vv?
    chng=numpy.logical_xor(mask[1:], mask[:-1])
    # Indices of points where change occurs     
    chindex=chng.nonzero()[0]
    # Pair 'em up 
    chindex.shape=(len(chindex)/2,2)
    return chindex

def rmBaseSegment(fnu,
                  il, ih,
                  delta=4):
    """Remove baseline segment between indices il and ih using delta
    points to estimate the baseline endpoint values
    """
    fl = fnu[il-delta:il].mean()
    cil= il - delta/2

    fh = fnu[ih:ih+delta].mean()
    cih= ih + delta/2

    baseln = fl+ (fh-fl)/float(cih-cil)*  numpy.arange(cih-cil)

    res = numpy.array(fnu)
    res[cil:cih] -=  baseln

    return res

    
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

    for (il,ih) in baseEndPts(mask):
        fnu=rmBaseSegment(fnu,
                          il,ih)

    return fnu, mask

