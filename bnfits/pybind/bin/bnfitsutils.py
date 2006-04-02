# Bojan Nikolic
# $Id: bnfitsutils.py,v 1.1 2006/04/02 23:15:46 bnikolic Exp $
#
# FITS file utilities exploting pybnfits

import os

import numarray

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


