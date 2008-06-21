# Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
# Unit testing of python bindings of BNMin1 library

import unittest
import math

import setup
import pybnmin1

class TestFlatPriors(unittest.TestCase):
    """Tests the Flat priors code"""

    def testInit(self):
        """Test that we can initialse the prior routine"""
        qm=pybnmin1.QuadModel()
        x = pybnmin1.DoubleVector([-1,0,1])
        obs=pybnmin1.DoubleVector([1,1,1])
        qo= pybnmin1.QuadObs  (x,obs)
        qo.thisown=False
        qifp=pybnmin1.IndependentFlatPriors(qo)

    def testEdge(self):
        """Test that including prior correctly forces minimisation to the edge
        of prior if max likelihood is clearly outside the prior"""
        pars= [1,2,3]
        qm=pybnmin1.QuadModel()
        qm.a, qm.b, qm.c = pars
        x=pybnmin1.DoubleVector( [ 0,1,2])
        obs=pybnmin1.DoubleVector(3)
        qm.eval(x, obs);
        qo= pybnmin1.QuadObs  ( x,obs);
        qo.sigma=0.01
        qo.thisown=False
        qifp=pybnmin1.IndependentFlatPriors(qo)        
        qifp.AddPrior("c", -10, 2)
        sigmas=pybnmin1.DoubleVector(3, 0.1)
        metro=pybnmin1.MetropolisMCMC(qifp,sigmas);
        res= metro.sample(10000)
        self.assert_( math.fabs(res[-1].p[2] -2) < 0.1)
        
if __name__ == '__main__':
    unittest.main()
    pass

        
        
        
        
        
