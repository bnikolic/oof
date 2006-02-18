# Bojan Nikolic
# $Id: red2005.py,v 1.2 2006/02/18 20:40:02 bnikolic Exp $
#
# The general routine for reducing data from the 2005 campaigns

import os
import re

import oofreduce
import oofplot

datadir=os.path.join(os.environ["AstroData"],
                     "gbtoof/ver001/")

def GetScanList(obsdate):

    "Get the list of all oof scans for this date"

    res=[]
    fnre=re.compile(r"^s(?P<sno>\d+)-l-db\.fits$" )

    for fname in os.listdir( os.path.join(datadir, obsdate)):
        m=fnre.match(fname)
        if m : res.append( int(m.group("sno")) )
    return res

def GetRedScanList(obsdate):

    "Get the list of all reduced oof scans for this date"

    res=[]
    fnre=re.compile(r"^s(?P<sno>\d+)-l-db-000$" )

    for fname in os.listdir( os.path.join("oofout%s"% obsdate)):
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
        
    
def Plot(obsdate):

    for sno in GetRedScanList(obsdate):

            oofplot.PlotDir( "oofout%s/s%i-l-db-000/z5" % (obsdate, sno) ,
                     bbox=[-0.6e-3, 0.4e-3, -0.5e-3, 0.5e-3],
                     npix=512,
                     fwhm=4, extent=10,
                     ncont=5,
                     hardcopy=True)

        
    
        
        

    
