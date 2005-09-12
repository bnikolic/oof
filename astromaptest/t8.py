# Bojan Nikolic
# Tests of the OOF system
#
# $Id: t8.py,v 1.2 2005/09/12 05:58:26 bnikolic Exp $
#

datadir="/home/bnikolic/data/gbtoof/ver001/0911"

import os
import oofreduce
import pyfits
import oofplot
import ooffitconv



#clist= [6 , 15]
clist= [29] 

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
#oofplot.PlotDir("oofout/s6-l-db-000/z5", bbox=[ -1e-3, 1e-3, -1e-3, 1e-3])

#ooffitconv.MkGBTSfcFile("oofout/s6-l-db-000/z5", "Fall05Exp1/surfacepars-el60.fits")
#MkGBTSfcFile("oofout/s6-l-db-000/z5", "Fall05Exp1/surfacepars-el60.fits")

# here is a good one -- see if the difference in apertures in scans 6
# and 29 consistent with what was dialed in?

if 0:
    import pyplot

    fname1="oofout/s6-l-db-000/z5/aperture-offset.fits"
    fname2="oofout/s29-l-db-001/z5/aperture-offset.fits"

    f1=pyplot.FitsMapLoad(fname1,2)
    f2=pyplot.FitsMapLoad(fname2,2)

    f1.mult(-1)
    f2.add(f1)
    implot.plotmap(f2, bbox=[-60,60,-60,60], colmap="heat")
    #Works out OK.


