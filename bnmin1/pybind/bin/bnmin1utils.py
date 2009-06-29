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

def sChainToArray(c):
    """Like ChainToArray but avoid exception based code

    This works around bugs introduced by multiple modules and swig.
    """
    n=len(c)
    res=numpy.zeros((n, len(c[0].p)))
    li=c.iterator()
    for i in range(n):
        if i is not 0:
            li.incr()
        res[i]=li.value().p
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
    """ Set the parameters of a model from a list
    
    If model has an attribute "downcast", this is called as a function
    to cast the model to a form suitable for ModelDesc class (this
    eases cross-module integration with bnmin1).

    """
    if getattr(m, "downcast", False):
        mod = pybnmin1.ModelDesc(m.downcast())
    else:
        mod = pybnmin1.ModelDesc(m)
    for i,x in enumerate(ic):
        mod.getbynumb(i).setp(x)

def ParDict(m):
    """Return parameters of the model as a dictionary"""
    if getattr(m, "downcast", False):
        md=pybnmin1.ModelDesc(m.downcast())
    else:
        md=pybnmin1.ModelDesc(m)
    d={}
    for i in range(md.NTotParam()):
        p=md.getbynumb(i)
        d[p.name]=p.getp()
    return d

def ParList(m):
    """Return parameters of the model as a dictionary"""
    md=pybnmin1.ModelDesc(m)
    d=[]
    for i in range(md.NTotParam()):
        p=md.getbynumb(i)
        d.append( (p.name,p.getp()))
    return d
    
    
