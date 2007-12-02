# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# Initial version November 2007
#
# Plot structure funcitons of generated turbulence

import numarray
import pdb

from setup import *

import pyxplot

import pybnlib
import kolmogorovutils


def PlotSFN(r,
            fnameout,
            fid,
            **kwargs):

    mask = numarray.logical_and( r[:,1] > 0,
                                 r[:,2] > 0)
    xvals= r[:,0]
    yvals= (r[:,1])[mask]/(r[:,2])[mask]

    m2= (xvals > 0)
    yfid= 6.88* (xvals[m2]/float(fid))**(2.0/3)

    pyxplot.vect( [xvals[mask], xvals[m2] ],
                  [yvals, yfid      ],
                  fnameout,
                  xax=pyxplot.axis(r"$d$", type="log"),
                  yax=pyxplot.axis(r"$D(d)$", type="log", xmax=12),
                  multi=True)
                  
def AccumPlot(N,
              naccum,
              fnameout,
              opt=pybnlib.KInitialEFB,
              nsamples=10,
              **kwargs):

    def Sample(N,i):
        c=kolmogorovutils.GenerateKolmogorov3D(N,N,N,
                                               i,
                                               opt=opt)
        return kolmogorovutils.RandomCubeSFN(c,
                                             nsamples , int(N*1.4))

    r=Sample(N,0)

    for i in range(1,naccum):
        r+=Sample(N,i)

    r[:,0] /= naccum
    PlotSFN(r,
            fnameout,
            N,
            **kwargs)

def TestPlots():

    if 0:
        AccumPlot( 33, 1000, "temp/c33normal.eps")
        AccumPlot( 33, 1000, "temp/c33balanced.eps", opt=pybnlib.KInitialEFB + pybnlib.KBalancedIters)

    if 0:
        AccumPlot( 33, 1000, "temp/c33Bfaceedge.eps",
                   opt=pybnlib.KInitialEFB + pybnlib.KBalancedIters+ pybnlib.KEdgeBalanced)

    if 1:
        AccumPlot(129, 500,
                  "temp/n129_e50.eps",
                  opt=pybnlib.KInitialEFB + pybnlib.KBalancedIters+ pybnlib.KEdgeBalanced,
                  nsamples=1)
