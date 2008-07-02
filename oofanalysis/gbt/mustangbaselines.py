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

laptop_dirin="/home/bnikolic/data/gbt-oof/mustang2/"


def PrepareInputs(col=5, row=0):

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
        mustang.MaxUFNU(ffout)
        
                            

        
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

def DoAPixel(c,r):
    """
    Process a single pixel and copy the output aperture phase plot to
    temporary directory for visualisation
    """
    PrepareInputs(c,r)
    fnameraw= "td/t18-raw-%i-%i.fits" % (c,r)
    fnamedb = "td/t18-raw-%i-%i-db.fits" % (c,r)
    RemoveBaseline(fnameraw , 
                   fnamedb,
                   rad=1.5e-4 )        
    oofreduce.Red(fnamedb, nzmax=5)

    for z in [3,5]:

        oofplot.PlotDir("oofout/t18-raw-%i-%i-db-000/z%i" % (c,r,z))
        shutil.copy( "oofout/t18-raw-%i-%i-db-000/z%i/plots/aperture-phase.png" % (c,r,z),
                     "temp/plots/p%i%i-z%i.png" % (c,r,z))
    
def DoAllPixels():
    """
    Extract all pixels individually, process to z=5, plot and copy
    plots to a directory
    
    See also DoAPixel
    """
    for c,r in MustangPL():
        try:
            DoAPixel(c,r)
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
    
