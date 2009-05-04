# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Initial version January 2008
#
# Processing/analysis of mustang data

import os
import shutil
import tarfile

import setup


import pyfits
import numarray
import numpy

import iofits4
import oofreduce
import oofplot

import pyplot
import implot
import pyxplot


def CorrectDZ(fnamein):

    "Correct fits files which have dz in mm instead of m"

    fin=pyfits.open(fnamein)

    res=[ fin[0]]
    for h in fin[1:]:
        dz=h.header["dz"]
        print dz
        if abs(dz) < 1.0 :
            print "DZ already less than 1.0, presumably in meters"
        else:
            h.header.update("DZ", dz * 1e-3,
                            "Telescope defocus (m) ")
        res.append(h)
            
    iofits4.Write(res,
                  fnamein,
                  overwrite=1)

def ScaleColumn(fnamein,
                colname,
                scale):
    fin=pyfits.open(fnamein)    
    res=[ fin[0]]
    for h in fin[1:]:
        for i,r in enumerate(h.data):
            h.data.field(colname)[i] = r.field(colname)*scale
        res.append(h)
    iofits4.Write(res,
                  fnamein,
                  overwrite=1)
    
def CorrectUFNU(fnamein):
    """
    Scale UFNU columns by 1e-3 since they seem to be out by that much
    in the supplied files.
    """
    fin=pyfits.open(fnamein)    
    res=[ fin[0]]
    for h in fin[1:]:
        for i,r in enumerate(h.data):
            h.data.field("ufnu")[i] = r.field("ufnu")*1.0e-3
        res.append(h)
    iofits4.Write(res,
                  fnamein,
                  overwrite=1)

def MaxUFNU(fnamein):
    """
    Replace all UFNU's by the maximum UFNU in the file. Useful to make
    sure that the variation in UFNUs doesn't bias too much the final
    fit.
    """
    fin=pyfits.open(fnamein)        
    maxufnu=max([max(h.data.field("ufnu")) for h in fin[1:] ])
    res=[ fin[0]]
    for h in fin[1:]:
        for i,r in enumerate(h.data):
            h.data.field("ufnu")[i] = maxufnu
        res.append(h)
    iofits4.Write(res,
                  fnamein,
                  overwrite=1)    

def SetUFNU(fnamein,
            ufnu=1.0):
    """
    Set all of the unfu columns
    """
    fin=pyfits.open(fnamein)        
    res=[ fin[0]]
    for h in fin[1:]:
        for i,r in enumerate(h.data):
            h.data.field("ufnu")[i] = ufnu
        res.append(h)
    iofits4.Write(res,
                  fnamein,
                  overwrite=1)    

def SetTelsc(fnamein,
             telesc):
    """
    Set telescope name
    """
    fin=pyfits.open(fnamein)        
    fin[0].header.update("TELESC",telesc)
    iofits4.Write(fin,
                  fnamein,
                  overwrite=1)        

    
    

def RemoveStartEnd(fnamein,
                   fnameout,
                   cut=5.0):

    "Remove the starts and the ends of the scans"

    fin=pyfits.open(fnamein)

    res=[ fin[0]]
    for h in fin[1:]:

        time=h.data.field("time")
        mt  = max(time)

        mask = numpy.logical_and( time > cut,
                                  time < ( max(time) - cut))
        print sum(mask)

        print len(h.data)
        h.data = h.data[mask]
        print len(h.data)        
        res.append(h)
            
    iofits4.Write(res,
                  fnameout,
                  overwrite=1)

def SelectCR( din,
              colno,
              rowno):

    """
    Select a single pixel by column and row numbers
    """
    r=numpy.logical_and(din.field("col") == colno,
                        din.field("row") == rowno)
    #Possible work-around for a bug: make sure the returned value has
    #boolean type
    return numpy.array(r,dtype=numpy.bool)


def SinglePixelFile(fnamein,
                    fnameout,
                    colno,
                    rowno):
    """
    Extract single pixel of data from a multi-pixel Mustang data file

    excample usage:
    >>> SinglePixelFile("/home/bnikolic/data/gbt-oof/mustang/agbt08a/agbt08a-056-08-s82s83s843C279.fits",
                        "/home/bnikolic/data/gbt-oof/mustang/agbt08a/c67.fits" , 6, 7)
                    
    """
    fin=pyfits.open(fnamein)
    res=[ fin[0]]
    for h in fin[1:]:
        mask=SelectCR(h.data, colno, rowno)
        newdata=h.data._clone((sum(mask),))
        newdata[:]=numpy.array(h.data)[mask]
        h.data=newdata
        res.append(h)
    iofits4.Write(res,
                  fnameout,
                  overwrite=1)


