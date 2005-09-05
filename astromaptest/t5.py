# Bojan Nikolic
# Tests of the OOF system

datadir="/home/bnikolic/data/gbtoof/TPTCSOOF_050411"

import os
import oofreduce
import pyfits
import oofplot

scanfiles = [ "s114-l-db.fits" ,
              "s141-l-db.fits" ,
              "s156-l-db.fits" ,
              "s183-l-db.fits",
              "s198-l-db.fits" ,
              "s225-l-db.fits" ,
              "s240-l-db.fits",
              "s30-l-db.fits" ,
              "s348-l-db.fits",
              "s375-l-db.fits",
              "s456-l-db.fits",
              "s471-l-db.fits",
              "s492-l-db.fits",
              "s57-l-db.fits",
              "s72-l-db.fits",
              "s99-l-db.fits"]


if 1:
    for x in scanfiles[1:2]:
        oofreduce.Red(os.path.join(datadir, x),
                      extrafit=[ "beamgainf" ],
                      extraic =[ ("z2" , -6.2),
                                 ( "sigma" , 0.3 )],
                      npix=256,
                      oversample=4.0,
                      ds_fwhm=1.0,
                      ds_extent=2.0,
                      nzmax=5,
                      dsreverse=False)

def printpar( pname , nz):

    for x in scanfiles:
        din = pyfits.open( os.path.join("oofout", x[:-5]+"-000" , "z%i" % nz , "fitpars.fits"))[1].data
        parindex= din.field("parname").search(pname)[0][0]
        print x , din.field("parvalue")[parindex]


def printel():

    for x in scanfiles:
        fnamein=os.path.join(datadir, x)

        print x , pyfits.open(fnamein)[0].header["meanel"]
        



#Plot example
#PlotDir("oofout/s114-l-db-005/z2", bbox=[ -1e-3, 1e-3, -1e-3, 1e-3])
