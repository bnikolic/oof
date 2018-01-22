# Simulations and tools for shaped reflector telescopes
# nix-shell  /home/user/n/oof/build/nix/oof.nix -A oofenv -j 2 --cores 6 --run "python  -i"

from math import factorial as fact

import numpy, scipy, pandas
import scipy.optimize

#Plotting setup
from matplotlib import pylab
import matplotlib.pyplot as plt
from matplotlib import cm

from mpl_toolkits import mplot3d

import os


def mkZernFitDifFn(nmax, a, v):
    "Make a function that returns difference between model and fit"
    lcfn=mkZernLCFn(nmax, a)
    return lambda x: v-lcfn(x)

def fitZerns(nmax, a, v):
    """
    Example: 
      d=loadZemaxDC("/home/user/QubesIncoming/DocStore/CORRECT3.TXT")
      mm=numpy.logical_and(d.FM==0 , d.FL==0)
      dd=numpy.vstack( [d.AX[mm], d.AY[mm], d.IN[mm] ])
      fitZerns(3, numpy.moveaxis(dd[0:2],0,-1), dd[2] )
    """
    return scipy.optimize.leastsq(mkZernFitDifFn(nmax, a, v),
                                  numpy.zeros(nZern(nmax)),
                                  full_output=True)

    
def loadZemaxDC(fin):
    """Load Zemax direction cosine output file"""
    return pandas.read_table(fin,
                             names=["FL", "FM", "AX", "AY", "IL", "IM", "IN" ] ,
                             delim_whitespace=True)

def plotQuiverN(d, m):
    """Plot the angle arrival direction cosines as a quiver"""
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    surf = ax.quiver(d.AX[m], d.AY[m], 0,
                     d.IL[m], d.IM[m], d.IN[m])
    
    ax.set_zlim(-1, 2)    
    plt.show()    

def zernIFromNL(n, l):
    return (n*(n+1) + n+ l)/2

def zernNLFromI(i):
    n=0
    while zernIFromNL(n,-n) <=i:
        n+=1
    n-=1
    l=-n
    while zernIFromNL(n, l) != i:
        l+=1
    return n,l
    
def plotZernsWithC(cl, nw=4, npix=128):
    "Plot Zernikes and their coefficients"
    fig=plt.figure(figsize=(12,12))
    n=len(cl)
    for i, c in enumerate(cl[1:]):
        ax=fig.add_subplot(nw, nw, i+1)
        n,l=zernNLFromI(i+1)
        g=numpy.moveaxis(numpy.mgrid[-1:1:npix*1j, -1:1:npix*1j], 0, -1)
        zz=evalZern(n,l,g)
        mask=(g**2).sum(axis=2) > 1.0
        zz[mask]=0
        ax.imshow(zz)
        ax.set_title("Z(%i, %i)= %4f" % (n, l, c))
        #plt.imshow(c)
    plt.show()

def selectData(fnamein, FM, FL):
    d=loadZemaxDC(fnamein)
    mm=numpy.logical_and(d.FM==FM , d.FL==FL)
    return d, mm

def plotIncomingRays(fnamein, FM, FL):
    fnameout="plots/%s-%g-%g.png" % (os.path.splitext(os.path.basename(fnamein))[0],
                                     FM, FL)
    d, mm=selectData(fnamein, FM, FL)
    plotQuiverN(d, mm)
    plt.savefig(fnameout)
    plt.close()

def plotZernFit(fnamein, FM, FL):
    fnameout="plots/%s-fit-%g-%g.png" % (os.path.splitext(os.path.basename(fnamein))[0],
                                         FM, FL)
    d, mm=selectData(fnamein, FM, FL)
    dd=numpy.vstack( [d.AX[mm], d.AY[mm], d.IN[mm] ])    
    x=fitZerns(4, numpy.moveaxis(dd[0:2],0,-1), dd[2] )
    plotZernsWithC(x[0])
    plt.savefig(fnameout)
    plt.close()    
    
if 0:
    plotIncomingRays("/home/user/QubesIncoming/DocStore/CORRECT3.TXT", 0, 0)
    plotIncomingRays("/home/user/QubesIncoming/DocStore/CORRECT3.TXT", 2.0, 2.0)
    plotIncomingRays("/home/user/QubesIncoming/DocStore/CLASSIC3.TXT", 0, 0)

if 0:
    plotZernFit("/home/user/QubesIncoming/DocStore/CORRECT3.TXT", 0.0, 0.0)    
    plotZernFit("/home/user/QubesIncoming/DocStore/CORRECT3.TXT", 2.0, 2.0)
    plotZernFit("/home/user/QubesIncoming/DocStore/CLASSIC3.TXT", 0.0, 0.0)    
    plotZernFit("/home/user/QubesIncoming/DocStore/CLASSIC3.TXT", 2.0, 2.0)
    
    
