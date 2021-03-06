# Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
#
# Initial version May 2008
#
# Investigate effects on Mustang data

import os
import shutil

import setup

import pyfits
import numpy
import iofits4

import mustang
import baselinealgo
import oofreduce
import oofplot
import oofcol

laptop_dirin="/home/bnikolic/data/gbt-oof/mustang2/"


def PrepareInputs(col=5, row=0,
                  do90=False):

    """Extract single pixel from input data, copies to shorter path, remove start/end"""

    for (fin, xfout ) in [ ("tpar18s56s58-apr080854+2006.fits",
                            "t18-poly-%i-%i.fits"),
                           ("tpar18s56s58-raw0854+2006.fits",
                            "t18-raw-%i-%i.fits"),                           
                           ]:

        fout= xfout % ( col, row)
        ffin = os.path.join(laptop_dirin, fin)
        ffout= os.path.join("td", fout)
        
        mustang.SinglePixelFile(ffin,
                                ffout,
                                col, row)

        mustang.RemoveStartEnd(ffout, ffout)
        mustang.CorrectDZ(ffout)
        mustang.CorrectUFNU(ffout)
        if do90:
            mustang.SetTelsc(ffout,"90GBT")
        #mustang.MaxUFNU(ffout)
        #mustang.SetUFNU(ffout)


def PrepareInputsV2(col=5, row=0):

    dirin="/home/bnikolic/data/gbt-oof/mustang3/"
    for (fin, xfout ) in [ ("tpar18s56s58-02jul080854+2006.fits",
                            "t18-poly-%i-%i-v2.fits"),
                           ("tpar18s56s58-raw02jul080854+2006.fits",
                            "t18-raw-%i-%i-v2.fits"),                           
                           ]:

        fout= xfout % ( col, row)
        ffin = os.path.join(dirin, fin)
        ffout= os.path.join("td", fout)
        
        mustang.SinglePixelFile(ffin,
                                ffout,
                                col, row)

        mustang.RemoveStartEnd(ffout, ffout)
        mustang.CorrectDZ(ffout)
        #mustang.MaxUFNU(ffout)
        #mustang.SetUFNU(ffout)

        
def RoughReduce():

    if 0:
        oofreduce.Red("td/t18-poly-5-0.fits")
        oofplot.PlotDir("oofout/t18-poly-5-0-000/z1")
        RemoveBaseline("td/t18-poly-5-0.fits", "td/t18-poly-5-0-db.fits")
        oofreduce.Red("td/t18-poly-5-0-db.fits")
        RemoveBaseline("td/t18-raw-5-0.fits", "td/t18-raw-5-0-db-lr.fits", rad=2e-4)
    if 0:
        oofreduce.Red("td/t18-raw-5-0.fits")
        oofplot.PlotDir("oofout/t18-raw-5-0-000/z1")
    if 0:
        PrepareInputs(5,1)
        RemoveBaseline("td/t18-raw-5-1.fits", "td/t18-raw-5-1-db.fits")        
        oofreduce.Red("td/t18-raw-5-1-db.fits", nzmax=5)
        oofplot.PlotDir("oofout/t18-raw-5-1-db-000/z3")

    if 0:
        PrepareInputs(5,3)
        RemoveBaseline("td/t18-raw-5-3.fits", "td/t18-raw-5-3-db.fits")        
        oofreduce.Red("td/t18-raw-5-3-db.fits", nzmax=5)
        oofplot.PlotDir("oofout/t18-raw-5-3-db-000/z3")

    if 0:
        PrepareInputs(7,1)
        RemoveBaseline("td/t18-raw-7-1.fits", "td/t18-raw-7-1-db.fits")        
        oofreduce.Red("td/t18-raw-7-1-db.fits", nzmax=5)
        oofplot.PlotDir("oofout/t18-raw-7-1-db-000/z3")

    if 0:
        PrepareInputs(7,7)
        RemoveBaseline("td/t18-raw-7-7.fits", "td/t18-raw-7-7-db.fits")        
        oofreduce.Red("td/t18-raw-7-7-db.fits", nzmax=5)
        oofplot.PlotDir("oofout/t18-raw-7-7-db-000/z3")

    if 1:
        PrepareInputs(0,7)
        RemoveBaseline("td/t18-raw-0-7.fits", "td/t18-raw-0-7-db.fits")        
        oofreduce.Red("td/t18-raw-0-7-db.fits", nzmax=5)
        oofplot.PlotDir("oofout/t18-raw-0-7-db-000/z3")

