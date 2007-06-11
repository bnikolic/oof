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
        if c >= N:
                break
        x = numarray.zeros(len(poly) )
        x[i]=1
        rhs[c]=(poly*x).sum()**2
        FillMtrxRow( a, x, c)
        c+=1

    for i in range(n):
        if c >= N:
            break
        for j in range (i+1,n) :
            x = numarray.zeros(n )
            x[i]=1
            x[j]=2
            rhs[c]=(poly*x).sum()**2
            FillMtrxRow( a, x, c)
            c+=1
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
                     klaw=PlainKolmogorovSpec2D):

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

    print solution
    
    # distances between the supplied points
    parentdists=PairDists(parlist)

    varlist=[ klaw(x) for x in parentdists]
    varlist=numarray.array(varlist)


    interpvar= (varlist*solution).sum()

    print "Variance of the interpolated point:", interpvar

    p1toposdist= ((parlist[0]-pos)**2).sum() **0.5
    print  p1toposdist
    requiredvar = klaw( p1toposdist)

    print requiredvar

    return requiredvar -interpvar
    
    

    
    

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


def Corner3D():

    "Calculate the variances for the corner point generation"

    a = [ [ 2, 3.0/2 , 0.5 ],
          [ 2, 2.0   , 0.5 ],
          [ 2, 3.0/2 ,  1  ]]
    a=numarray.array(a)
    f=PlainKolmogorovSpec2D

    r=numarray.array( [ f(1), f(2.0**0.5), f(3.0**0.5)])
    print r
    return la.solve_linear_equations(a,r)

def Corner3DV2():

    "Experimetal -- look for better initialisation"

    a = [ [ 2, 3.0/2 , 0.5 ],
          [ 2, 3.0   , 0.5 ],
          [ 0, 3.0/2 ,  1  ]]
    a=numarray.array(a)
    f=PlainKolmogorovSpec2D

    r=numarray.array( [ f(1), f(2.0**0.5), f(3.0**0.5)])
    print r
    return la.solve_linear_equations(a,r)


def RotateList(l):

    return [l[-1]]+l[:-1]

def CubeFaceDiagonals():

    res = []
    for k in [0,1]:
        res.append( [ [0,0,k] , [1,1,k] ])
        res.append( [ [1,0,k] , [0,1,k] ])

    for r in [0,1]:
        for j in range(4):
            res.append( [ RotateList(res[j+r*4][i]) for i in [0,1] ])

    return res

    
        
def PrintCubeFaceDiagonals():

    fd= CubeFaceDiagonals()

    for x in fd:
        print "{ %i, %i, %i,  %i, %i, %i }, " % (
            tuple(x[0]+x[1]))

    

    
