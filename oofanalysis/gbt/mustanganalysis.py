"""
Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>

More analalysis of Mustang data
"""

import os

import oofreduce
import oofplot

import mustang




def PrepSinglePixelData(fnamein,
                        col,row,
                        do90=False):

    ffout="td/px-%i-%i.fits"% (col,row)
    mustang.SinglePixelFile(fnamein,
                            ffout,
                            col, row)    
    mustang.RemoveStartEnd(ffout, ffout)
    mustang.CorrectDZ(ffout)    
    if do90:
        mustang.SetTelsc(ffout,"90GBT")




    