def residualsW(obsfname,
               beamfname):
    """
    Compute noise-weighted residuals

    :returns: List of noise-weighted residuals arrays, one for each
    de-focus setting
    """
    res=[]
    odata=pyfits.open(obsfname)
    dslist=oofplot.dsObsModel(obsfname,
                              beamfname)
    for i,(obsd,modeld) in enumerate(dslist):
        res.append((obsd-modeld[:,2])/modeld[:,3])
    return res    

def SinglePixelChiSq(obsfname,
                     beamfname,
                     col,
                     row,
                     res=None):
    """
    Compute the chi-sq contribution of a single pixel

    :param obsfname: FITS file with the observed time stream data

    :param res: If res is passed, use these residuals rather than
    re-computing for each pixel separately. (see PixelChiSq() )

    """
    if res is None:
        res=residualsW(obsfname,
                       beamfname)
    odata=pyfits.open(obsfname)
    r=0
    for i,x in enumerate(res):
        mask=SelectCR(odata[i+1].data,
                      col,row)
        r+= numpy.sum((res[i][mask])**2)
    return r

def PixelList(obsfname):
    """
    Return every unique pixel present in file as a (col,row) pair
    """
    d=pyfits.open(obsfname)[1].data
    pl=zip(d.field("col"), 
           d.field("row"))
    return numpy.unique(pl)

def PixelChiSq(obsfname,
               beamfname,
               doprint=True):
    """
    Return sorted list of per-pixel chi-squared contributions
    """
    residuals=residualsW(obsfname,
                         beamfname)
    res=[]
    for c,r in PixelList(obsfname):
        chsq=SinglePixelChiSq(obsfname,
                              beamfname,
                              c,r,
                              residuals)
        res.append( (chsq, (c,r)))
    res.sort()
    if doprint:
        printPixelChiSq(res)
    return res

def printPixelChiSq(res):
    """
    Print the results of PixelChiSq in easier to read format
    """
    for ch, (c,r) in res:
        print "Col=%i, Row=%i :  Chi-sq=%g" % (c, r, ch)

               

def CombineFiles( fnamelist,
                  fnameout):
    """Combine OOF observations in multiple files
    
    Designed for use with Mustang data after spliting out pixels into
    separate files.
    """
    finl = [pyfits.open(x) for x in fnamelist]
    # Open for second time, since some operations unexpectedly modify
    # the data
    clean = [pyfits.open(x) for x in fnamelist]

    # Take primary HDU from the first file
    res=[ finl[0][0] ]
    for i in range(1,len(finl[0])):
        rows=[ x[i].data.shape[0] for x in finl]
        trows= sum(rows)

        h1 = finl[0][i]
        h1.data = finl[0][i].data._clone((trows,))
        crow=0
        for j,h in enumerate([x[i] for x in clean]):
            h1.data[crow:crow+rows[j]]= h.data
            crow+= rows[j]
        res.append(h1)

    iofits4.Write(res,
                  fnameout,
                  overwrite=1)        

def PlotPixTimeSer(fnamein,
                   hduno,
                   pixno):

    f=pyfits.open(fnamein)
    mask= ( f[hduno].data.field("PixID") == pixno)
    pylab.plot( f[hduno].data.field("time")[mask],
                f[hduno].data.field("fnu")[mask])
    


tpar18list=  [ "0854+2006tpar18s56s58.fits",
               "0854+2006tpar18s59s61.fits",
               "0854+2006tpar18s64s66.fits" ]

def RedTPAR18():

    dirin= "/home/bnikolic/data/gbt-oof/mustang/TPAR18/"
    obslist = tpar18list

    for f in obslist:
        fnamein=os.path.join(dirin, f)
        CorrectDZ(fnamein)
        fs=fnamein[:-5] + "_s.fits"
        RemoveStartEnd( fnamein ,
                        fs)

        oofreduce.Red(fs)
        
        
def PlotAndPack():

    tf=tarfile.open("oofout/tpar18analysis.tar.bz2" , "w:bz2")

    for f in tpar18list:
        fs = os.path.join("oofout", f[:-5] + "_s-000"  , "z5")
        oofplot.PlotDir(fs, bbox=[ -6e-4 * x for x in [-1 ,1,-1,1] ])
        tf.add( fs )

def PlotObitMUSTANG(sno):

    fnamein="/home/bn204/d/data/oof/gbt/mustang/obit/OOF/0854+2006.%i.CalImage.fits" % sno

    m=pyplot.FitsMapLoad(fnamein ,1)
    pyplot.ReplaceInfNaN(m, 0)

    implot.plotmap(m, colmap="heat")
    
    
    
