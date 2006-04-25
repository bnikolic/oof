# Bojan Nikolic
# $Id: verification.py,v 1.1 2006/04/25 13:24:48 bnikolic Exp $
#
# Plot OOF verification results

import string

# Format of data file
#Source   Scan Pol El    UT    Antenna Temp.    Aperture Eff.   Model

def ParseData(fin):

    """
    Format of data file:
    Source   Scan Pol El    UT    Antenna Temp.    Aperture Eff.   Model    
    """

    res = []
    for line in fin:
        ld=string.split(line)
        if len(ld) > 1:
            pol= ld[2]
            elev=float(ld[3])

            apeff= float(ld[8])
            apefferr= float(ld[10])
            model   = ld[11]

            if model == "(None)": model = 0
            elif model == "(2005WinterV1)" : model =1

            res.append ( ( pol, elev,( apeff, apefferr ) , model ))

    return res




        
