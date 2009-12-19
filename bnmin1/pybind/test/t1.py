# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Illustration of using metropolis sampling form bnmin1

import numpy


import localsetup
import pybnmin1
import bnmin1utils

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



xvals=numpy.random.normal(size=50)
yvals=xvals+numpy.random.normal(0,0.1, size=50)
l=pybnmin1.LineLkl(xvals, yvals, 1.0, 0.1)
l.x0=0
l.y0=0
l.Rx=1
l.Ry=1
