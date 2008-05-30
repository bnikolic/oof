# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Uitlities for the minimisation/likelihood routines

import numpy

def ChainToArray(c):
    """Extract points from a chain and return as numpy array"""
    res=numpy.zeros( (len(c), len(c[0].p) ))
    for i,x in enumerate(c):
        res[i]=x.p
    return res
    
    
