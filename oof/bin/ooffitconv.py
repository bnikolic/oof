#
# Bojan Nikolic
#
# $Id: ooffitconv.py,v 1.5 2005/09/19 15:17:05 bnikolic Exp $
#
# Routines to convert OOF fits between various formats

import os
import re
import math

from itertools import izip

import pyfits

import iofits4
import oofreduce
import oofcol

modcvs = r"$Id: ooffitconv.py,v 1.5 2005/09/19 15:17:05 bnikolic Exp $"

def OOFktoOOFnl(k):
    "Converts between the sequential and n,l numbering used in the OOF software"

    nmin= int( math.sqrt(2*k) ) - 1
    nmax= int( math.sqrt(2*k) ) + 1

    n=None
    remainder=None
    for ntrial in range(nmin, nmax):
        if ( (ntrial)*(ntrial+1)/2 <= k):
            n=ntrial
            remainder= k - (ntrial)*(ntrial+1)/2 

    l= -1 * n + 2* remainder
    return  n , l

def OOFnltoOOFk(n,l):
    return n*(n+1)/2 + (n+l)/2

def SchwabnltoSchwabk(n,l):
    return n*(n+1)/2 + (n+l)/2 +1

def OOFktoSchwabk(k):

    """

    Converts the sequential zernike number as output by the oof
    software to the k numbering shown in F. Schwab & M. Mello's memo

    """

    oof_n , oof_l =  OOFktoOOFnl(k)

    ## first, sin and cos terms in Schwab convention are reversed--> reverse l
    sch_n = oof_n
    sch_l = -1 * oof_l

    ## now convert to the sequential number k and return:
    sch_k = SchwabnltoSchwabk(sch_n,sch_l)
    return sch_k

def SchwabktoOOFk(schk):

    for i in range(100):
        if OOFktoSchwabk(i) == schk :
            return i


def ConvertOOFtoGBT (d ):

    "Convert OOF results to the the GBT zernike convention"

    """
    d is a dictionary with with entries { "parname" : parvalue}
    """

    zrex=re.compile ("^z(\d)+")
    
    res={}
    for k in d :
        if zrex.match(k):
            oofk = int(k[1:])
            oofn , oofl = OOFktoOOFnl(oofk)
            gbt1k = OOFktoSchwabk(oofk)

            if oofl <0 : sign = -1.0
            else : sign = 1.0

            if oofk == 1 or  oofk ==2:
                res[ "z%i" % (gbt1k) ] = 0
            else:
                res[ "z%i" % (gbt1k) ] = d[k] * sign 
            

    return res 


def LoadFITS(fnamein):

    "Load parameters from a fits file and return them as a dictionary"

    fin=pyfits.open(fnamein)[1].data
    res = {}
    for rowin in fin:
        res[rowin.field("parname")] = float( rowin.field("parvalue") )
    return res

def SaveFITS(d , fnameout , keys={}):

    "Save the dictionary to a fits file"

    fout=iofits4.PrepFitsOut(modcvs)
    
    coldefs=  [ pyfits.Column( "parname" , "30A" , "unknown" ) ,
                pyfits.Column( "parvalue" , "E" , "unknown" )  ]

    tabout = pyfits.new_table( coldefs , nrows=len(d))

    for k,rowout in izip(d,tabout.data) :
        rowout.setfield("parname", k)
        rowout.setfield("parvalue", d[k] )

    for k in keys:
        tabout.header.update(k , keys[k] )        

    fout.append(tabout)
    iofits4.Write( fout, fnameout , overwrite=1)


def Scale( d , wavel , inv=0):

    c = wavel / (2 * math.pi ) * 1e6 / 2

    if inv: c = 1.0 / c

    zrex=re.compile ("^z(\d)+")
    for k in d:
        if zrex.match(k):
            d[k] = d[k] * c


def MkGBTSfcFile(fnamein, fnameout, wavel ):

    oofdict = LoadFITS(fnamein)

    gbtdict = ConvertOOFtoGBT (oofdict )

    Scale(gbtdict, wavel)

    SaveFITS(gbtdict, fnameout,
             keys=  {"freq":  3e8/wavel } )
    

    

def MkGBTSfcDir(dirin, fnameout):

    "Make a GBT surface correction file"

    # If the offset file exists than that is almost certainly the one
    # to use
    if os.access( os.path.join( dirin , "offsetpars.fits") , os.F_OK):
        fnamein=os.path.join( dirin , "offsetpars.fits" )
    else:
        fnamein=os.path.join( dirin , "fitpars.fits" )

    obsdsfname=  oofcol.getpar(dirin,  "fitinfo.fits", "obsfilename")
    wavel=oofreduce.GetObsWaveL(obsdsfname)

    MkGBTSfcFile( fnamein, fnameout, wavel)
    


    
                             
