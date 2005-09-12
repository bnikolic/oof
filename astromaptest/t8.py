# Bojan Nikolic
# Tests of the OOF system
#
# $Id: t8.py,v 1.1 2005/09/12 04:29:00 bnikolic Exp $
#

datadir="/home/bnikolic/data/gbtoof/ver001/0911"

import os
import oofreduce
import pyfits
import oofplot



clist= [6] 

scanfiles = [ "s%i-l-db.fits" % sno for sno in clist] 


def red():
    for sno in clist:
        oofreduce.Red(os.path.join(datadir, "s%i-l-db.fits" % sno),
                      extrafit=[ "beamgainf" ],
                      extraic =[ ("z2" , -6.2),
                                 ( "sigma" , 0.3 )],
                      npix=256,
                      oversample=4.0,
                      ds_fwhm=1.0,
                      ds_extent=2.0,
                      nzmax=5)
    



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

#InvertDSFile ("/home/bnikolic/data/gbtoof/TPTCSOOF_050411/s141-l-db.fits" , "/home/bnikolic/data/gbtoof/TPTCSOOF_050411/s141-l-db-rev.fits")
