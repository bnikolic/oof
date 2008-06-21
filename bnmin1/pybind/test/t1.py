# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Illustration of using metropolis sampling form bnmin1

import setup
import pybnmin1

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