def MustangPL():
    """Return of pixels on MUSTANG array in order they occurr"""
    return [ (2,1), (2,4), 
             (2,6),
             (3,3),
             (3,6),
             (4,0),
             (1,6),
             (2,0),
             (2,3),
             (2,7),
             (3,0),
             (3,4),
             (3,7),
             (4,1),
             (1,4),
             (1,5),
             (2,2),
             (2,5),
             (3,2),
             (3,5),
             (4,2),
             (4,3),
             (1,3),
             (1,1),
             (4,7),
             (4,6),
             (4,4),
             (4,5),
             (0,6),
             (0,7),
             (0,5),
             (7,0),
             (5,0),
             (5,1),
             (5,3),
             (0,4),
             (7,1),
             (6,5),
             (6,2),
             (0,1),
             (0,0),
             (7,3),
             (6,7),
             (6,3),
             (6,0),
             (5,6),
             (7,7),
             (7,6),
             (7,4),
             (7,2),
             (6,6),
             (6,4),
             (6,1),
             (5,7)]

def DoAPixel(c,r,
             ver=1,
             multiamp=False,
             do90=False,
             usepoly=False,
             base_rad=1.5e-4,
             ):
    """
    Process a single pixel and copy the output aperture phase plot to
    temporary directory for visualisation
    """
    if ver == 1:
        PrepareInputs(c,r,
                      do90=do90)
        fnameraw= "td/t18-raw-%i-%i.fits" % (c,r)
        fnamepoly="td/t18-poly-%i-%i.fits" % (c,r)
    elif ver == 2:
        PrepareInputsV2(c,r)
        fnameraw= "td/t18-raw-%i-%i-v2.fits" % (c,r)
    else:
        raise "Unkown version"
    if usepoly :
        obsfname=fnamepoly
    else:
        fnamedb = fnameraw[:-5]+"-db.fits"
        RemoveBaseline(fnameraw , 
                       fnamedb,
                       rad=base_rad)        
        obsfname=fnamedb

    oofreduce.Red(obsfname, 
                  nzmax=5,
                  multiamp=multiamp)

    for z in [3,5]:

        oofplot.PlotDir("oofout/t18-raw-%i-%i-db-000/z%i" % (c,r,z))
        shutil.copy( "oofout/t18-raw-%i-%i-db-000/z%i/plots/aperture-phase.png" % (c,r,z),
                     "temp/plots/p%i%i-z%i.png" % (c,r,z))
    
def DoAllPixels(**args):
    """
    Extract all pixels individually, process to z=5, plot and copy
    plots to a directory
    
    See also DoAPixel
    """
    for c,r in MustangPL():
        try:
            DoAPixel(c,r,**args)
        except None, e :
            print e
            print "Pixel not processed: " , c, r
            pass
        except AttributeError :
            print "Pixel has no data: " , c, r
        except ValueError:
            pass


def tableDict(tin):
    res={}
    for r in tin.data:
        res[r.field("Parameter")]=r.field("Value")
    return res

def FitChi(z=3):
    
    for c,r in MustangPL():
        try:
            f=pyfits.open("oofout/t18-raw-%i-%i-db-000/z%i/fitinfo.fits" % (c,r,z))
            d=tableDict(f[2])
            print "C=%i, R=%i : %s " % (c,r,
                                        str(d["chisquaredfinal"]))
        except :
            pass
        
