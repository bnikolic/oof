# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# November 2007
#
# Unit testing for kolmogorov turbulence

import unittest
import numpy


import k3d_structretest

class Test3dStructureFn(unittest.TestCase):

    "Tests of 3-d kolmogorov turbulence generation"

    def setUp(self):
        self.maxCornerErr= 0.05
        self.ncubeCorner = 3000

        self.SfnSamples=3000

    def Check(self, a, expectval, f_tol):

        f_e = max(abs(numpy.mean(a, axis=0 )  - expectval)) / expectval
        self.assert_( f_e  <  f_tol )
        
    def CornerCheck(self, a , expectval ):
        # fractional error
        return self.Check( a, expectval, self.maxCornerErr )


    def testEdgeCorner(self):
        
        a=k3d_structretest.EdgeCorner(3, self.ncubeCorner)
        self.CornerCheck( a, 6.88)
        
    def testFaceStruct(self):

        a=k3d_structretest.FaceStruct(5, self.SfnSamples)
        self.Check(a, 6.88, 0.2)

        a=k3d_structretest.FaceQStruct(5, self.SfnSamples)
        self.Check(a, 6.88 * (2.0/3)**2, 0.2)

        
        
        
    
    
if __name__ == '__main__':
    unittest.main()
    pass
