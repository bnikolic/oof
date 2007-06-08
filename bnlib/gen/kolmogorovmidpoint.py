# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007
#
# Cacluate required scalings for mid point displacements when
# generating three dimensional Kolmogorov turbulence.
#
# Some code moved here from bnlib/pybind/test/threedimturbulence.py

import math

import numarray
import numarray.linear_algebra as la

def JKtoi(J,K,N):

    """
    Defines the ordering of pairs from the squaring into
    one-dimensional sequence. E.g.:

    (3a -b -c -d )
     ^   ^
     J=0 K=1

     so (a-b)^2 is the J=0, K=1, pairing.

     Calculated by simple application of arithmetic progression.

    """

    return J*(N-2) - J*(J-1)/2 + K -1


def GenLinSystem(poly):

    """
    Generates the linear system which allows factorisation of
    something like:

    (a1 * a+ a2 *b + a3 *c ....) ^2 into:
    c1(a-b)^2 + c2(a-c)^2

    For the two dimensional bilinear interpolator, get something like:

    p2 = numarray.array([3,-1,-1,-1])

    which may be solved by:
    a,r=GenLinSystem(p2)
    la.solve_linear_equations(a,r)

    """

    n=len(poly)

    def FillMtrxRow(a,x, c):
        for J in range(0,n-1):
            for K in range(J+1,n):
                k = JKtoi(J,K,n)
                a[c,k] = (x[J] - x[K]) **2
    
    # number of pairings
    N=n*(n-1) /2 
    rhs = numarray.zeros(N ,numarray.Float64)
    a   = numarray.zeros( ( N,N) ,numarray.Float64)
    c= 0

    # Generate the constraings by substitution into the defining
    # equations... Not very clever but should work sufficiently well.
    for i in range(n):
        x = numarray.zeros(len(poly) )
        x[i]=1
        rhs[c]=(poly*x).sum()**2
        FillMtrxRow( a, x, c)
        c+=1

    for i in range(n):
        for j in range (i+1,n) :
            x = numarray.zeros(n )
            x[i]=1
            x[j]=2
            rhs[c]=(poly*x).sum()**2
            FillMtrxRow( a, x, c)
            c+=1
            if c >= N:
                break
        if c >= N:
            break
    return a, rhs


def PairDists(parlist):

    """
    Return distances betweene each distinct pair of supplied points
    """
    n=len(parlist)
    parentdists=[]
    for i in range(0,n-1):
        for j in range(i+1,n):
            parentdists.append( ((parlist[i]-parlist[j])**2).sum()**0.5)

    return parentdists

def PlainKolmogorovSpec3D(x):

    return 6.88 * (x)**(5.0/3)

def PlainKolmogorovSpec2D(x):

    return 6.88 * (x)**(2.0/3)

def MidPointVariance(pos, parlist,
                     klaw=PlainKolmogorovSpec3D):

    "Calculate the variance due to interpolation to form the mid-point"

    """
    parlist : parent list
    """

    # distances pos
    n=len(parlist)
    d= [ ((pos-x)**2).sum()**0.5 for x  in parlist ]
    d=numarray.array(d)
    # Weights that make up the linear interpolation
    w = d/d.sum()

    poly = numarray.zeros(n, numarray.Float64)
    poly[0] = 1
    poly -= w


    a,r=GenLinSystem(poly)
    # This is the factorisation which allows to directly substitude
    # the defining structure function into the equations.
    solution=la.solve_linear_equations(a,r)

    
    # distances between the supplied points
    parentdists=PairDists(parlist)

    varlist=[ klaw(x) for x in parentdists]
    varlist=numarray.array(varlist)


    return (varlist*solution).sum()
    
    

    
    

c1= numarray.array( [0.5, 0.5, 0])
pl= numarray.array( [ [1, 0, 0],
                      [1, 1, 0],
                      [0, 1, 0],
                      [0, 0, 0]])

c2= numarray.array( [0.5, 0.5, 0.5])
pl2= numarray.array( [ [1, 0, 0],
                      [1, 1, 0],
                      [0, 1, 0],
                      [0, 0, 0],
                      [1, 0, 1],
                      [1, 1, 1],
                      [0, 1, 1],
                      [0, 0, 1]
                      ])