def AllPixIC():
    """Process all pixels, without stepping through Zernike orders and
    starting from a single initial condition
    """
    for c,r in MustangPL():
        try:
            fnamedb = "td/t18-raw-%i-%i-db.fits" % (c,r)
            oofreduce.RedOrder(fnamedb,
                               "oofout/ic",
                               ic="oofout/t18-raw-5-3-db-000/z5/fitpars.fits",
                               zorder=5)
            oofplot.PlotDir("oofout/ic")
            shutil.copy("oofout/ic/plots/aperture-phase.png",
                        "temp/plot-ic/p%i%i-ic-z5.png" % (c,r))
        except None, e :
            print "Pixel not processed: " , c, r
        except AttributeError :
            print "Pixel has no data: " , c, r
        except IOError:
            pass
    



def RemoveBaseline(fnamein,
                   fnameout,
                   rad=1.5e-4):

    fin=pyfits.open(fnamein)

    res=[ fin[0]]
    for h in fin[1:]:

        fnu,mask=baselinealgo.rmBase( h.data.field("dx"),
                                      h.data.field("dy"),
                                      h.data.field("fnu"),
                                      baselinealgo.circleMask(0,0,rad) )
        
        h.data = h.data[mask]
        for i,f in enumerate( fnu[numpy.array(mask)] ):
            h.data.field("fnu")[i]=float(f)
        res.append(h)
            
    iofits4.Write(res,
                  fnameout,
                  overwrite=1)    



def Red20080606():
    """Reductions on 6th june"""

    # Plain reduction
    oofreduce.Red("td/t18-raw-5-0-db.fits", nzmax=5)
    oofplot.PlotDir("oofout/t18-raw-5-0-db-000/z5")
    # Try bigger map, oversampling, as in Q-band
    oofreduce.Red("td/t18-raw-5-0-db.fits", nzmax=5,
                  npix=256,
                  oversample=4.0,
                  ds_fwhm=1.0,
                  ds_extent=2.0)
    oofplot.PlotDir("oofout/t18-raw-5-0-db-001/z5")
    # Nothing interesting...

    # Compare to another pixel
    oofreduce.Red("td/t18-raw-7-0-db.fits", nzmax=5)
    oofplot.PlotDir("oofout/t18-raw-7-0-db-000/z5")

    oofreduce.Red("td/t18-raw-5-1-db.fits", nzmax=5)
    oofplot.PlotDir("oofout/t18-raw-5-1-db-000/z3")

    
def Red20080606_2():
    
    CombineFiles(["td/t18-raw-5-0-db.fits" , "td/t18-raw-7-0-db.fits"], 
                 "td/t18-comb2.fits")
    
    oofreduce.Red("td/t18-comb2.fits", nzmax=5)    
    oofplot.PlotDir("oofout/t18-comb2-000/z5")
    oofplot.PlotDir("oofout/t18-comb2-000/z3")
    oofplot.PlotDir("oofout/t18-comb2-000/z4")
    

def PlotVersions(ext):
    
    f1=pyfits.open("td/t18-raw-5-3-db.fits")
    f2=pyfits.open("td/t18-raw-5-3-v2-db.fits")
    pylab.clf()
    for f in [f1,f2]:
        x=f[ext].data.field("fnu")
        pylab.plot(x / x.max() )


def prepCheckRelativeAmp(col=5,
                         row=3,
                         poly=False):

    if poly:
        f1name=os.path.join(laptop_dirin, 
                            "tpar18s56s58-apr080854+2006.fits")
        f2name=os.path.join("/home/bnikolic/data/gbt-oof/mustang3/", 
                            "tpar18s56s58-02jul080854+2006.fits")
    else:
        f1name=os.path.join(laptop_dirin, "tpar18s56s58-raw0854+2006.fits")
        f2name=os.path.join("/home/bnikolic/data/gbt-oof/mustang3/", 
                        "tpar18s56s58-raw02jul080854+2006.fits")
    
    mustang.SinglePixelFile(f1name,
                            "temp/t1.fits",
                            col, row)
    mustang.SinglePixelFile(f2name,
                            "temp/t2.fits",
                            col, row)

