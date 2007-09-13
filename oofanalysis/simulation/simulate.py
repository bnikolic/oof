# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# September 2007
#
# Simulations for talks
#
# See also scripts in astromaptest, especially "oofillustrate.py"

import os

import numarray.random_array

from setup import *

import pyplot
import pyoof
import pybnmin1

import implot



def MkTalkTel():

    """
    Toy telescope for use in talks
    """
    
    tel1=pyoof.PrimeFocusGeo()                         
    tel1.PrimRadius=10
    tel1.PrimF=1

    return tel1


def ModelMaps(apmod,
              dz):
    
    "Generate de-focussed maps from an aperture model"

    """

    """

    amm=pybnmin1.ModelDesc( apmod.downcast() )
    z4orig=amm.getbyname("z4" ).getp()

    farf= pyoof.FarF ( apmod.getphase(),
                       1e-3)

    res = []
    for cdz in [ 0 , dz, -1* dz]:
        amm.getbyname("z4" ).setp(z4orig + cdz)
        m=pyplot.Map( apmod.getamp().nx,
                      apmod.getamp().ny)
        farf.Power( apmod.getamp(), apmod.getphase(),
                    m)
        res.append(m)

    amm.getbyname("z4" ).setp(z4orig)
    
    return res
    


def MkApModel(znmax,
              npix=512):

    npix = 512
    tel1 = MkTalkTel()
    
    apmod = pyoof.MkSimpleAp( tel1,
                              1e-3,
                              npix,
                              znmax,
                              4)
    return apmod
    
    

def ZernPower(zn , dz):

    ""

    apmod=MkApModel(5)

    amm=pybnmin1.ModelDesc( apmod.downcast() )
    amm.getbyname("z%i" % zn).setp(1)

    modmaps=ModelMaps(apmod, dz)

    return modmaps

def RandomSurface( znmax , stddev=0.5,dz=1):

    apmod=MkApModel(znmax)

    amm=pybnmin1.ModelDesc( apmod.downcast() )

    n=amm.NTotParam()

    #Set taper to -12 db @edge
    amm.getbyname("sigma").setp(0.36)

    v=numarray.random_array.normal(0,stddev, n-2)
    for i,x in enumerate(v) :
        print i
        amm.getbyname("z%i" % i).setp(x)

    print "Aperture RMS is :" , pyplot.MapRMS(apmod.getphase())
    modmaps=ModelMaps(apmod, dz)

    return modmaps

def NoisyfySet(r,
               therm_noise):

    maxlevel=r[0].max()
    for m in r:
        mnoise=pyplot.Map( m.nx, m.ny)
        pyplot.NormDist(mnoise, maxlevel * therm_noise)
        m.add(mnoise)
        
    

def PlotMapsSet(r,
                pref="plots/temp",
                post=".png/PNG",
                s=4e-4,
                eqrange=False):

    "Plot a set of model maps"

    """
    s:       bounding box scale
    eqrange: if true, plot all maps to same range
    """

    if eqrange:
        lmax= [ m.max() for m in r]
        lmin= [ m.min() for m in r]
        valrange=[ min(lmin), max(lmax) ]
    else:
        valrange=None

    for i,mid  in enumerate( ["infoc",
                              "-ve",
                              "+ve"]):
        implot.plotmap(r[i],
                       bbox=[x * s for x in [-1,1,-1,1]] ,
                       fout=pref+mid+post,
                       colmap="heat",
                       valrange=valrange)
        

    
def MPIfRIllus():

    r0=RandomSurface(5,0,3)
    PlotMapsSet(r0, pref="plots/mpifr-pfctsfc",
                eqrange=True)
    
    r=RandomSurface(5,0.2,3)
    PlotMapsSet(r, pref="plots/mpifr-rsfc",
                eqrange=True)
    NoisyfySet(r, 0.01)
    PlotMapsSet(r, pref="plots/mpifr-rsfc-noise100",
                eqrange=False)    

#implot.plotmap(r[1], bbox=[x * 4e-4 for x in [-1,1,-1,1]] , colmap="heat")
