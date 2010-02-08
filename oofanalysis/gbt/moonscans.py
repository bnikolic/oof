# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>.
# The initial versions of this file appeared in 2005 and was
# signficantly extended in 2006. 
#
# Updated in 2010
"""
Tools for analysis of scans across the Moon and similar data used to
constrain error correlation scales on radio telescopes
"""

import math

import pyfits

import numarray
from matplotlib import pylab

import localsetup

import iofits4

import pyplot
import pybnlib
import pyoof
import implot


sfile= "cdata/TPTCSOOF_050324/s75-l.fits"

def SaveScanFits(dx, fnu , fnameout):

    "Save a moon scan, simulated or observed, to FITS file"

    coldefs = [
        pyfits.Column( "dx" , "E" , "arcmins" ,
                       array=numarray.array(dx)),
        pyfits.Column( "fnu" , "E" , "logpower" ,
                       array=numarray.array(fnu))]

    tabout= pyfits.new_table( coldefs )

    fout=iofits4.PrepFitsOut(r"$Id$")
    fout.append(tabout)
    iofits4.Write( fout,
                   fnameout,
                   overwrite=1)        


def PlotF(fname,
          dxrange=[-30,-16],
          dolog=False,
          logsign=1,
          fitsout=False):

    din=pyfits.open(fname)[1].data

    dx= din.field("dx") * 180 * 60 / math.pi
    fnu = din.field("fnu") 

    mask = numarray.logical_and( dx > dxrange[0] ,
                                 dx < dxrange[1] )

        
    if dolog:

        fnu -= fnu.min()
        
        fnu *= logsign
        mask = numarray.logical_and( mask,
                                     fnu > 0)
        fnu  = numarray.log10(fnu)

    if fitsout:
        SaveScanFits( dx[mask], fnu[mask] , fitsout)
        
    pylab.plot(dx[mask], fnu[mask])
    pylab.show()

#PlotF("cdata/TPTCSOOF_050324/s75-l-tp.fits", dxrange=[-40,-15], dolog=True)
#PlotF("cdata/TPTCSOOF_050324/s75-l-tp.fits", dxrange=[15,45], dolog=True)

def MkMoon(m, Cm=0):

    # moon radius 15 arcmin
    mradius=15 * math.pi / 180 / 60

    moonfn  =  pybnlib.TaperedTopHatDD()
    moonfn.radius  =  mradius
    moonfn.Cm = Cm
    pyplot.WorldSet( m , moonfn)
    pyplot.FitsWrite(m, "!temp/moon.fits")    
    



def GenBeam( pixrms,
             fnameout,             
             npix=1024,
             corrscale=4,
             postmult=1,
             telradius=50,
             soften=False,
             oversample=2,
             taper=0.3
             ):


    # Note oversample needs to be  2 here for critical sampling!

    #tel=pyoof.TelSwitch("GBT")
    tel=pyoof.PrimeFocusGeo()
    tel.PrimRadius=telradius
    
    mphase=pyoof.MkApMap(tel,
                         npix,
                         oversample)

    mtemp  = pyplot.Map( npix / corrscale,
                         npix / corrscale)

    
    pyplot.NormDist( mtemp,
                     pixrms)

    
    mphase2=pyplot.IntZoom ( mtemp, corrscale)
    mphase2.mult(postmult)

    if soften:
        mconvk  =  pyplot.Map(npix, npix)

        MkSquare(mconvk, soften)
        mphase3=pyplot.FFTConvolve(mphase2,
                                   mconvk)
        mphase3.mult( 1.0/ soften**2)
        mphase2=mphase3
    
    pyplot.FitsWrite(mphase2, "!temp/mphase2.fits")    


    
    #pyplot.NormDist( mphase,
    #                     pixrms)

    mamp=pyoof.MkApMap(tel,
                       npix,
                       oversample)

    mbeam = pyoof.MkApMap(tel,
                          npix,
                          oversample)

    ilmod=pyoof.GaussAmpMod( tel, mamp)
    ilmod.SetSigma(taper)
    ilmod.Calc(mamp)
    pyplot.FitsWrite(mamp, "!temp/aplitude.fits")

    farf= pyoof.FarF(mamp, 7.3e-3)

    print "Maps weighted rms is : ", pyplot.MapRMS(mphase2, mamp)

    if soften:
        farf.Power( mamp, mphase3, mbeam)
    else:
        farf.Power( mamp, mphase2, mbeam)

    pyplot.FitsWrite(mbeam, fnameout)

# std GenBeam(0.43 , "!temp/d10.fits", corrscale=8, postmult=1)
#GenBeam(0.43 , "!temp/d10_s.fits", corrscale=8, postmult=1, soften=True)    

