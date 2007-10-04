# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# June 2007
#
# Test the three dimensional corner geration function


import sys ; sys.path.extend(["/home/bnikolic/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

import numarray

import pybnlib

rfn=pybnlib.NormDistZM(1.0)

def DrawCorners(N=3,ver="V1"):
    cube= pybnlib.doubleArray( N**3)
    for i in range(N**3):
        cube[i]=0
    if ver == "V1":
        pybnlib.KolmogorovCorners3D( cube, N, rfn)
    elif ver == "V2":
        pybnlib.KolmogorovCorners3DV2( cube, N, rfn)
    else:
        raise "Unkown version"
    
    return cube

def Sfn( c1, c2, ver="V1", samples=10000):

    r=[]
    for sno in range(samples):
        c=DrawCorners(3,ver=ver)
        r.append( (c[c1] - c[c2])**2)

    r=numarray.array(r)
    return r.mean(), (r.stddev() / samples**0.5)

def PlainKolmogorovSpec2D(x):

    return 6.88 * (x)**(2.0/3)


def DoCompare(ver="V1"):

    print "*** edge : expect,  " , PlainKolmogorovSpec2D( 1)
    print "    Got : %f " % ( Sfn( 0 , 2, ver=ver )[0] )
    print "    Got : %f " % ( Sfn( 6 , 8, ver=ver )[0] )
    print "    Got : %f " % ( Sfn( 24 , 26, ver=ver )[0] )
    
    print "*** face diagonal: expect,  " , PlainKolmogorovSpec2D( 2.0**0.5)
    print "    Got : %f " % ( Sfn( 0 , 8, ver=ver )[0] )
    print "    Got : %f " % ( Sfn( 18 , 26, ver=ver )[0] )    

    print "*** body diagonal: expect,  " , PlainKolmogorovSpec2D( 3.0**0.5)
    print "    Got : %f " % ( Sfn( 0 , 26, ver=ver )[0] )    

    

