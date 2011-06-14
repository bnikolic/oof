# Bojan Nikolic <bojan@bnikolic.co.uk>
# Initial version 2009
#
# This file is part of BNMin1 and is licensed as described in file
# COPYING
"""
Higher level wrappers for the nested sampling routines
"""
import math

import numpy
import pybnmin1
    
def applyFlatPrior(m, pr):
    """
    Apply priors to an observational data set + model to get a
    complete hypothesis that can be analysed
    
    :param pr: Priors as a dictionary 

    """
    m.thisown=False
    po=pybnmin1.IndependentFlatPriors(m)
    mm=pybnmin1.ModelDesc(m)
    for i in range(mm.NParam()):
        pname=mm.getbynumb(i).name
        po.AddPrior(pname, pr[pname][0], pr[pname][1])
    return po


def setRandomIStrat(mm,
                    n_ss):
    """
    Set the initial point strategy to random from live set
    """
    istrat=pybnmin1.InitialRandom(n_ss)
    istrat.thisown=False
    mm.InitalS(istrat)
    
def doSample(po,
             ns,
             n_ss=200,
             ellipsoid=False):
    """
    Carry out nested sampling
    """
    ss=pybnmin1.ListDV()
    pybnmin1.startSetDirect(po,
                            n_ss,
                            ss)
    mm=pybnmin1.NestedS(po,
                        33)
    if ellipsoid:
        cps=pybnmin1.EllipsoidCPSampler(po, mm)
        cps.thisown=False
        cps.reshape_maxp=50
        mm.reset(ss, cps)
        cps.reshape()
        if 0:
            pp=pybnmin1.SOutMCMon();
            pp.thisown=False
            mm.mon=pp;
            cps.mon=pp;
    else:
        mm.reset(ss)
        setRandomIStrat(mm,
                        n_ss)

    Z=mm.sample(ns)
    print "Evidence: ", Z
    ns_act=len(mm.g_post())
    if ns_act != ns:
        print "Warning: terminated early after %i/%i samples" % (ns_act, 
                                                                 ns)
        lp=mm.g_post()[-1]
        print "     Evidence contribution of last sample %g " % (lp.w * math.exp(-lp.ll))
    return mm

def moments(mm):
    """
    Return the moments for each of the parameters in the nested
    sampler
    """
    return momentsRaw(mm.g_post(), mm.Z())

def momentsRaw(post,
               Z):
    """
    :param post: The list containing the posterior distribution
    :param Z: The evidence value
    """
    res=[]
    m1=pybnmin1.DoubleVector()
    m2=pybnmin1.DoubleVector()
    pybnmin1.moment1(post, 
                     Z, m1)
    pybnmin1.moment2(post, 
                     m1, Z, 
                     m2)
    for i in range(len(post[0].p)):
        res.append( (m1[i], m2[i]) )
    return res


def jointHist(mm,
              pranges,
              nbins=50):
    """
    Compute the histogram of the joint posterior distribution
    
    :param pranges: A dictionary on parameter name, defining the box
    over which to histogram the posterior

    :returns: n-dimensional array containing the histogram

    """
    res=pybnmin1.DoubleVector()
    l, h=[] , []
    for i in range(mm.NParam()):
        pname=mm.getbynumb(i).name
        plow,phigh = pranges[pname]
        l.append(plow)
        h.append(phigh)
        
    pybnmin1.postHist(mm.g_post(),
                      mm.Z(),
                      l, 
                      h,
                      nbins,
                      res)
    res=numpy.array(res)
    res.shape=[nbins]*len(pranges)
    return res
                      
        

