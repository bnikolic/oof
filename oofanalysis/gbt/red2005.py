# Bojan Nikolic
# $Id: red2005.py,v 1.1 2005/09/17 22:15:30 bnikolic Exp $
#
# The general routine for reducing data from the 2005 campaigns

import os
import re

import oofreduce

datadir="/home/bnikolic/data/gbtoof/ver001/"

def GetScanList(obsdate):

    "Get the list of all oof scans for this date"

    res=[]
    fnre=re.compile(r"^s(?P<sno>\d+)-l-db\.fits$" )

    for fname in os.listdir( os.path.join(datadir, obsdate)):
        m=fnre.match(fname)
        if m : res.append( int(m.group("sno")) )
    return res

def Red(obsdate):

    for sno in GetScanList(obsdate):

        oofreduce.Red(os.path.join(datadir, obsdate,  "s%i-l-db.fits" % sno),
                      extrafit=[ "beamgainf" ],
                      extraic =[ ("z2" , -6.2),
                                 ( "sigma" , 0.3 )],
                      npix=256,
                      oversample=4.0,
                      ds_fwhm=1.0,
                      ds_extent=2.0,
                      nzmax=5,
                      prefdirout="oofout" +obsdate )
        
    

        
        

    
