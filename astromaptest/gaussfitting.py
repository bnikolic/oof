"""
Bojan Nikolic <bojan@bnikolic.co.uk>
"""
import numpy
import pickle

import setup

import implot
import pyplot
import bnmin1utils
import pybnmin1

import pyxplot
from pyhlp import obsdst, twod


def MkIllMap(npix,
             noise=0.3,
             width=70):
    m1=pyplot.Map(npix,npix)
    fm=pyplot.GaussMapModel(m1)
    fm.worldcs=False
    bnmin1utils.SetIC(fm, [1,npix/2,npix/2,
                           width,0.5,0.3])
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

if 0:
    m=MkIllMap(256)
    x,y=plotProjections(m)

def plotmapmc():
    for i in range(10):
        implot.plotmap(MkIllMap(64,0.5),
                       "o/gauss-5-%i.eps/CPS" % i,
                       colmap="heat")


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
    
def MkMapFit(m,
             width=70):
    fm=pyplot.GaussMapModel(m)
    bnmin1utils.SetIC(fm, [1,m.nx/2,m.ny/2,
                           width,0.5,0.3])
    lmm=pybnmin1.LMMin(fm)
    lmm.solve()
    return [ lmm.getbyname(p).getp() for p in ["amp", "sigma"] ]


def GenAmpBiasData(npix=64,n=100,noise=0.5):
    r=[]
    r2=[]
    for i in range(n):
        r.append(MkMapFit(MkIllMap(npix,noise=noise))[0])
        r2.append(MkMapFit(MkIllMap(npix,noise=noise/(2.0**0.5),width=70.0/2),
                           width=70.0/2)[0])
    pickle.dump([r,r2],open("o/ampbiasdata.p","w"))

def GenCorrData(npix=64,n=100,noise=0.5):
    r=[]
    for i in range(n):
        r.append(MkMapFit(MkIllMap(npix,noise=noise)))
    pickle.dump(r,open("o/corrdata.p","w"))


def PlotAmpBias():
    r,r2=pickle.load(open("o/ampbiasdata.p"))
    noise=0.5
    pyxplot.histogram([[r, ""],
                       [r2,""]],
                      "o/amphist-%i.eps" % (noise*10,),
                      width=10,
                      xlabel="Amplitude",
                      nbins=50)    

    obsdst.cuml([[r, ""],
                 [r2,""]],
                "o/ampcuml-%i.eps" % (noise*10,),
                xlabel="Amplitude",
                fmin=0.4,
                fmax=0.6)

    obsdst.cuml([[r, ""],
                 [r2,""]],
                "o/ampcuml-%i-whole.eps" % (noise*10,),
                xlabel="Amplitude")


def plotCorr():
    d=numpy.array(pickle.load(open(("o/corrdata.p"))))
    twod.hist2d(d[:,0],d[:,1],
                "o/ampwidthcorr.eps",
                xlabel="Amplitude",
                ylabel="Width")



