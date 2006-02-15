# Bojan Nikolic
# $Id: ruzeverify.py,v 1.1 2006/02/15 22:06:15 bnikolic Exp $
#
# Analyse Ruze officiency data

import math

import pyfits
import pyxplot


def GetData(fname):

    "return the horizontal position and fnu vectors"

    din=pyfits.open(fname)[1].data

    # have azimuth position in arcminutes...
    dx = din.field("dx") * 180 * 60 / math.pi
    # Make the fnu zero mean (only makes sense for diffd data)
    fnu = din.field("fnu")
    fnu -= fnu.mean()

    return dx, fnu

def PlotF( fnamelist,
           fnameout="plots/ruze.eps"):

    xvv, yvv = [] , []

    for fname in fnamelist:
        data=GetData(fname)
        xvv.append( data[0]  )
        yvv.append( data[1]  )
        print data[1].max() , data[1].min()


    pyxplot.vect( xvv,
                  yvv,
                  fnameout,
                  xax=pyxplot.axis("Azimuth Offset (arcmin)",
                                   xmin=-2, xmax=1),
                  yax=pyxplot.axis("Antenna T / Cal T"),
                  multi=1,
                  width=pyxplot.THESIS)

fl = [ "cdata/TPTCSOOF_050324/s%i-l.fits" % x for x in [ 90, 95, 100]]

                  
    
