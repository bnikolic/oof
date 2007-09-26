# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# GBT single beam illustraton

import math

from setup import *

import pyoof
import implot
import pyplot





def MkGBT(over=4):

    tel=pyoof.TelSwitch("GBT")
    npix = 512
    
    apmod = pyoof.MkSimpleAp( tel,
                              7e-3,
                              npix,
                              4,
                              over)

    return apmod , tel

def PlotGBTDefocus():

    apmod, tel = MkGBT()

    phasemap=pyplot.Map( apmod.getphase() )
    phasemap.mult(0)
    
    tel.MkDefocus(35e-3, phasemap)
    phasemap.add(-1.0 * phasemap.getv( phasemap.nx/2, phasemap.ny/2)  )    

    mask = pyoof.Clone(phasemap)
    tel.DishMask(mask)

    phasemap.mult(mask)    

    nlevels=7
    contours=[ phasemap.min() * (i+1)/float(nlevels+1) for i in range(nlevels)  ]
    
    for ext in ["png/PNG" ] :
        implot.plotmap(phasemap,
                       bbox=[x * 60 for x in [-1,1,-1,1]] ,
                       fout="plots/gbtdefocus."+ext ,
                       colmap="heat",
                       valrange=None,
                       contours=contours,
                       contcolour=0)
        

    
    

def MkDefocusBeam(dz, apmod,tel, difference=False):

    wavel=7e-3

    phasemap=pyplot.Map( apmod.getphase() )
    phasemap.mult(0)
    res=pyplot.Map( apmod.getphase().nx,apmod.getphase().ny)

    tel.MkDefocus(dz, phasemap)

    if difference == False:
        farf=pyoof.FarF ( apmod.getphase(),
                          wavel)
    else:
        farf=pyoof.ChoppedFF ( apmod.getphase(),
                               wavel)
        farf.vchop=0
        farf.hchop= 58 * math.pi / 3600  / 180
        

    farf.Power( apmod.getamp(),
                phasemap,
                res)

    return phasemap, res
    
def PlotGBTDefocusedBeam( difference=False):

    apmod, tel = MkGBT(over=8)
    


    for dz in [0 , -35, 35]:

        phasemap, res = MkDefocusBeam( dz , apmod, tel,
                                       difference=difference)

        contours=implot.MkChopContours(res,
                                       ctype="log",
                                       nlevels=8)
        if difference:
            fnameout= "plots/gbtsingledefoc%g-diff.png/PNG" % dz
        else:
            fnameout= "plots/gbtsingledefoc%g.png/PNG" % dz

        implot.plotmap(res,
                       bbox=[x * 8e-4 for x in [-1,1,-1,1]] ,
                       fout=fnameout,
                       colmap="heat",
                       valrange=None,
                       contours=contours,
                       contcolour=0)
        

                         

