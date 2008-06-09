# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Uitlities for the minimisation/likelihood routines

import numpy

import pybnmin1

def ChainToArray(c):
    """Extract points from a chain and return as numpy array"""
    res=numpy.zeros( (len(c), len(c[0].p) ))
    for i,x in enumerate(c):
        res[i]=x.p
    return res

def ChainToLkl(c):
    """Extract the likelihoods from a chain"""
    res=numpy.zeros( len(c))
    for i,x in enumerate(c):
        res[i]=x.ll
    return res    

def ChainMostLkl(c):
    """Return the parameters of the most likely point of the chain"""
    l=ChainToLkl(c)
    return list(c[l.argmax()].p)


def SetIC(m,ic):
    """ Set the parameters of a model from a list"""
    mod = pybnmin1.ModelDesc(m.downcast())
    for i,x in enumerate(ic):
        mod.getbynumb(i).setp(x)
    
    
