# Bojan Nikolic
# $Id: docuplots.py,v 1.1 2005/11/23 14:02:58 bnikolic Exp $
#
# Some plots for the documentation

import math

from setup import *


import pyfits
import numarray


from  matplotlib import pylab

dd11="/home/bnikolic/data/gbtoof/ver001/0411"

sno=114
origds=os.path.join( dd11, "s%i-l.fits" %sno )
atmods=os.path.join( dd11, "s%i-l-atmo.fits" %sno )
modatmods=os.path.join( dd11, "s%i-l-modatmo.fits" %sno )
dbds=os.path.join( dd11, "s%i-l-db.fits" %sno )

#pyfits.open(dbds)[1].data.field("fnu")

def PlotDSs():

    pylab.clf()

    d=pyfits.open(dbds)[1].data

    pylab.plot( d.field("time"),
                d.field("fnu") )

    pylab.xlabel("Time (h)")
    pylab.ylabel("Tb")    

    pylab.savefig("plots/s114-ds.png")
    pylab.savefig("plots/s114-ds.eps")
    pylab.savefig("plots/s114-ds.pdf")    
    pylab.clf()

    pylab.clf()

    d=pyfits.open(dbds)[1].data

    pylab.plot( d.field("time")[100:500],
                d.field("fnu") [100:500])
    pylab.xlabel("Time (h)")
    pylab.ylabel("Tb")    

    pylab.savefig("plots/s114-ds-zoom.png")
    pylab.savefig("plots/s114-ds-zoom.pdf")    


    pylab.clf()

    d=pyfits.open(dbds)[1].data

    pylab.plot( d.field("time")[2700:3100],
                d.field("fnu") [2700:3100])
    pylab.xlabel("Time (h)")
    pylab.ylabel("Tb")        

    pylab.savefig("plots/s114-ds-zoom2.png")
    pylab.savefig("plots/s114-ds-zoom2.pdf")


    pylab.clf()    

    d=pyfits.open(origds)[1].data

    pylab.plot( d.field("time"),
                d.field("fnu") )

    pylab.savefig("plots/s114-origds.png")
    pylab.savefig("plots/s114-origds.eps")

    pylab.clf()

    d=pyfits.open(origds)[1].data

    pylab.plot( d.field("time")[200:600],
                d.field("fnu") [200:600] - (d.field("fnu")[200:600]).mean())

    d=pyfits.open(dbds)[1].data

    pylab.plot( d.field("time")[100:500],
                d.field("fnu") [100:500])

    pylab.savefig("plots/s114-comb-zoom.png")
        

