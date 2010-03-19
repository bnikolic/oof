# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
#
# This file is part of OOF analysis for the GBT. This file superceeds
# the contents of modelwint*.py
"""
Model the gravitational deformation of the GBT using OOF analysis
"""

import os

import localsetup

import pyfits
import bnmin1io

def getModelWint02Data(redprefix="",
                       obsprefix=""):
    """
    Get the data which was used for the modelwint02 model
    
    :param redprefix: Directory the reduced data are stored
    """
    sl0911 = [6 , 14 ,53 ,69, 85, 93, 101 ]
    sl0912 = [ 19 , 27 , 35,  51, 59, 67, 75,  83,  91 ,  99 , 107 , 115,  123,  131 ,  139,
               147]
    sl0411 = [114, 141, 156, 183, 198, 225, 240, 348, 375]

    allscans = []
    allscans.extend([os.path.join(redprefix,
                                  "oofout0911/s%i-l-db-000/z5" %i) for i in sl0911])
    allscans.extend([os.path.join(redprefix,
                                  "oofout0912/s%i-l-db-000/z5" %i) for i in sl0912])
    allscans.extend([os.path.join(redprefix,
                                  "oofout0411/s%i-l-db-000/z5" %i) for i in sl0411])

    obsscans=[]
    obsscans.extend([os.path.join(obsprefix,
                                  "ver001/0911/s%i-l-db.fits" %i) for i in sl0911])
    obsscans.extend([os.path.join(obsprefix,
                                  "ver001/0912/s%i-l-db.fits" %i) for i in sl0912])
    obsscans.extend([os.path.join(obsprefix,
                                  "ver001/0411/s%i-l-db.fits" %i) for i in sl0411])
    
    return allscans, obsscans


def getpardata(pname,
               redscans,
               obsscans):
    """
    Get the observed for parameter pname
    """
    pdata = []
    for scandir, obsds in zip(redscans, obsscans):
        el=pyfits.open(obsds)[0].header["meanel"]
        par=bnmin1io.FGetPar(os.path.join(scandir,
                                          "offsetpars.fits"), 
                             pname)
        
        pdata.append((el,par,obsds))
    return pdata

def printModel(redscans, obsscans):
    pnamel=[]
    res=[]
    fout=open("model.csv", "w")
    fout.write("el,")
    for z in range(3,21):
        pname= ("z%i" %z)
        pnamel.append(pname)
        res.append(getpardata(pname,
                              redscans,
                              obsscans))
        poofname=("z%i" % ooffitconv.OOFktoSchwabk(z))
        fout.write(poofname+",")
    fout.write("\n")
    for i in range(len(res[0])):
        fout.write(str(res[0][i][0])+",")
        for j in range(len(res)):
            fout.write(str(res[j][i][1])+",")
        fout.write("\n")
    


        
                     

