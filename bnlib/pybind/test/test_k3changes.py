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

def GenTestK(n):
    return kolmogorovutils.GridToNumarray(kolmogorovutils.GenerateKolmogorov3D(n,n,n,
                                                                               99))

class TestK3Changes(unittest.TestCase):

    testdataname= "data/k3changes_9.p"

    def testCubeChange(self):

        a= pickle.load( open(self.testdataname))
        x=GenTestK(9)

        t= numarray.all(a==x)

        self.assert_ ( t)
        



if __name__ == '__main__':
    unittest.main()
    pass
