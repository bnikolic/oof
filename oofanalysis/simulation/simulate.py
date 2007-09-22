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

import iofits4
import implot
import oofdataio
import oofreduce
import oofplot



def MkTalkTel():

    """
    Toy telescope for use in talks
    """
    
    return pyoof.MkALMA()


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

def DefocModelMaps(apmod, dz, telgeo):

    "Generate defocus model maps with proper defocus"

    farf= pyoof.FarF ( apmod.getphase(),
                       1e-3)

    res = []
    for cdz in [ 0 , dz, -1* dz]:
        m=pyplot.Map( apmod.getamp().nx,
                      apmod.getamp().ny)
        mp=pyplot.Map( apmod.getphase() )

        od=pyoof.ObsDefocus(telgeo, apmod.getamp(), cdz,
                            1e-3)
        od.DePhase(mp)
                            
        farf.Power( apmod.getamp(), mp,
                    m)
        res.append(m)
    
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

def RandomSurface( znmax , stddev=0.5,
                   dzlist=[1.0],
                   propdefoc=False):

    if type(dzlist ) != list:
        dzlist = [dzlist]

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

    res= []
    for dz in dzlist:
        if propdefoc:
            modmaps=DefocModelMaps(apmod, dz, MkTalkTel())
        else:
            modmaps=ModelMaps(apmod, dz)
        res.append(modmaps)

    if len(res) == 1:
        return res[0], apmod
    else :
        return res, apmod

def NoisyfySet(r,
               therm_noise):

    maxlevel=r[0].max()
    for m in r:
        mnoise=pyplot.Map( m.nx, m.ny)
        pyplot.NormDist(mnoise, maxlevel * therm_noise)
        m.add(mnoise)
        

def SaveSet( rlist, dzlist,
             fnameout):

    tabs=[]
    for r,dz in zip (rlist, dzlist):
        ds=pyplot.MapToDSPoss(r)
        me=pyplot.MapDSNearest(ds, r)
        me.Calc(r, ds)
        tabs.append( oofdataio.DataSeriesToOOFTable(ds))
        tabs[-1].header.update("dz",dz)

    fout=iofits4.PrepFitsOut("")
    fout[0].header.update("telesc", "ALMA")
    fout[0].header.update("freq", 3e8/1e-3)    
    fout.extend(tabs)
    iofits4.Write( fout,
                   fnameout ,
                   overwrite=1)
    
    
def CropFile(fnamein, s ):

    """
    s=4e-4 is good ...
    """

    fnameout=fnamein[:-5]+"-crop.fits"
    print fnameout

    def selfn(d):
        m1 = numarray.logical_and( d.field("dX") > -s,
                                   d.field("dX") < s)
        m2 = numarray.logical_and( d.field("dY") > -s,
                                   d.field("dY") < s)
        return numarray.logical_and(m1,m2)

    iofits4.TableSelect(fnamein,
                        fnameout,
                        rowselfn= selfn)
    
                                   
def GenSimSet(dirout):

    dz=2e-3

    fnameout=os.path.join(dirout, "sim.fits")

    res, apmod=RandomSurface(4, dzlist=dz,  propdefoc=True)

    SaveSet( res,
             [0 , -dz, dz],
             fnameout)

    CropFile(fnameout, 6e-4)
    
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
        

def PlotAperture(apmod,
                 pref,
                 post=".png/PNG",
                 contour=False):

    s=12

    if contour:
        contours=implot.MkChopContours(pyplot.Map(apmod.getphase()),
                                       ctype="lin", nlevels=5)
    else:
        contours=None    

    implot.plotmap(pyplot.Map(apmod.getphase()),
                   bbox=[x * s for x in [-1,1,-1,1]] ,
                   fout=pref+"-phase"+post ,
                   colmap="heat",
                   valrange=None,
                   contours=contours,
                   contcolour=0)

    implot.plotmap(pyplot.Map(apmod.getamp()),
                   bbox=[x * s for x in [-1,1,-1,1]] ,
                   fout=pref+"-amp"+post ,
                   colmap="heat",
                   valrange=None)

def IllustratePerfectAp():

    apmod=MkApModel(2)
    amm=pybnmin1.ModelDesc( apmod.downcast() )

    #Set taper to -12 db @edge
    amm.getbyname("sigma").setp(0.36)
    amm.getbyname("z0").setp(1)

    PlotAperture(apmod,
                 "plots/perfectap")

def IllustratePerfectApFFT():

    apmod=MkApModel(2)
    amm=pybnmin1.ModelDesc( apmod.downcast() )

    #Set taper to -12 db @edge
    amm.getbyname("sigma").setp(0.36)
    amm.getbyname("z0").setp(1)

    farf=pyoof.FarF ( apmod.getphase(),
                      1e-3)

    fa= pyplot.Map(apmod.getphase().nx,apmod.getphase().ny)
    fp= pyplot.Map(apmod.getphase().nx,apmod.getphase().ny)

    farf.AmpPhase( apmod.getamp(),
                   apmod.getphase(),
                   fa,
                   fp)
    s=4e-4
    implot.plotmap(fa,
                   bbox=[x * s for x in [-1,1,-1,1]] ,
                   fout="plots/perfect_farf_a.png/PNG",
                   colmap="heat",
                   valrange=None )
    implot.plotmap(fp,
                   bbox=[x * s for x in [-1,1,-1,1]] ,
                   fout="plots/perfect_farf_p.png/PNG",
                   colmap="heat",
                   valrange=None )    
    

    
    
def MPIfRIllus():

    r0, apmod=RandomSurface(5,0,3)
    PlotMapsSet(r0, pref="plots/mpifr-pfctsfc",
                eqrange=True)

    r, apmod=RandomSurface(5,0.2,3)
    PlotMapsSet(r, pref="plots/mpifr-rsfc",
                eqrange=True)
    PlotAperture(apmod ,
                 "plots/mpifr-aperture-rsfc",
                 contour=True)
    
    NoisyfySet(r, 0.01)
    PlotMapsSet(r, pref="plots/mpifr-rsfc-noise100",
                eqrange=False)

def GBTWkSpIllus():

    dzlist = [1, 2,3,5,7,10 ]

    r, apmod=RandomSurface(5,0.2, dzlist)

    PlotAperture(apmod ,
                 "plots/oofwk-aperture-rsfc",
                 contour=True)    

    for i, dz in enumerate(dzlist):
        PlotMapsSet(r[i], pref=("plots/oofwk-%g-rsfc" % dz),
                    eqrange=True,
                    s=6e-4)
    
        NoisyfySet(r[i], 0.01)
        PlotMapsSet(r[i],
                    pref=("plots/oofwk-%g-rsfc-noise100" % dz),
                    eqrange=False,
                    s=6e-4)

        NoisyfySet(r[i], 0.02)
        PlotMapsSet(r[i],
                    pref=("plots/oofwk-%g-rsfc-noise220" % dz),
                    eqrange=False,
                    s=6e-4)        

#implot.plotmap(r[1], bbox=[x * 4e-4 for x in [-1,1,-1,1]] , colmap="heat")
