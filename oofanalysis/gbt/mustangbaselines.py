# Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
#
# Initial version May 2008
#
# Investigate effects on Mustang data

import os

import setup

import pyfits
import iofits4

import mustang
import baselinealgo

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
                            

        
def RoughReduce():

    oofreduce.Red("td/t18-poly-5-0.fits")
    oofplot.PlotDir("oofout/t18-poly-5-0-000/z1")
    RemoveBaseline("td/t18-poly-5-0.fits", "td/t18-poly-5-0-db.fits")
    oofreduce.Red("td/t18-poly-5-0-db.fits")

    if 0:
        oofreduce.Red("td/t18-raw-5-0.fits")
        oofplot.PlotDir("oofout/t18-raw-5-0-000/z1")

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
        
        h.data = pyfits.FITS_rec(h.data[mask])
        for i,f in enumerate( fnu[numpy.array(mask)] ):
            h.data.field("fnu")[i]=float(f)
        res.append(h)
            
    iofits4.Write(res,
                  fnameout,
                  overwrite=1)    



