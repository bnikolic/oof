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
             n_ss=200):
    """
    Carry out nested sampling
    """
    ss=pybnmin1.ListDV()
    pybnmin1.startSetDirect(po,
                            n_ss,
                            ss)
    mm=pybnmin1.NestedS(po,
                        33)
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
    res=[]
    m1=pybnmin1.DoubleVector()
    m2=pybnmin1.DoubleVector()
    pybnmin1.moment1(mm.g_post(), mm.Z(), m1)
    pybnmin1.moment2(mm.g_post(), m1, mm.Z(), m2)
    for i in range(mm.NParam()):
        res.append( (m1[i], m2[i]) )
    return res
        

