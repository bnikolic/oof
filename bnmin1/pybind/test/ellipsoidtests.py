import numpy
import numpy.linalg
import pylab

import sys
sys.path.insert(0, "/home/bnikolic/n/prog/main/bnmin1/pybind/bin/")
import localsetup

import pybnmin1

def mkSet(pl):
    res=pybnmin1.SetMC()
    for i,p in enumerate(pl):
        pp=pybnmin1.MCPoint()
        pp.p=pybnmin1.DoubleVector(p)
        pp.ll=i
        res.append(pp)
    return res

def randomSet(d, n):
    return mkSet(numpy.random.uniform(low=0.2, 
                                      high=0.3,
                                      size=(n,d)))
    
                  
#ss=mkSet([ [1,1], [-1, -1], [1,-1],[-1,1], [0,0], [0.1, 0.1]])        
ss=randomSet(3, 100)
res=pybnmin1.KhachiyanEllipsoid()
pybnmin1.KhachiyanAlgo(ss, 0.1, 50, res)
rg=pybnmin1.mt19937()

ns=pybnmin1.EllipsoidSampler(res.Q,
                             res.c,
                             rg)

def plotns(ns):
    pylab.clf()
    xx=pybnmin1.DoubleVector(2)
    rx, ry = [] ,[] 
    for i in range(1000):
        ns(xx)
        rx.append(xx[0])
        ry.append(xx[1])
    pylab.scatter(rx, ry)

    





