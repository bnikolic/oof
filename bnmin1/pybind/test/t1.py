# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Illustration of using metropolis sampling form bnmin1

import numpy


import localsetup
import pybnmin1
import bnmin1utils
import bnmin1nested

if 0:
    pars= [1,2,3]

    qm=pybnmin1.QuadModel()
    qm.a, qm.b, qm.c = pars

    x=pybnmin1.DoubleVector( [ 0,1,2])
    obs=pybnmin1.DoubleVector(3)

    qm.eval(x, obs);

    qo= pybnmin1.QuadObs  ( x,obs);
    qo.sigma=0.01

    sigmas=pybnmin1.DoubleVector(3, 0.1)

    metro=pybnmin1.MetropolisMCMC(qo,sigmas);

    res= metro.sample(10000)

    print res[-1]


if 1:
    xvals=numpy.arange(-2, 2, 0.05)
    yvals=xvals
    xvals+=numpy.random.normal(0, 0.1, size=len(xvals))
    yvals+=numpy.random.normal(0, 0.1, size=len(xvals))
    l=pybnmin1.LineLkl(xvals, yvals, 0.1, 0.1)
    l.x0=0
    l.y0=0
    l.Rx=0
    l.Ry=0

if 0:
    metro=pybnmin1.MetropolisMCMC(l,[0.1, 0.1, 0.1, 0.1]);
    res= metro.sample(1000000)
    xx=bnmin1utils.ChainToArray(res)

if 1:
    mm=bnmin1nested.applyFlatPrior(l, 
                                   {"x0": (-1, 1),
                                    "y0": (-1, 1),
                                    "Rx": (-1, 2),
                                    "Ry": (-1, 2)})
    xx=bnmin1nested.doSample(mm, 100000)


