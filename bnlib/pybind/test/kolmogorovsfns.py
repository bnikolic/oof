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
            fid=129):

    mask = r[:,0] > 0
    xvals= numarray.arange(len(r))
    yvals= r[:,0]/r[:,1]

    m2= (xvals > 0)
    yfid= 6.88* (xvals[m2]/129.0)**(2.0/3)

    pyxplot.vect( [xvals[mask], xvals[m2] ],
                  [yvals[mask], yfid      ],
                  fnameout,
                  xax=pyxplot.axis(r"$d$", type="log"),
                  yax=pyxplot.axis(r"$D(d)$", type="log"),
                  multi=True)
                  
