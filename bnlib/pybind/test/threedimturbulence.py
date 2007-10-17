# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007
#
# Investigate how to do three dimensional turbulence by the mid-point
# displacement method.

import math

from setup import *

import vtk
from vtk.util.colors import *

import pybnlib

import numarray
import numarray.linear_algebra as la

def MkCube( cx, cy, cz, l ):
    CubeModel = vtk.vtkCubeSource()
    CubeModel.SetCenter(cx, cy ,cz)
    CubeModel.SetXLength(l)
    CubeModel.SetYLength(l)
    CubeModel.SetZLength(l)
    return CubeModel

def Edges(cm,
          cl=khaki):

    Edges = vtk.vtkExtractEdges()
    Edges.SetInputConnection(cm.GetOutputPort())
    Tubes = vtk.vtkTubeFilter()
    Tubes.SetInputConnection(Edges.GetOutputPort())
    Tubes.SetRadius(.01)
    Tubes.SetNumberOfSides(6)
    Tubes.UseDefaultNormalOn()
    Tubes.SetDefaultNormal(.577, .577, .577)
    # Create the mapper and actor to display the cube edges.
    TubeMapper = vtk.vtkPolyDataMapper()
    TubeMapper.SetInputConnection(Tubes.GetOutputPort())
    CubeEdges = vtk.vtkActor()
    CubeEdges.SetMapper(TubeMapper)
    CubeEdges.GetProperty().SetDiffuseColor(cl)
    CubeEdges.GetProperty().SetSpecular(.4)
    CubeEdges.GetProperty().SetSpecularPower(10)

    return CubeEdges

def Solid(cm,
          cl=red):

    sm= vtk.vtkPolyDataMapper()
    sm.SetInputConnection(cm.GetOutputPort())
    a = vtk.vtkActor()
    a.SetMapper(sm)
    a.GetProperty().SetDiffuseColor(cl)
    a.GetProperty().SetSpecular(.4)
    a.GetProperty().SetSpecularPower(10)

    return a


def Render( al ):

    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    renWin.SetSize(640, 480)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    for a in al:
        ren.AddActor(a)

    ren.SetBackground(slate_grey)

    ren.ResetCamera()
    ren.GetActiveCamera().Dolly(1.2)
    ren.GetActiveCamera().Azimuth(30)
    ren.GetActiveCamera().Elevation(20)
    ren.ResetCameraClippingRange()

    iren.Initialize()
    renWin.Render()
    iren.Start()

def Il1():

    c1=Edges(MkCube(0.5,0.5,0.5, 1))
    c3=Edges(MkCube(0.25,0.25,0.25, 0.5),cl=blue)
    c4=Edges(MkCube(0.365,0.365,0.365, 0.25), cl=red)
    Render( [c1,c3,c4])

def Il2(N,ol,
        dofacel=True,
        doedgel=True,
        shrink=1.0,
        lim=None):

    """
    For example, show cubes necessary to calculte parents by:

    Il2(5,[0,1], dofacel=[True,False],doedgel=[True,False])
    """

    c1=Edges(MkCube(0.5,0.5,0.5, 1))

    if type(ol) != list :
        ol = [ol]

    if type(dofacel) != list:
        dofacel = [dofacel for x in ol]

    if type(doedgel) != list:
        doedgel =[doedgel for x in ol]

    sl = []
    # Put cubes at all of the corners
    for x,y,z in [ (0,0,0),
                   (1,0,0),
                   (0,1,0),
                   (0,0,1),
                   (1,1,0),
                   (1,0,1),
                   (0,1,1),
                   (1,1,1)]:
        sl.append( Solid(MkCube(x*(N-1.0)/N+ 0.5 / (N),
                                y*(N-1.0)/N+ 0.5 / (N),
                                z*(N-1.0)/N+ 0.5 / (N),
                                1.0 / (N)  * shrink),
                         cl=black))

    for o,doface, doedge in zip(ol, dofacel, doedgel):
        ci=pybnlib.K3DCenterItertor(N,N,N, o)
        while ci.inBounds():
            i,j,k= ci.getc()
            if lim== None or ( i < lim[0] and j < lim[1] and k < lim[2] ):
                sl.append( Solid(MkCube(1.0 / (N) * (i+0.5),
                                        1.0 / (N) * (j+0.5),
                                        1.0 / (N) * (k+0.5),
                                        1.0 / (N) * shrink)))
            ci.next()

        if doface:
            fi=pybnlib.K3FaceIterV2(N,N,N, o)
            cnt =0             
            while fi.inBounds():
                i,j,k= fi.getc()
                if ((lim== None or ( i < lim[0] and j < lim[1] and k < lim[2] ) ) and
                    ( (not type(doface)==int) or cnt < doface ))      :                
                    sl.append( Solid(MkCube(1.0 / (N) * (i+0.5),
                                            1.0 / (N) * (j+0.5),
                                            1.0 / (N) * (k+0.5),
                                            1.0 / (N) * shrink),
                                     cl=blue))
                    print i,j,k, " c:" , cnt
                fi.next()
                cnt+=1

        if doedge:
            print "***EDGE***"
            ei=pybnlib.K3EdgeIterV2(N,N,N, o)
            cnt=0
            while ei.inBounds():
                i,j,k= ei.getc()
                if ( ( lim== None or ( i < lim[0] and j < lim[1] and k < lim[2] )) and
                     ( (not type(doedge)==int) or cnt < doedge) and
                     ( type(doedge)==bool or ( type(doedge)==tuple) and cnt >= doedge[0] and cnt < doedge[1] ) ):
                    
                    sl.append( Solid(MkCube(1.0 / (N) * (i+0.5),
                                            1.0 / (N) * (j+0.5),
                                            1.0 / (N) * (k+0.5),
                                            1.0 / (N) * shrink),
                                     cl=green))
                    print i,j,k
                ei.next()
                cnt +=1

    
    Render( [c1]+sl)
                   


