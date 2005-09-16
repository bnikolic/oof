#
# Bojan Nikolic
#
# $Id: red0912.py,v 1.4 2005/09/16 14:59:10 bnikolic Exp $

import os

import oofreduce


datadir="/home/bnikolic/data/gbtoof/ver001/0912"

scanlist= [ 11, 19 , 27 , 35, 43, 51, 59, 67, 75,  83,  91 ,  99 , 107 , 115,  123,  131 ,  139,
            147, 155]

def red():
    for sno in scanlist:
        oofreduce.Red(os.path.join(datadir, "s%i-l-db.fits" % sno),
                      extrafit=[ "beamgainf" ],
                      extraic =[ ("z2" , -6.2),
                                 ( "sigma" , 0.3 )],
                      npix=256,
                      oversample=4.0,
                      ds_fwhm=1.0,
                      ds_extent=2.0,
                      nzmax=5,
                      prefdirout="oofout0912")

def doplot():
    for sno in scanlist:
        oofplot.PlotDir("oofout0912/s%i-l-db-000/z5" %sno,
                        bbox=[ -1e-3, 1e-3, -1e-3, 1e-3])


