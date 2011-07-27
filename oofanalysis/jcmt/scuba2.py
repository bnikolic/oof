# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
# July 2011
# 
# Analysis of some OOF test data from SCUBA 2 on the JCMT

import os
import math
import numpy
import pyfits

import localsetup

import iofits4
import pyplot
import implot
import oofreduce
import oofplot

def cntrpx(fnamein):
    """
    Pixel in which the source is expected to be found
    """
    fin=pyfits.open(fnamein)
    mc=[float(fin[0].header["CRPIX1"]), float(fin[0].header["CRPIX2"])]
    return mc

def plotscan(fnamein,
             d=0.03):
    fnameout=os.path.basename(os.path.split(fnamein)[1])+".png/PNG"
    fin=pyfits.open(fnamein)
    mc=[float(fin[0].header["CRVAL1"]), float(fin[0].header["CRVAL2"])]
    m=pyplot.FitsMapLoad(fnamein, 1)
    implot.plotmap(m,
                   valrange=[0,m.max_fin()], 
                   colmap="heat", 
                   bbox=[mc[0]-d, 
                         mc[0]+d, 
                         mc[1]-d, 
                         mc[1]+d],   
                   contours=implot.MkSynthesisContours(m, 
                                                       step=0.5,
                                                       nlevels=9),
                   fout=fnameout)

def genDSArray(fnamein,
               d=30):
    """
    Generated what looks like a time series from a map
    """
    dx, dy, f =[] , [] ,[]
    fin=pyfits.open(fnamein)
    mc=[int(fin[0].header["CRPIX1"]), int(fin[0].header["CRPIX2"])]
    for i in range(mc[0]-d, mc[0]+d):
        for j in range(mc[1]-d, mc[1]+d):
            el= float(fin[0].header["CDELT1"]) * ( (i-mc[0]) * float(fin[0].header["PC1_1"]) + (j-mc[1]) * float(fin[0].header["PC1_2"]))
            az= float(fin[0].header["CDELT2"]) * ( (i-mc[0]) * float(fin[0].header["PC2_1"]) + (j-mc[1]) * float(fin[0].header["PC2_2"]))
            dx.append(az)
            dy.append(el)
            f.append(fin[0].data[0,j,i])
    return numpy.array(dx), numpy.array(dy), numpy.array(f)

def SCUBA2_DHDU(dx, dy, f,
                dZ,
                ufnu=0.001):
    """
    Build a data hdu from data for one defucs setting
    """
    coldefs = [
        pyfits.Column ( "DX",   "E",   "radians",
                        array=numpy.radians(dx)),
        pyfits.Column ( "DY",   "E",   "radians",
                        array=numpy.radians(dy)),
        pyfits.Column ( "fnu",   "E",   "Jy",
                        array=f ),
        pyfits.Column ( "UFNU",   "E",   "Jy",
                        array=(numpy.ones(len(dx))*ufnu )),
        pyfits.Column ( "TIME",   "E",   "d",
                        array=numpy.arange(len(dx)))
        ]

    nh = pyfits.new_table( coldefs )
    nh.header.update("dz", dZ )    
    return nh

def SCUBA2Primary():
    res=pyfits.PrimaryHDU()

    res.header.update("freq" ,   3e8/450e-6 )
    res.header.update("telesc", "JCMT")
    res.header.update("objsize", 0.0)
    res.header.update("Recv", "SCUBA2")
    return res

def buildData(an="a"):
    dirin="/home/bnikolic/data/oof/jctm/"
    res=[SCUBA2Primary()]
    df=[ ("s65-%s.fits"%an, 0),
         ("s67-%s.fits"%an, -0.0004),
         ("s68-%s.fits"%an, -0.0008),
         ("s70-%s.fits"%an, 0.0004),
         ("s71-%s.fits"%an, 0.0008)]
    for fname, dz in df:
        dx, dy, f=genDSArray(os.path.join(dirin, fname),
                             d=25)
        res.append( SCUBA2_DHDU(dx, dy, f, dz))

    iofits4.Write(res ,
                  "jcmtscuba2t.fits" ,
                  overwrite=1,
                  mkpath=1)
    
            
    
    
    
    



