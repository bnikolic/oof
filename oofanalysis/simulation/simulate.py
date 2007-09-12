# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# September 2007
#
# Simulations for talks
#
# See also scripts in astromaptest, especially "oofillustrate.py"

import os

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
    

def ZernPower(zn , dz):

    ""

    npix = 512
    tel1 = MkTalkTel()
    
    apmod = pyoof.MkSimpleAp( tel1,
                              1e-3,
                              npix,
                              5,
                              4)

    amm=pybnmin1.ModelDesc( apmod.downcast() )
    amm.getbyname("z%i" % zn).setp(1)

    modmaps=ModelMaps(apmod, dz)

    return modmaps

def PlotMapsSet(r,
                pref="plots/temp",
                post=".png/PNG",
                s=4e-4):

    "Plot a set of model maps"

    """
    s: bounding box scale
    """

    for i,mid  in enumerate( ["infoc",
                              "-ve",
                              "+ve"]):
        implot.plotmap(r[i],
                       bbox=[x * s for x in [-1,1,-1,1]] ,
                       fout=pref+mid+post,
                       colmap="heat")
        

    


#implot.plotmap(r[1], bbox=[x * 4e-4 for x in [-1,1,-1,1]] , colmap="heat")
