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

def CJKtoi(J,K,N):
    return J*(N-2) - J*(J-1)/2 + K -1

def PJKtoi(J,K,N):
    return (2*J*N - J*J - J) / 2 +K 
    
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

    # number of pairings
    NC=n*(n-1) /2
    NP=n*(n+1) /2

    # The linear system
    rhs = numarray.zeros(NP ,
                         numarray.Float64)
    a   = numarray.zeros( ( NP,NC) ,
                          numarray.Float64)

    for i in range(0, n-1):
        for j in range (i+1, n):
            cdx = CJKtoi(i,j,n)
            a[ PJKtoi(i,i,n) , cdx ] =1
            a[ PJKtoi(i,j,n) , cdx ] =-2
            a[ PJKtoi(j,j,n) , cdx ] =1

    # right hand side
    for i in range(0, n):
        for j in range (i, n):
            pdx=PJKtoi(i,j,n)
            if i == j:
                rhs[pdx]= poly[i]**2
            else:
                rhs[pdx]= 2 * poly[i] * poly[j]

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
    solution=la.linear_least_squares(a,r)[0]

    # distances between the supplied points
    parentdists=PairDists(parlist)

    varlist=[ klaw(x) for x in parentdists]
    varlist=numarray.array(varlist)


    interpvar= (varlist*solution).sum()


    p1toposdist= ((parlist[0]-pos)**2).sum() **0.5

    requiredvar = klaw( p1toposdist)


    return requiredvar -interpvar
    

def MidPointRot( pos, parlist , **kwargs):

    "Rotate the parlist to ensure optimum solution"

    """
    Need to have this to deal with non-equal-distant interpolation
    """

    res = []
    parlist= parlist.tolist()
    
    for i in range(len(parlist)):
        r=MidPointVariance(pos, numarray.array(parlist), **kwargs)
        res.append(r)
        parlist= [list(parlist[-1])]+parlist[0:-1]

    return res
        
c8= numarray.array( [0.5, 0.5, 0.5])
p8= numarray.array( [ [1, 0, 0],
                      [1, 1, 0],
                      [0, 1, 0],
                      [0, 0, 0],
                      [1, 0, 1],
                      [1, 1, 1],
                      [0, 1, 1],
                      [0, 0, 1]
                      ])
    

fc6 = numarray.array( [0.5, 0.5, 1])
fp6 = numarray.array( [ [0.5, 0.5, 0.5],
                        [0, 0, 1],
                        [0, 1, 1],
                        [1, 0, 1],
                        [1, 1, 1],
                        [0.5, 0.5, 1.5] ])

fc5 = numarray.array( [0.5, 0.5, 1])
fp5 = numarray.array( [ [0.5, 0.5, 0.5],
                        [0, 0, 1],
                        [0, 1, 1],
                        [1, 0, 1],
                        [1, 1, 1] ])

    
def ShowRequiredVariances():

    "Print the required variances for the 3d kolmogorov case"

    print "Normal eight parents at vertices of the cube"

    print 8 , MidPointVariance( c8, p8)**0.5

    print "Normal six parent for face iterator"


    print 6,  MidPointVariance( fc6, fp6)**0.5

    print "Face iterator, five parent"
    print 5,  MidPointVariance( fc5, fp5)**0.5

    print "Face iterator, four parent"
    fc4 = numarray.array( [0.5, 0.5, 1])
    fp4 = numarray.array( [ [0, 0, 1],
                            [0, 1, 1],
                            [1, 0, 1],
                            [1, 1, 1] ])
    print 4,  MidPointVariance( fc4, fp4)**0.5    

    print "Edge iterator : "
    ec6 = numarray.array( [0.5, 1, 1])
    ep6 = numarray.array( [ [0, 1, 1],
                            [1, 1, 1],
                            [0.5, 0.5, 1],
                            [0.5, 1.5, 1],
                            [0.5, 1, 0.5],
                            [0.5, 1, 1.5] ])
    ep5 = numarray.array( [ [0, 1, 1],
                            [1, 1, 1],
                            [0.5, 0.5, 1],
                            [0.5, 1.5, 1],
                            [0.5, 1, 0.5]
                            ])

    ep4 = numarray.array( [ [0, 1, 1],
                            [1, 1, 1],
                            [0.5, 0.5, 1],
                            [0.5, 1, 0.5]
                            ])
    print 6,  MidPointVariance( ec6, ep6)**0.5
    print 5,  MidPointVariance( ec6, ep5)**0.5
    print 4,  MidPointVariance( ec6, ep4)**0.5    
    


    
    
c8= numarray.array( [0.5, 0.5, 0.5])
p8= numarray.array( [ [1, 0, 0],
                      [1, 1, 0],
                      [0, 1, 0],
                      [0, 0, 0],
                      [1, 0, 1],
                      [1, 1, 1],
                      [0, 1, 1],
                    [0, 0, 1]
                      ])

c1= numarray.array( [0.5, 0.5, 0])
pl= numarray.array( [ [1, 0, 0],
                      [1, 1, 0],
                      [0, 1, 0],
                      [0, 0, 0]])




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

def Corner3DV3():

    "Test only"

    # This corresponds to even term on edges and odd terms on face
    # diagonals and body diagonals.
    a = [ [ 1.0  ,     3.0/2 , 1.0/2 ],
          [ 3.0/2, 2.0   , 1.0/2 ],
          [ 3.0/2, 3.0/2 ,  1.0  ]]
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

    
def MatrixToTex(a):

    "Format a matrix for inclusion into Tex"

    rows, cols= a.shape

    print ( r"\begin{array}{%s}" % ( "c" * cols ) )

    for i in range(rows):
        out = ""
        for j in range(cols):
            out += ( " %g " % a[i,j])
            if j != cols-1:
                out +=   "&"
            else:
                out +=   r"\\"
        print out

    print ( r"\end{array}")

def VectorToTex(v):

    print ( r"\begin{array}{c}" )

    for i in range(len(v)):
        print (r"%g \\" % v[i] )

    print ( r"\end{array}")
    
    

            


