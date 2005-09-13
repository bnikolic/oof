#
# Bojan Nikolic
#
# $Id: red0912.py,v 1.2 2005/09/13 02:13:00 bnikolic Exp $

import os

import oofreduce


datadir="/home/bnikolic/data/gbtoof/ver001/0912"

# scanlist= [11]
scanlist= [19]

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


