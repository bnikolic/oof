"""
Bojan Nikolic <bojan@bnikolic.co.uk>
"""
import numpy

import setup

import implot
import pyplot
import bnmin1utils
import pybnmin1

import pyxplot


def MkIllMap(npix,
             noise=0.3,
             width=70):
    m1=pyplot.Map(npix,npix)
    fm=pyplot.GaussMapModel(m1)
    fm.worldcs=False
    bnmin1utils.SetIC(fm, [1,npix/2,npix/2,
                           70,0.5,0.3])
    fm.eval(m1)
    mnoise=pyplot.Map(npix, npix)
    pyplot.NormDist(mnoise, 1.0 * noise)
    m1.add(mnoise)
    return m1


if 0:
    implot.plotmap(MkIllMap(256,0), "o/gauss_no.eps/CPS",colmap="heat")
    implot.plotmap(MkIllMap(256,0.2), "o/gauss_med.eps/CPS",colmap="heat")
    implot.plotmap(MkIllMap(256,0.5), "o/gauss_high.eps/CPS",colmap="heat")

def plotProjections(m):
    d=numpy.array(m.vect())
    d.shape=m.nx,m.ny
    xproj=d.sum(axis=1)
    yproj=d.sum(axis=0)
    pyxplot.vect(numpy.arange(len(xproj)),
                 xproj,
                 "o/xproj.eps",
                 xlabel=r"$x_i$",
                 ylabel=r"$\sum_i b_i$ ")
    pyxplot.vect(numpy.arange(len(yproj)),
                 yproj,
                 "o/yproj.eps",
                 xlabel=r"$y_i$",
                 ylabel=r"$\sum_i b_i$ ");
                 
    return xproj, yproj

if 1:
    m=MkIllMap(256)
    x,y=plotProjections(m)

def maxpix(m):
    d=numpy.array(m.vect())
    mx=d.argmax()
    return int(mx/m.nx), mx % m.nx


def plotmode(n=1000):
    xx, xy= [] , []
    for i in range(n):
        x=maxpix(MkIllMap(256)) 
        xx.append(x[0])
        xy.append(x[1])
    pyxplot.histogram([[xx, "x"],
                       [xy, "y"]],
                      "o/pixpos.eps",
                      width=10,
                      xlabel="position")
                  
    return xx, xy
    
def MkMapFit(m):
    fm=pyplot.GaussMapModel(m)
    bnmin1utils.SetIC(fm, [1,m.nx/2,m.ny/2,
                           70,0.5,0.3])
    lmm=pybnmin1.LMMin(fm)
    lmm.solve()
    return [ lmm.getbyname(p).getp() for p in ["amp"]]

def PlotAmpBias(npix=64,n=100,noise=0.5):
    r=[]
    for i in range(n):
        r.append(MkMapFit(MkIllMap(npix,noise=noise))[0])
    pyxplot.histogram([[r, ""]],
                      "o/amphist-%i.eps" % (noise*10,),
                      width=10,
                      xlabel="Amplitude",
                      nbins=50)    