def ShowParents(it,
                shrink=0.5):

    c1=Edges(MkCube(0.5,0.5,0.5, 1))
    sl=[]

    N=it.Nx

    # Drow the current pos
    ci,cj,ck = it.getc()
    sl.append( Solid(MkCube(1.0 / (N) * (ci+0.5),
                                1.0 / (N) * (cj+0.5),
                                1.0 / (N) * (ck+0.5),
                                1.0 / (N) * shrink),
                         cl=red))

    parentl = it.CopyParentList()

    for pr in parentl :
        sl.append( Solid(MkCube(1.0 / (N) * (pr.i+0.5),
                                1.0 / (N) * (pr.j+0.5),
                                1.0 / (N) * (pr.k+0.5),
                                1.0 / (N) * shrink),
                         cl=green))

    Render( [c1]+sl)

    pass


def CheckParents(a, it,
                 filtered=False ):

    i,j,k= it.getc()
    if not filtered :
        pl = it.CopyParentList()
    else:
        pl = it.CopyFilteredParentList()

    for pr in pl :
        if pr.i < it.Nx and pr.j < it.Ny and pr.k < it.Nz:
            if not a[pr.i, pr.j, pr.k ] :
                print i,j,k , "has no parent" ,pr.i, pr.j, pr.k 

def CheckCoverage(N, omax, filtered=False):

    a= numarray.zeros( (N,N,N), numarray.Bool)

    # Starting points
    for x,y,z in [ (0,0,0),
                   (N-1,0,0),
                   (0,N-1,0),
                   (0,0,N-1),
                   (N-1,N-1,0),
                   (N-1,0,N-1),
                   (0,N-1,N-1),
                   (N-1,N-1,N-1)]:
        a[x,y,z] = True 

    # Iterations
    for  o in range(omax):

        ci=pybnlib.K3DCenterItertor(N,N,N, o)
        while ci.inBounds():
            i,j,k= ci.getc()
            CheckParents(a, ci, filtered=filtered)
            a[i,j,k]=True
            ci.next()

        fi=pybnlib.K3FaceIterV2(N,N,N, o)
        while fi.inBounds():
            i,j,k= fi.getc()
            CheckParents(a, fi,filtered=filtered)
            a[i,j,k]=True
            fi.next()
            
        ei=pybnlib.K3EdgeIterV2(N,N,N, o)
        while ei.inBounds():
            i,j,k= ei.getc()
            CheckParents(a, ei,filtered=filtered)
            a[i,j,k]=True
            ei.next()

    return a


# Linear system generation
def itoJ(i,N):

    if i == 0 :
        return 0
    
    lb=(2*N-1)
    la=-1
    lc=-2*i

    return int(( -b + math.sqrt( lb **2 - 4 * la * lc) ) / 2 / la + 1)


def JKtoi(J,K,N):

    return J*(N-2) - J*(J-1)/2 + K -1

def itoJK(i,N):

    J=itoJ(i,N)
    K=i - J*(2*N-3-J) /2

    return J,K+1
    
def GenLinSystem(poly):

    n=len(poly)
    N=n*(n-1) /2 
    rhs=numarray.zeros(N )
    a  = numarray.zeros( ( N,N) )
    c= 0

    for i in range(n):
        x = numarray.zeros(len(poly) )
        x[i]=1
        rhs[c]=(poly*x).sum()**2
        for J in range(0,n-1):
            for K in range(J+1,n):
                k = JKtoi(J,K,n)
                a[c,k] = (x[J] - x[K]) **2
        c+=1

    for i in range(n):
        for j in range (i+1,n) :
            x = numarray.zeros(n )
            x[i]=1
            x[j]=2
            rhs[c]=(poly*x).sum()**2
            for J in range(0,n-1):
                for K in range(J+1,n):
                    k = JKtoi(J,K,n)
                    a[c,k] = (x[J] - x[K]) **2
            c+=1
            if c >= N:
                break
        if c >= N:
            break
    return a, rhs

def Selve1():

    a=[ [ 1,1,1,0,0,0  ],
        [ 1,0,0,1,1,0  ],
        [ 0,1,0,1,0,1  ],
        [ 0,0,1,0,1,1  ],
        [ 0,1,1,1,1,0  ],
        [ 1,0,1,1,0,1  ] ]

    rhs = [9, 1 ,1 ,1 , 4 , 4]

a=[ [ 1,1,1,0,0,0  ],
    [ 1,0,0,1,1,0  ],
    [ 0,1,0,1,0,1  ],
    [ 0,0,1,0,1,1  ],
    [ 0,1,1,1,1,0  ],
    [ 1,0,1,1,0,1  ] ]

rhs = [9, 1 ,1 ,1 , 4 , 4]    

    

        

    
    

#import sys; sys.path.extend(["/import/appcs/bn204/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])
#import pybnlib

p2=numarray.array([3,-1, -1, -1])

# Symetric  cube:
p3=numarray.array([7,-1, -1, -1, -1 ,-1, -1 , -1])
a,r=GenLinSystem(p3)
x=la.solve_linear_equations(a,r)
r2=la.mlab.innerproduct(a,x)
