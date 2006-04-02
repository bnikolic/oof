# Bojan Nikolic
# $Id: bnfitsutils.py,v 1.2 2006/04/02 23:34:08 bnikolic Exp $
#
# FITS file utilities exploting pybnfits

import os

import numarray
import pyfits

import pybnfits


def MaskToList(mask):

    "Turn a mask into a list of rows to delete"

    mask = numarray.array( mask, numarray.Bool)
    xr=numarray.arange( len(mask) )[mask]
    xr=numarray.array(xr)

    res=pybnfits.LongVector(len(xr))
    for i,v in enumerate(xr):
        res[i]=v
    return res

def Select(fname,
           mask):

    "Remove all rows for which mask isn't true"

    rowlist=MaskToList(mask)

    fin=pybnfits.FitsF( fname, pybnfits.FitsF.readwrite)

    fin.HDUseek(2)

    pybnfits.DeleteRows(fin, rowlist)

def Cat(fnameinlist,
        fnameout):

    "Concatenate fits files"

    finlist= [ pybnfits.FitsF( fname, pybnfits.FitsF.read) for fname in fnameinlist]

    nrowstotal= sum([ pybnfits.NRows(f, 2) for f in finlist ])

    fout   = pybnfits.FitsF( fnameout, pybnfits.FitsF.create)
    fout.CreateTbl(nrowstotal, "")
    fout.HDUseek(2)

    #  copy first table:
    ncols=len(pyfits.open(fnameinlist[0])[1].data.names)
    cr   =1
    finlist[0].HDUseek(2)
    for i in range(ncols):
        pybnfits.CopyCol(finlist[0],
                             fout ,
                             i+1 ,
                             i+1 ,
                             True )
    cr += pybnfits.NRows(finlist[0],2)

    # copy the data from other files
    
    for fin in finlist[1:]:
        fin.HDUseek(2)
        for i in range(ncols):
            pybnfits.CopyColData(fin,
                                 fout ,
                                 i+1 ,
                                 i+1 ,
                                 cr )
        cr += pybnfits.NRows(fin,2)



    
    
        


