# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# October 2007
#
# Further tests on the structure function of generated turbulence,
# concentrating on the edge effects

import numarray
import numpy

from setup import *

import pybnlib
import kolmogorovutils

def CubeStructure(cuben,
                  samples,
                  pairl,
                  opts=pybnlib.KInitialEFB):

    "Compute structure function on many realisations of small cubes"

    """
    e.g. sue:
    a=CubeStructure( 5, 100,   [ [ [2,2,4] , [2,2,0] ], [ [2,4,2], [2,0,2] ] ] )
    """

    res=[]

    for seed in range(1,samples):
        g=kolmogorovutils.GridToNumarray(kolmogorovutils.GenerateKolmogorov3D(cuben,cuben,cuben,
                                                                              seed,
                                                                              opt=opts))
        r = []
        for (p1, p2) in pairl:
            r.append( (g[ p1[0],p1[1],p1[2] ] - g[ p2[0],p2[1],p2[2] ] ) **2)
        res.append(r)

    return numpy.array(res)

def EdgeCorner(cuben, samples):

    edgecl =  [ [ [0,0,0 ]  , [cuben-1,0,0 ] ],
                [ [0,0,0 ]  , [0 , cuben-1,0 ] ] ,
                [ [0,0,0 ]  , [0 , 0, cuben-1 ] ],
                [ [cuben-1,cuben-1,cuben-1 ] , [0,cuben-1,cuben-1 ]] ,
                [ [cuben-1,cuben-1,cuben-1 ] , [cuben-1,0 ,cuben-1 ]] ,
                [ [cuben-1,cuben-1,cuben-1 ] , [cuben-1,cuben-1,0 ]] ,                
                ]

    return CubeStructure( cuben, samples, edgecl )

def FaceCorner(n, samples):

    l = [ [ [0,0,0 ], [n-1, n-1, 0] ],
          [ [0,0,0 ], [n-1, 0 , n-1] ],
          [ [0,0,0 ], [0, n-1, n-1] ]         
          ]
    return CubeStructure( n, samples, l )

def BodyCorner(n, samples):

    l = [ [ [0,0,0] , [n-1,n-1,n-1] ] ,
          [  [n-1,0,0] , [0,n-1,n-1] ]
          ]

    return CubeStructure( n, samples, l )    
        
           
         
def FaceStruct(n, samples):

    h=n/2
    n1=n-1

    l = [ [ [h,h,n1] , [h,h,0] ],
          [ [h,n1,h] , [h,0,h] ]
          ]
    return CubeStructure( n, samples, l )

def CornerToFace(n , samples):
    
    h=n/2
    n1=n-1

    l = [ [ [0,0,0] , [h,h,0] ],
          [ [n1,n1,n1] , [h,h,n1] ],
          ]
    return CubeStructure( n, samples, l )

def CentreToFace(n , samples):

    h=n/2
    n1=n-1

    l = [ [ [h,h,h] , [h,h,0] ],
          [ [h,h,h] , [h,h,n1] ],
          ]
    return CubeStructure( n, samples, l )

def CornerToFirst(n, samples):

    l = [ [ [0,0,0] , [0,0,1]],
          [ [0,0,0] , [0,1,0]],
          [ [0,0,0] , [1,0,0]]]

    return CubeStructure( n, samples, l )

def CentreStruct(n , samples):

    h=n/2
    n1=n-1

    l = [ [ [0,0,0] , [h,h,h] ]
          ]
    return CubeStructure( n, samples, l )

#expect: 6.88 * ( (0.25*3)**0.5)**(2.0/3) == 6.2508948393425605


def FaceQStruct(n , samples):

    q = n/4
    h = n/2

    l = [ [ [h,h, h+q] , [h,h,h-q] ]
          ]
    return CubeStructure( n, samples, l )
    
def FaceToFace(n, samples,
               **kwargs):

    l=[]
    for i in range(n):
        for j in range(n):
            l.append( [ [i,j,0] , [i,j,n-1] ] )
    
    return CubeStructure( n, samples, l ,
                          **kwargs)



def PlotSTest(a):

    x=numpy.mean(a, axis=0)
    x.shape=( int(len(x)**0.5), int(len(x)**0.5) )
    pylab.matshow(x)
    pylab.colorbar()
