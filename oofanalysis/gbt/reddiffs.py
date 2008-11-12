"""
Bojan Nikolic <bojan@bnikolic.co.uk>

Investigate differences in reductions on different machines
"""

import os

import setup

import oofreduce
import oofplot

datadir="/home/bnikolic/data/gbt-oof/q-band/reddiff/"

def Red():
    oofreduce.Red(os.path.join(datadir,
                               "s19-1-db.fits"),
                  extrafit=[ "beamgainf" ],
                  extraic =[ ("z2" , -6.2),
                             ( "sigma" , 0.3 )],
                  npix=256,
                  oversample=4.0,
                  ds_fwhm=1.0,
                  ds_extent=2.0,
                  nzmax=7,
                  prefdirout="oofout/reddiff")    

def Todds():
    oofreduce.Red(os.path.join(datadir,
                               "s19-1-db.fits"), 
                  prefdirout = "oofout/todds",
                  extraic=[("z2",-6.2),("sigma",0.3)],
                  nzmax=7)
