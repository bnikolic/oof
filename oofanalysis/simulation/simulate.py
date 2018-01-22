# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# September 2007
#
# Simulations for talks
#
# See also scripts in astromaptest, especially "oofillustrate.py"

import os

import numpy

from setup import *

import pyplot
import pyoof
import pybnmin1
import pyfits

import iofits4
import implot
import oofdataio
import oofreduce
import oofplot



def MkTalkTel():
    "Make a telescope geometry"
    tel=pyoof.PrimeFocusGeo()
    tel.PrimRadius=3.0
    tel.PrimF=14.4
    return tel


def ModelMaps(apmod,
              dz):
    """
    Generate de-focussed maps from an aperture model
    
    :param dz: Note this is coefficient of z4. Actual defocus is 2x this!

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

def DefocModelMaps(apmod, dz, telgeo,
                   wl=1e-3):

    "Generate defocus model maps with proper defocus"

    farf= pyoof.FarF (apmod.getphase(),
                      wl)

    res = []
    for cdz in [ 0 , dz, -1* dz]:
        m=pyplot.Map( apmod.getamp().nx,
                      apmod.getamp().ny)
        mp=pyplot.Map( apmod.getphase() )

        od=pyoof.ObsDefocus(telgeo, apmod.getamp(), cdz,
                            wl)
        od.DePhase(mp)
                            
        farf.Power( apmod.getamp(), mp,
                    m)
        res.append(m)
    
    return res    
    


def MkApModel(znmax,
              npix=256,
              wl=1e-3):

    npix = npix
    tel1 = MkTalkTel()
    
    apmod = pyoof.MkSimpleAp( tel1,
                              wl,
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

def RandomSurface( znmax ,
                   stddev=0.5,
                   dzlist=[1.0],
                   propdefoc=True):

    if type(dzlist ) != list:
        dzlist = [dzlist]

    apmod=MkApModel(znmax)

    amm=pybnmin1.ModelDesc( apmod.downcast() )

    n=amm.NTotParam()

    #Set taper to -12 db @edge
    amm.getbyname("sigma").setp(0.36)

    if stddev >0:
        v=numpy.random.normal( 0,stddev, n-4)
    else:
        v=numpy.zeros( n-4)
        
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
        tabs[-1].header.update([("dz",dz, "Defocus distance")])

    fout=iofits4.PrepFitsOut("")
    fout[0].header.update([("telesc", "ALMA"),
                           ("freq", 3e8/1e-3)])
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
        m1 = numpy.logical_and( d.field("dX") > -s,
                                   d.field("dX") < s)
        m2 = numpy.logical_and( d.field("dY") > -s,
                                   d.field("dY") < s)
        return numpy.logical_and(m1,m2)

    iofits4.TableSelect(fnamein,
                        fnameout,
                        rowselfn= selfn)

def NoisifyFile(fnamein, fnameout,
                fnoise_therm):
    
    fin=pyfits.open(fnamein)
    
    nlevel=fnoise_therm * fin[1].data.field("fnu").max()

    for i in range(1,len(fin)) :
        l=len(fin[i].data.field("fnu"))
        nv=fin[i].data.field("fnu")+  numpy.random.normal(0,
                                                          nlevel,
                                                          l)
        fin[i].data.field("fnu").setreal(nv)

    iofits4.Write( fin, fnameout , overwrite=1)
    
                                   
def GenSimSet(dirout,
              stddev=0.0):

    dz=2e-3

    fnameout=os.path.join(dirout, "sim.fits")

    res, apmod=RandomSurface(4, dzlist=dz,  propdefoc=True,
                             stddev=stddev)

    SaveSet( res,
             [0 , -dz, dz],
             fnameout)

    CropFile(fnameout, 10e-4)

    PlotAperture(apmod,
                 os.path.join(dirout, "aperture"))
                 
    
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
                       valrange=valrange,
                       transf=2,
                       #contours=r[i].max() * (numpy.array([1.0, 0.8, 0.4, 0.1]))
                       
         )
        print list(r[i].max() * 2**(-1*numpy.arange(8)))
        

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

    box= [-0.6,0.6,-0.6,0.6]
    implot.plotmap(pyplot.Map(apmod.getphase()),
                   bbox=[x * s for x in box] ,
                   fout=pref+"-phase"+post ,
                   colmap="heat",
                   valrange=None,
                   contours=contours,
                   contcolour=0,
                   plotbox=False)

    implot.plotmap(pyplot.Map(apmod.getamp()),
                   bbox=[x * s for x in box] ,
                   fout=pref+"-amp"+post ,
                   colmap="heat",
                   valrange=None,
                   plotbox=False)

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
                   valrange=None , plotbox=False)
    implot.plotmap(fp,
                   bbox=[x * s for x in [-1,1,-1,1]] ,
                   fout="plots/perfect_farf_p.png/PNG",
                   colmap="heat",
                   valrange=None, plotbox=False)
    

    
    
def MPIfRIllus():

    r0, apmod=RandomSurface(5,0,3)
    PlotMapsSet(r0, pref="plots/mpifr-pfctsfc",
                eqrange=True, s=4e-4)

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

def PlotNoiseSims():

    for x in ["01", "05", "10"]:
        m1=pyplot.FitsMapLoad( "oofout/sim-%s-000/z4/aperture.fits" % x,
                               2)

        implot.plotmap(m1,
                       bbox=[xm * 6 for xm in [-1,1,-1,1]] ,
                       fout="plots/noise%sz4ap.png/PNG" % x,
                       colmap="heat",
                       valrange=[-1.0,1.0] )    

def PlotCorrelationMatrix(dirin):

    from matplotlib import pylab
    
    fnamein=os.path.join(dirin, "cvmatrix.csv")
    fnameout=os.path.join(dirin,"plots", "cvmatrix.png")    

    m=bnmin1io.LoadCVSFile(fnamein)
    pylab.clf()
    pylab.matshow(m)
    pylab.colorbar()
    pylab.savefig(fnameout)


def IntroTalkIntro():

    r0, apmod=RandomSurface(5, 0, dzlist=list(numpy.linspace(0, 3.0, 10)) )
    for i,rr in enumerate(r0):
        PlotMapsSet(rr, pref="plots/intro/introtalk-%i" % i,
                    eqrange=True, s=4e-4)

    r, apmod=RandomSurface(5,0.2, dzlist=list(numpy.linspace(0, 3, 10)) )
    PlotAperture(apmod ,
                 "plots/intro/impfc-aperture",
                 contour=True)    
    for i,rr in enumerate(r):    
        PlotMapsSet(rr, pref="plots/intro/impfc-%i" % i, 
                    eqrange=True)
    NoisyfySet(r[-1], 0.01)
    PlotMapsSet(r[-1], pref="plots/intro/impfc-noisy",
                eqrange=False)
        

    

#implot.plotmap(r[1], bbox=[x * 4e-4 for x in [-1,1,-1,1]] , colmap="heat")
