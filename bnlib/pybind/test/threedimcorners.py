# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# June 2007
#
# Test the three dimensional corner geration function


import sys ; sys.path.extend(["/home/bnikolic/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

import numarray

import pybnlib

rfn=pybnlib.NormDistZM(1.0)

def DrawCorners(N=3):
    cube= pybnlib.doubleArray( N**3)
    for i in range(N**3):
        cube[i]=0
    pybnlib.KolmogorovCorners3D( cube, N, rfn)
    return cube

def Sfn( c1, c2, samples=10000):

    r=[]
    for sno in range(samples):
        c=DrawCorners(3)
        r.append( (c[c1] - c[c2])**2)

    r=numarray.array(r)
    return r.mean(), (r.stddev() / samples**0.5)

    

