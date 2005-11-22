# Bojan Nikolic
# $Id: daytimered.py,v 1.1 2005/11/22 20:53:37 bnikolic Exp $
#
# Reduce daytime oof data

import os
import re

import oofplot
import pyplot

import oofreduce


datadir="/home/bnikolic/data/gbtoof/test/"

# Not sure if zernike's were applied for 456 or not?


def Red( dirin, sno):
    
    oofreduce.Red(os.path.join(dirin,  "s%i-l-db.fits" % sno),
                  extrafit=[ "beamgainf" ],
                  extraic =[ ("z2" , -6.2),
                             ( "sigma" , 0.3 )],
                  npix=256,
                  oversample=4.0,
                  ds_fwhm=1.0,
                  ds_extent=2.0,
                  nzmax=5,
                  prefdirout="oofoutday" )
        
#Red("/home/bnikolic/data/gbtoof/ver001/0411/" , 471)
#Red("/home/bnikolic/data/gbtoof/ver001/0411/" , 492)

def Plot():

    p1=oofplot.PlotZernFile( "oofoutday/s456-l-db-000/z5/fitpars.fits" ,
                             "plots/sfcs0411-456.eps/CPS" )

    print "RMS:", pyplot.MapRMS(p1)

    p1=oofplot.PlotZernFile( "oofoutday/s471-l-db-000/z5/fitpars.fits" ,
                             "plots/sfcs0411-471.eps/CPS" )

    print "RMS:", pyplot.MapRMS(p1)

    p1=oofplot.PlotZernFile( "oofoutday/s471-l-db-000/z5/offsetpars.fits" ,
                             "plots/sfcs0411-471-offset.eps/CPS" )

    print "RMS:", pyplot.MapRMS(p1)

    p1=oofplot.PlotZernFile( "oofoutday/s492-l-db-000/z5/fitpars.fits" ,
                             "plots/sfcs0411-492.eps/CPS" )

    print "RMS:", pyplot.MapRMS(p1)

    p1=oofplot.PlotZernFile( "oofoutday/s492-l-db-000/z5/offsetpars.fits" ,
                             "plots/sfcs0411-492-offset.eps/CPS" )

    print "RMS:", pyplot.MapRMS(p1)


#oofplot.PlotDir("oofoutday/s471-l-db-000/z5",bbox=[-0.6e-3, 0.4e-3, -0.5e-3, 0.5e-3],
#                     npix=512,
#                     fwhm=4, extent=10,
#                     ncont=5,
#                     hardcopy=True)