def plotScaled():
    for f in [pyfits.open("temp/t%i.fits"%i ) for i in [1,2]]:
        fnumax=max([max(f[j].data.field("fnu")) for j in [1,2,3]])
        r=[]
        for j in [1,2,3]:
            r.extend(list(f[j].data.field("fnu")/fnumax ))
        pylab.plot(numpy.array(r))

def vectorise(fnamein):
    time=[]
    fnu=[]
    for h in pyfits.open(fnamein)[1:]:
        dt=h.data.field("time")
        if len(time):
            dt=dt+time[-1]
        time.extend(list(dt))
        fnu.extend(list(h.data.field("fnu")))
    return numpy.array(time),numpy.array(fnu)
    

def CompPixelData(c,r,**kw):
    x1,y1=vectorise("td/t18-raw-5-3-db.fits")
    x2,y2=vectorise("td/t18-raw-%i-%i-db.fits" % (c,r))
    plot("temp/test.eps",[x1,y1,x2,y2],
         xlabel=r"$t$",
         ylabel=r"$f_\nu$",
         **kw
         )

def ObsVsFitGen(dirin):
    obsfilename=oofcol.getpar(dirin,"fitinfo.fits","obsfilename")
    oofreduce.genSimFile(os.path.join(dirin,"fitbeams.fits"),
                         obsfilename,
                         os.path.join(dirin,"simds.fits"), 
                         1,2)

def ObsVsFitPlot(dirin,simdir=None,**kw):
    if simdir is None:
        simdir=dirin
    obsfilename=oofcol.getpar(dirin,"fitinfo.fits","obsfilename")
    x1,y1=vectorise(obsfilename)
    x2,y2=vectorise(os.path.join(simdir,"simds.fits"))
    diff(None,y1,y2,
         os.path.join(dirin,"plots","obsvsfit.eps"),
         xlabel=r"$t$",
         ylabel=r"$f_\nu$",
         **kw
         )
def RelativeAmp(fname):
    f=pyfits.open(fname)
    cf= max(f[2].data.field("fnu"))
    print max(f[1].data.field("fnu"))/cf
    print max(f[3].data.field("fnu"))/cf

def CombineGood():
    goodpix= [ (5,3),
               (5,1),
               (4,6)]
    mustang.CombineFiles(["td/t18-raw-4-6-db.fits","td/t18-raw-5-1-db.fits" , "td/t18-raw-5-3-db.fits"], "td/t18-comb4.fits")




def doTwoPix(c,r):
    """
    Compute a pixel with pixel 5,3 and compute the phase map
    """
    obsfname="td/comb-2px-%i-%i.fits" % (c,r)
    mustang.CombineFiles(["td/t18-raw-%i-%i-db.fits" %(c,r), "td/t18-raw-5-3-db.fits"],
                         obsfname)
    dirout=oofreduce.Red(obsfname, nzmax=5)    
    oofplot.PlotDir(os.path.join(dirout,"z5"))
    shutil.copy(os.path.join(dirout,"z5","plots","aperture-phase.png"),
                "temp/comb-2px/p%i%i-z5.png" % (c,r))

def doAllTwoPix():
    for c,r in MustangPL():
        try:
            doTwoPix(c,r)
        except IOError, e:
            print "not processed"
    
    
    
    


#oofreduce.RedOrder("td/t18-raw-5-3-db.fits", "oofout/test1", zorder=4, ic="oofout/t18-raw-5-3-db-003/z3/fitpars.fits", multiamp=True, nofit=["amp_r1", "amp_r2"])
