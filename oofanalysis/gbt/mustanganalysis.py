"""
Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>

More analalysis of Mustang data
"""

import os

import setup

import oofreduce
import oofplot

import mustang

def PrepSinglePixelData(fnamein,
                        col,row,
                        post="",
                        do90=False):

    ffout="td/px-%i-%i-%s.fits"% (col, row, post)
    mustang.SinglePixelFile(fnamein,
                            ffout,
                            col, row)    
    mustang.RemoveStartEnd(ffout, ffout)
    mustang.CorrectDZ(ffout)    
    if do90:
        mustang.SetTelsc(ffout,"90GBT")

def MkTPar18SinglePx(col,row,
                     qd=False,
                     reddate="21nov08",
                     datain="/home/bnikolic/data/gbt-oof/mustang4/"):
    if qd:
        post="qd"
    else:
        post="noqd"
    fnamein=os.path.join(datain,
                         "tpar18s56s58-%s-p12-%s0854+2006.fits" %(reddate,
                                                                  post))
    PrepSinglePixelData(fnamein,
                        col,
                        row,
                        post=post,
                        do90=True)

    
                        
    
    
    
    




    
