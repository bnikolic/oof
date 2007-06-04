# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007
#
# Investigate how to do three dimensional turbulence by the mid-point
# displacement method.

import vtk
from vtk.util.colors import *

CubeModel = vtk.vtkCubeSource()
CubeModel.SetCenter(.5, .5, .5)
Edges = vtk.vtkExtractEdges()
Edges.SetInputConnection(CubeModel.GetOutputPort())
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
CubeEdges.GetProperty().SetDiffuseColor(khaki)
CubeEdges.GetProperty().SetSpecular(.4)
CubeEdges.GetProperty().SetSpecularPower(10)




ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(640, 480)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

ren.AddActor(CubeEdges)

ren.SetBackground(slate_grey)

ren.ResetCamera()
ren.GetActiveCamera().Dolly(1.2)
ren.GetActiveCamera().Azimuth(30)
ren.GetActiveCamera().Elevation(20)
ren.ResetCameraClippingRange()

iren.Initialize()
renWin.Render()
iren.Start()