def CopyData():
    """Copy across original data

    Getting hit by long pathnames again
    """

    dirin="/home/bnikolic/data/gbt-oof/mustang/06032008/t/"

    for fin, fout in [ ("tpar18s56s58-pfit30ptc0854+2006.fits", "s56-p30.fits"),
                       ("tpar18s56s58-pfit60ptc0854+2006.fits", "s56-p60.fits"),
                       ("tpar18s56s58-subcommon0854+2006.fits", "s56-sc.fits"),
                       ]:
        ffout=os.path.join("td", fout)
        shutil.copy( os.path.join(dirin, fin),
                     ffout)
        CorrectDZ(ffout)

    dir2="/home/bnikolic/data/gbt-oof/mustang/06032008/t2/"
    ffout = os.path.join("td", "s56-p18.fits")
    shutil.copy( os.path.join(dir2, "tpar18s56s58-apr080854+2006.fits"),
                 ffout)
    CorrectDZ(ffout)    
    
    

def ComapareBaselineRemoval(col, row,
                            trim=False):
    
    """
    Push single pixels through the pipeline to check if baseline
    removal is better.

    """
    if 0:
        fl = [ "s56-p30.fits",
               "s56-p60.fits",
               "s56-sc.fits",]
    fl = [ "s56-p18.fits" ,]

    for f in fl:
        ofname =  ("c%i%i-" % (col, row) )+f
        SinglePixelFile( os.path.join("td",f),
                         os.path.join("temp",ofname) ,
                         col,
                         row)

        if trim:
            tf= ofname[:-5]+"-tr.fits"
            RemoveStartEnd(os.path.join("temp",ofname),
                           os.path.join("temp",tf))
            ofname=tf

        oofreduce.Red(os.path.join("temp",ofname) ,
                      nzmax=5)

        oofplot.PlotDir( os.path.join("oofout",
                                      ofname[:-5] + "-000",
                                      "z5"))
        oofplot.PlotDir( os.path.join("oofout",
                                      ofname[:-5] + "-000",
                                      "z2"))        
                         
                                      
def PlotSignal(fnamein,
               pixel_l,
               fnameout,
               hdu=1,
               trange=None):

    din= pyfits.open(fnamein)[hdu].data
    xv, yv = [] , []

    for c, r  in pixel_l:
        mask = SelectCR(din, c, r)
        time =din.field("time")

        if trange is not None:
            mask= numarray.logical_and(mask,
                                       time>=trange[0])
            mask= numarray.logical_and(mask,
                                       time<trange[1])

        xv.append(time[mask])
        yv.append(din.field("fnu")[mask])

    pyxplot.vect( xv, yv, fnameout, multi=True,
                  xax=pyxplot.axis(r"$t\,$(s)"),
                  yax=pyxplot.axis(r"$F_{\nu}$"),
                  )
        
    
def doSigPlots():

    def BothPlots(fin, pl, fout, **kwargs):
        for x in [".eps", ".pdf"]:
            PlotSignal(fin, pl, fout+x, **kwargs)        

    if 0:
        PlotSignal("td/s56-p30.fits", ((7,0),(7,1)), "plots/compare7071.eps", trange=(65,85), hdu=2)
        PlotSignal("td/s56-p30.fits", ((7,0),(7,1)), "plots/compare7071.pdf", trange=(65,85), hdu=2)

        PlotSignal("td/s56-p30.fits", ((7,0),(5,0)), "plots/compare7050.pdf", trange=(65,85), hdu=2)
        PlotSignal("td/s56-p30.fits", ((7,0),(5,0)), "plots/compare7050.eps", trange=(65,85), hdu=2)


        PlotSignal("td/s56-sc.fits", ((7,0),(7,1)), "plots/compare7071-sc.pdf", trange=(65,85), hdu=2)


        
        BothPlots("td/s56-sc.fits", ((7,0),(7,1)), "plots/compare7071-sc-drift", trange=(0,200), hdu=3)

        BothPlots("td/s56-sc.fits", ((7,0),(7,1)), "plots/compare7071-sc-drift-zm", trange=(0,50), hdu=3)
        BothPlots("td/s56-sc.fits", ((7,0),(7,1)), "plots/compare7071-sc-osc", trange=(0,50), hdu=1)

    BothPlots("td/s56-p18.fits", ((7,0),(7,1)), "plots/7071-p18", trange=(71,76), hdu=2)



def FigsForMRAOTalk():
    oofreduce.Red("/home/bnikolic/data/gbt-oof/AGBT09A_052_01/Raw/s8-1.fits",nzmax=8)
    oofreduce.Red("/home/bnikolic/data/gbt-oof/AGBT09A_052_01/Raw/s15-1.fits",nzmax=8)

    oofreduce.Red("/home/bnikolic/data/gbt-oof/AGBT08C_078_02/Raw/s140-1.fits",nzmax=8)

    oofplot.PlotDir("oofout/s8-1-000/z7", bbox=[ -6e-4 * x for x in [-1 ,1,-1,1] ])
    oofplot.PlotDir("oofout/s15-1-000/z7", bbox=[ -6e-4 * x for x in [-1 ,1,-1,1] ])
