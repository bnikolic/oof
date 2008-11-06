"""
Bojan Nikolic <bojan@bnikolic.co.uk>
"""
import os
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
             width=70,
             posfit=True):
    fm=pyplot.GaussMapModel(m)
    bnmin1utils.SetIC(fm, [1,m.nx/2,m.ny/2,
                           width,0.5,0.3])
    lmm=pybnmin1.LMMin(fm)
    if not posfit:
        for p in ["x0", "y0"]:
            lmm.getbyname(p).dofit=0
    lmm.solve()
    chisq=lmm.ChiSquared()
    return [lmm.getbyname(p).getp() for p in ["amp", "sigma"] ] + [chisq]


def GenAmpBiasData(npix=64,
                   n=100,
                   noise=0.5,
                   posfit=True):
    r=[]
    r2=[]
    for i in range(n):
        r.append(MkMapFit(MkIllMap(npix,noise=noise),
                          posfit=posfit))
        r2.append(MkMapFit(MkIllMap(npix,noise=noise/(2.0**0.5),width=70.0/2),
                           width=70.0/2,
                          posfit=posfit))
    if posfit:
        pickle.dump([r,r2],open("o/ampbiasdata.p","w"))
    else:
        pickle.dump([r,r2],open("o/ampbiasdata-npos.p","w"))

def GenCorrData(npix=64,n=100,noise=0.5):
    r=[]
    for i in range(n):
        r.append(MkMapFit(MkIllMap(npix,noise=noise)))
    pickle.dump(r,open("o/corrdata.p","w"))


def PlotAmpBias(fin="o/ampbiasdata.p",
                fout="o/amp"):
    r,r2=pickle.load(open(fin))
    noise=0.5
    print "%shist-%i.eps" % (fout,noise*10,)
    print "o/%scuml-%i.eps" % (fout,noise*10,)
    pyxplot.histogram([[r, ""],
                       [r2,""]],
                      "%shist-%i.eps" % (fout,noise*10,),
                      width=10,
                      xlabel="Amplitude",
                      nbins=50)    

    obsdst.cuml([[r, ""],
                 [r2,""]],
                "%scuml-%i.eps" % (fout,noise*10,),
                xlabel="Amplitude",
                fmin=0.4,
                fmax=0.6)

    obsdst.cuml([[r, ""],
                 [r2,""]],
                "%suml-%i-whole.eps" % (fout,noise*10,),
                xlabel="Amplitude")


def plotCorr():
    d=numpy.array(pickle.load(open(("o/corrdata.p"))))
    twod.hist2d(d[:,0],d[:,1],
                "o/ampwidthcorr.eps",
                xlabel="Amplitude",
                ylabel="Width")

def plotchi():
    xlabel=r"$-\log P(x|\theta)$"
    d=numpy.array(pickle.load(open(("o/ampbiasdata.p"))))
    d2=numpy.array(pickle.load(open(("o/ampbiasdata-npos.p"))))
    pyxplot.histogram([[d[0,:,2]*4, ""],
                       [d2[0,:,2]*4,""]],
                      "o/chisqhist.eps",
                      width=10,
                      xlabel=xlabel,
                      nbins=50)

    obsdst.cuml([[d[0,:,2]*4, ""],
                 [d2[0,:,2]*4,""]],
                "o/chisqcuml.eps",
                xlabel=xlabel,
                fmin=0.48, fmax=0.52)


def MapMCMC(npix=64,
            noise=0.5,
            width=70,
            posfit=True,
            ns=1000):
    ic=[1/noise,npix/2,npix/2,
        width,0.5,0.3]

    m1=pyplot.Map(npix,npix)
    f2=pyplot.GaussMapModel(m1)
    f2.worldcs=False
    bnmin1utils.SetIC(f2,ic)
    f2.eval(m1)
    mnoise=pyplot.Map(npix, npix)
    pyplot.NormDist(mnoise, 1.0 )
    m1.add(mnoise)
    

    fm=pyplot.GaussMapModel(m1)
    bnmin1utils.SetIC(fm, ic)
    mm=pybnmin1.MetropolisMCMC(fm,
                               [0.05, 1.0, 1.0, 1.0, 0.05, 0.05],
                               33)

    return mm.sample(ns)



def genMapMCMCdata(rep=1):
    fname="o/mcmc.p"
    if (os.access(fname, os.F_OK)):
        d=pickle.load(open(fname))
    else:
        d=[]
    for i in range(rep):
        r=bnmin1utils.ChainToArray(MapMCMC(ns=1000))
        d.append(r[10:])
    pickle.dump(d,open(fname,"w"))    


def readMapMCMC():
    x=pickle.load(open("o/mcmc.p"))
    r=[]
    for y in x:
        r.extend(list(y[:,0]))
    return r

def plotMCMCbias():
    x=readMapMCMC()
    pyxplot.histogram([[x, ""],],
                      "o/mcmc_bias.eps",
                      width=10,
                      xlabel="Amplitude",
                      nbins=100,
                      relative=True,
                      key=None)    

    
