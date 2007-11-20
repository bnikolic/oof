# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Initial version 2007
#
# Test for changes in output of Kolmogorov code

import unittest
import pickle
import numarray

from setup import *

import kolmogorovutils
import pybnlib

def GenTestK(n):
    return kolmogorovutils.GridToNumarray(kolmogorovutils.GenerateKolmogorov3D(n,n,n,
                                                                               99))

def GenTestK_Balanced(n):
    opts=pybnlib.KInitialEFB + pybnlib.KBalancedIters+ pybnlib.KEdgeBalanced
    c=kolmogorovutils.GenerateKolmogorov3D(n,n,n,
                                           99,
                                           opts)
    return kolmogorovutils.GridToNumarray(c)

class TestK3Changes(unittest.TestCase):

    testdataname= "data/k3changes_9.p"
    testbalancedname = "data/k3changes_9_bal.p"

    def testCubeChange(self):

        a= pickle.load( open(self.testdataname))
        x=GenTestK(9)

        t= numarray.all(a==x)

        self.assert_ ( t)

    def testBalancedChange(self):

        a= pickle.load( open(self.testbalancedname))
        x=GenTestK_Balanced(9)

        t= numarray.all(a==x)
        self.assert_ ( t)

    def testBalancedDefault(self):

        a= GenTestK(9)
        b= GenTestK_Balanced(9)

        t= numarray.all(a==b)
        self.assert_ ( not t)
        
        



if __name__ == '__main__':
    unittest.main()
    pass
