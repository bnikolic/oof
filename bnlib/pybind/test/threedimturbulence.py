# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007
#
# Investigate how to do three dimensional turbulence by the mid-point
# displacement method.

import vtk
from vtk.util.colors import *

import pybnlib

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
        doedgel=True):

    """
    For example, show cubes necessary to calculte parents by:

    Il2(5,[0,1], dofacel=[True,False],doedgel=[True,False])
    """

    c1=Edges(MkCube(0.5,0.5,0.5, 1))

    if type(ol) != list :
        ol = [ol]

    if type(dofacel) != list:
        dofacel = [dofacel]

    if type(doedgel) != list:
        doedgel =[doedgel]

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
                                1.0 / (N) ),
                         cl=black))

    for o,doface, doedge in zip(ol, dofacel, doedgel):
        ci=pybnlib.K3DCenterItertor(N,N,N, o)
        while ci.inBounds():
            i,j,k= ci.getc()
            sl.append( Solid(MkCube(1.0 / (N) * (i+0.5),
                                    1.0 / (N) * (j+0.5),
                                    1.0 / (N) * (k+0.5),
                                    1.0 / (N) )))
            ci.next()

        if doface:
            fi=pybnlib.K3FaceIter(N,N,N, o)
            while fi.inBounds():
                i,j,k= fi.getc()
                sl.append( Solid(MkCube(1.0 / (N) * (i+0.5),
                                        1.0 / (N) * (j+0.5),
                                        1.0 / (N) * (k+0.5),
                                        1.0 / (N) ),
                                 cl=blue))
                print i,j,k
                fi.next()

        if doedge:
            print "***EDGE***"
            ei=pybnlib.K3EdgeIter(N,N,N, o)
            while ei.inBounds():
                i,j,k= ei.getc()
                sl.append( Solid(MkCube(1.0 / (N) * (i+0.5),
                                        1.0 / (N) * (j+0.5),
                                        1.0 / (N) * (k+0.5),
                                        1.0 / (N) ),
                                 cl=green))
                print i,j,k
                ei.next()                    

    
    Render( [c1]+sl)
                   

    
    

#import sys; sys.path.extend(["/import/appcs/bn204/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])
#import pybnlib

