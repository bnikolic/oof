# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# October 2007
#
# Further tests on the structure function of generated turbulence,
# concentrating on the edge effects

import numarray

from setup import *

import kolmogorovutils

def FaceStructure(n=100):
    res=[]
    for seed in range(1,n):
        g=kolmogorovutils.GridToNumarray(kolmogorovutils.GenerateKolmogorov3D(5,5,5, seed  ))

        s1= (g[2,2,4]- g[2,2,0])**2
        s2= (g[2,4,2]- g[2,0,2])**2
        res.append(s1)
        res.append(s2)
    return numarray.array(res)

def EdgeStructure(n=1000):
    res=[]
    for seed in range(1,n):
        g=kolmogorovutils.GridToNumarray(kolmogorovutils.GenerateKolmogorov3D(5,5,5, seed  ))

        s1= (g[2,0,4]- g[2,0,0])**2
        s2= (g[2,4,0]- g[2,0,0])**2
        res.append(s1)
        res.append(s2)
    return numarray.array(res)

        






