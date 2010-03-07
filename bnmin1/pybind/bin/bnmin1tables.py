# Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
# Initial version March 2010
#
# This file is part of BNMin1 package and is licensed under GPL V2
"""
Input and output of the BNMin1 data structures to the HDF5 file format
"""

from tables import *

import bnmin1utils

def mkNestedTableDef(mm):
    """
    Create the definition for storing the posterior distribution of
    the nested sampler
    """
    res={}
    for i in range(mm.NParam()):
        pname=mm.getbynumb(i).getname()
        pcom=mm.getbynumb(i).getcomment()
        res[pname]=Float64Col(pos=i)
    return res
    
    