def TruncateBeam(fnamein, fnameout,
                 rad_arcmin):

    "Set beam everywhere outside certain pixel radius range to value indicated"

    mapin = pyplot.FitsMapLoad(fnamein, 1)

    mtemp = pyplot.Clone(mapin)
    tfn=  pybnlib.TopHatDD()
    tfn.radius = rad_arcmin * math.pi / 180 / 60
    pyplot.WorldSet( mtemp , tfn)

    mapin.mult(mtemp)
    pyplot.FitsWrite(mapin, fnameout)
    # Turns out truncation not very usefull, better off figuring out
    # how to get good beams without all the nasty ailasing

#TruncateBeam( "temp/d10.fits" , "!temp/d10_t.fits", 20)
    
    

def MkSquare (m, s):

    sx = m.nx /2 -s/2
    sy = m.ny /2 -s/2

    for i in range(s):
        for j in range(s):
            m.set(sx+i , sy+j, 1)

            
def MkMoonScan( fbeam,
                fnameout, Cm=0):

    mbeam = pyplot.FitsMapLoad(fbeam, 1)
    mmoon = pyplot.Clone(mbeam)
    MkMoon(mmoon, Cm=Cm)

    res=pyplot.FFTConvolve(mbeam,
                           mmoon)

    pyplot.FitsWrite(res, fnameout)

#MkMoonScan( "temp/d10_t.fits" , "!temp/moonscan2.fits")
    

def PlotSynthBeam(finlist):

    for fnamein in finlist:

        delt=pyfits.open(fnamein)[0].header["CDELT1"]
        din=pyfits.open(fnamein)[0].data

        nx, ny = din.shape
        
        fnu = din[ny/2,:]
        dx  = ( numarray.arange(nx, type=numarray.Float64) - nx/2) * delt * 180 * 60 / math.pi
        mask = fnu > 0

        pylab.plot(dx[mask],
                   numarray.log10(fnu[mask]))
        
        
    pylab.show()

def ModelTPScan(fnamein):

    delt= pyfits.open(fnamein)[0].header["CDELT1"]
    din=pyfits.open(fnamein)[0].data
    
    nx, ny = din.shape
    
    fnu = din[ny/2,:]

    dx  = ( numarray.arange(nx, type=numarray.Float64) - nx/2) * delt * 180 * 60 / math.pi

    return dx , fnu

def ModelDiffScan(fnamein,
                  diffgain):

    
    delt= pyfits.open(fnamein)[0].header["CDELT1"]
    din=pyfits.open(fnamein)[0].data
    beamsep_px = int(56*4.8e-6 / delt)
    
    nx, ny = din.shape
    
    fnu = din[ny/2,:]
    fnudiff = fnu[:nx-beamsep_px] - fnu[beamsep_px:]* diffgain
        
    dx  = ( numarray.arange(nx, type=numarray.Float64) - nx/2) * delt * 180 * 60 / math.pi

    return dx[beamsep_px:] , fnudiff



def PlotDiffd(finlist,
              diffgain=0.8,
              dxrange=[-30,-16],
              dolog=False,
              logsign=1):

    for fnamein in finlist:

        dx, fnudiff = ModelDiffScan(  fnamein, diffgain=diffgain)

        mask = numarray.logical_and( dx > dxrange[0] ,
                                     dx < dxrange[1] )

        
        if dolog:
            
            fnudiff *= logsign
            mask = numarray.logical_and( mask,
                                         fnudiff > 0)
            fnudiff  = numarray.log10(fnudiff)
            
            
        pylab.plot(dx[mask], fnudiff[mask])
        

    pylab.show()

    

def PlotTP(finlist,
           dxrange=[-30,-16],
           dolog=False,
           logsign=1,
           fitsout=False):

    for fnamein in finlist:

        dx, fnudiff = ModelTPScan(  fnamein)
        mask = numarray.logical_and( dx > dxrange[0] ,
                                     dx < dxrange[1] )

        
        if dolog:
            
            fnudiff *= logsign
            mask = numarray.logical_and( mask,
                                         fnudiff > 0)
            fnudiff  = numarray.log10(fnudiff)
            
            
        pylab.plot(dx[mask], fnudiff[mask])
        if fitsout:
            SaveScanFits( dx[mask], fnudiff[mask] , fitsout)        

    pylab.show()

def MkLargeScaleErrors():

    GenBeam(0.43 * 250/250 , "!temp/dexp.fits", corrscale=32, postmult=1)
    MkMoonScan( "temp/dexp.fits" , "!temp/moonsexp.fits")
    PlotTP(["temp/moonsexp.fits"] ,
           dxrange=[-40,-14] ,
           dolog=True,
           fitsout="moonscand/modelexp.fits")
    
    
