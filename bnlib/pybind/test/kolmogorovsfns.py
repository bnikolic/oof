# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# Initial version November 2007
#
# Plot structure funcitons of generated turbulence

import numarray

from setup import *

import pyxplot

import pybnlib
import kolmogorovutils


def PlotSFN(r,
            fnameout,
            fid):

    mask = numarray.logical_and( r[:,0] > 0,
                                 r[:,1] > 0)
    xvals= numarray.arange(len(r))
    yvals= (r[:,0])[mask]/(r[:,1])[mask]

    m2= (xvals > 0)
    yfid= 6.88* (xvals[m2]/float(fid))**(2.0/3)

    pyxplot.vect( [xvals[mask], xvals[m2] ],
                  [yvals, yfid      ],
                  fnameout,
                  xax=pyxplot.axis(r"$d$", type="log"),
                  yax=pyxplot.axis(r"$D(d)$", type="log"),
                  multi=True)
                  
def AccumPlot(N,
              naccum,
              fnameout,
              opt=pybnlib.KInitialEFB):

    def Sample(N,i):
        c=kolmogorovutils.GenerateKolmogorov3D(N,N,N,
                                               i,
                                               opt=opt)
        return kolmogorovutils.RandomCubeSFN(c,
                                             10 , int(N*1.4))

    r=Sample(N,0)

    for i in range(1,naccum):
        r+=Sample(N,i)

    PlotSFN(r,
            fnameout,
            N)
