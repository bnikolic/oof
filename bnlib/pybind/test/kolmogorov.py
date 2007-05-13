# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# May 2007
#
# Testing script for Kolmogorov phase screen generation

import pybnlib

import numarray
from  matplotlib import pylab

def MarkGIter( grid,
               o,
               cntruct):

    ci=cntruct(grid.shape[0],o)

    while ci.inBounds():
        i,j=ci.getc()
        print i,j
        grid[i,j]=1
        ci.next()
    

def MarkCiter( grid,
               o):

    """
    e.g.:
    a=numarray.zeros( (9,9) ); MarkCiter(a, 2)
    pylab.matshow(a) ; pylab.show()

    """

    MarkGIter( grid, o , pybnlib.CenterIter)

def MarkEiter( grid,
               o):

    MarkGIter( grid, o , pybnlib.EdgeIter)    







