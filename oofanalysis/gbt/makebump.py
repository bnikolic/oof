# Bojan NIkolic
# $Id: makebump.py,v 1.3 2006/03/04 16:31:11 bnikolic Exp $
#
# Make bumps for OOF testing

import os
import math

import ooffitconv
import oofplot

# This is the original list as sent by Richard dated 23 Feb 2004

RHBump = { "z1":	0,
           "z2"  :	375,
           "z3"  :	375,
           "z4"  :	0,
           "z5"  :	-265,
           "z6"  :	383,
           "z7"  :	-192,
           "z8"  :	-607,
           "z9"  :	-607,
           "z10"  :	192,
           "z11"  :	17 ,
           "z12"  :	0,
           "z13"  :	-126,
           "z14"  :	-771,
           "z15"  :	0,
           "z16"  :	0,
           "z17"  :	193,
           "z18"  :	250,
           "z19"  :	250,
           "z20"  :	-193,
           "z21"  :	0,
           "z22"  :	0,
           "z23"  :	0,
           "z24"  :	0,
           "z25"  :	144,
           "z26"  :	386
           }

def MkOrig():
    ooffitconv.SaveFITS( RHBump, "bump/rhbumporig.fits",
                         { "freq" : 43e9 })

def MkHalf():
    hb = RHBump.copy()
    for k in hb.keys() : hb[k] = hb[k]/2
    ooffitconv.SaveFITS( hb, "bump/rhbumphalf.fits",
                         { "freq" : 43e9 })    

def RevConvert():
    ooffitconv.SfcFtoOOFpars( "bump/rhbumporig.fits",
                              "bump/rhbumpoof.fits",
                              7e-3)

    ooffitconv.SfcFtoOOFpars( "bump/rhbumphalf.fits",
                              "bump/rhbumphalfoof.fits",
                              7e-3)

def PlotBump():
    oofplot.PlotZernFile( "bump/rhbumpoof.fits",
                          "bump/bumpphase.eps/CPS")

    oofplot.PlotZernFile( "bump/rhbumpoof.fits",
                          "bump/bumpphase.png/PNG")
                          
    oofplot.PlotZernFile( "bump/rhbumphalfoof.fits",
                          "bump/bumphalfphase.png/PNG")
                          
