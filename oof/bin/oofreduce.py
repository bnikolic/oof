# Bojan Nikolic
# $Id: oofreduce.py,v 1.2 2005/08/16 14:46:10 bnikolic Exp $
#
# Main OOF reduction script

oofreducever = r"$Revision: 1.2 $"

import pyfits

import pyoof

def MkTel(fnamein):

    "Returns the telescope geometry of the telescope specified in the file"

    telname= pyfits.open(fnamein)[0].header["telesc"]

    return pyoof.TelSwitch(telname)


def GetObsWaveL(fnamein):

    "Return the obseving wavelength"

    filein = pyfits.open(fnamein)
    
    return  3e8 / filein[0].header["freq"]






