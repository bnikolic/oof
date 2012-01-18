# Bojan Nikolic
# $Id: oofillustrate.py,v 1.3 2006/12/03 20:41:36 bnikolic Exp $
#
# Make illustrations for an OOF talk

from localsetup import *

import pybnlib
import pyplot
import pyoof
import pybnmin1
import ooffitconv

import implot

def MkSimpleTel():

    tel1=pyoof.PrimeFocusGeo()                         
    tel1.PrimRadius=1
    tel1.PrimF=1

    return tel1

def PlotZern(nmax=6,
             contour=False):

    npix = 512
    tel1 = MkSimpleTel()
    
    m = pyplot.Map(npix, npix)
    pyplot.MkApCS(m, 1.2)

    mask = pyplot.Clone(m)
    tel1.DishMask(mask)

    for n in range(1,nmax):
        for i in range (0, n+1 ):
            l= -n + 2*i

            zfn=pybnlib.ZernPoly(n,l)
            pyplot.WorldSet( m , zfn)
            m.mult( mask)
            if contour:
                contours=implot.MkChopContours(m, ctype="lin", nlevels=5)
            else:
                contours=None
            implot.plotmap( m,
                            fout="plots/ZPoly-%i%i.png/PNG" % (n,l),
                            colmap="heat",
                            contours=contours,
                            contcolour=0)

def PlotZernLatexCmds(nmax):
    for n in range(1,nmax):
        for i in range (0, n+1 ):
            l= -n + 2*i
            print '\includegraphics[clip,width=0.16\columnwidth]{figs/zern/ZPoly-%i%i}&' %(n,l)
    


def ZPAll():

    for i in range( 16 , 17):
        ZernPower(i , 2)

def ZernPower(zn , dz):

    ""
    npix = 512
    tel1 = MkSimpleTel()
    m = pyplot.Map(npix, npix)
    
    apmod = pyoof.MkSimpleAp( tel1,
                              1e-3,
                              npix,
                              5,
                              4)

    amm=pybnmin1.ModelDesc( apmod.downcast() )
    amm.getbyname("z%i" % zn).setp(1)

    for cdz in [ 0 , dz, -1* dz]:
        amm.getbyname("z4" ).setp(cdz)

        farf= pyoof.FarF ( apmod.getphase(),
                           1e-3)

        farf.Power( apmod.getamp(), apmod.getphase(),  m)
        implot.plotmap( m, colmap="heat",
                        fout="plots/ZPpower-zn%i-dz%g.png/PNG" % ( zn , cdz ),
                        bbox=[-0.007, 0.007, -0.007,0.007])

def GenTable(nmax=21):

    for zn in range(1,nmax):
        oofn=zn
        n,l = ooffitconv.OOFktoOOFnl(zn)
        gbtn = ooffitconv.OOFktoSchwabk(zn)

        print """
    <tr>
  <td> n=%i, l=%i <br/>
       OOF=%i<br/>
       GBT=%i<br/>       
  </td>
  <td>
  <figure src="images/zern/ZPoly-%i%i.png" alt=""
      width="150" height="150" />
  </td>
  <td>
  <figure src="images/zern/ZPpower-zn%i-dz0.png" alt=""
      width="150" height="150" />
  </td>
  <td>
  <figure src="images/zern/ZPpower-zn%i-dz-2.png" alt=""
      width="150" height="150" />
  </td>
  <td>
  <figure src="images/zern/ZPpower-zn%i-dz2.png" alt=""
      width="150" height="150" />
  </td>
  </tr>
  """ % ( n, l, oofn, gbtn, n, l , zn, zn , zn)
  
    
def WhyDefocus(npix=256, zn=7, err=1,
               rnoise=0,
               pref="plots",
               valrange=[0,3e5]):

    tel1 = MkSimpleTel()
    m = pyplot.Map(npix, npix)
    mperf = pyplot.Map(npix, npix)
    
    apmod = pyoof.MkSimpleAp( tel1,
                              1e-3,
                              npix,
                              5,
                              4)

    amm=pybnmin1.ModelDesc( apmod.downcast() )
    amm.getbyname("z%i" % zn).setp(err)

    apmodperf = pyoof.MkSimpleAp( tel1,
                              1e-3,
                              npix,
                              5,
                              4)

    ammperf=pybnmin1.ModelDesc( apmodperf.downcast() )
    
    bbox= [-0.005, 0.005, -0.005,0.005]
    for cdz in [ 0 , 0.5  , 1 , 2 , 5]:
        amm.getbyname("z4" ).setp(cdz)
        ammperf.getbyname("z4" ).setp(cdz)

        farf= pyoof.FarF ( apmod.getphase(),
                           1e-3)

        farf.Power( apmod.getamp(), apmod.getphase(),  m)
        farf.Power( apmodperf.getamp(), apmodperf.getphase(),  mperf)

        #use this to add random noise:
        if cdz == 0:
            maxlevel=mperf.max()

        if rnoise != 0:
            mnoise=pyplot.Map(npix, npix)
            pyplot.NormDist(mnoise, maxlevel * rnoise)
            m.add(mnoise)
        
        implot.plotmap( m,
                        colmap="heat",
                        fout=os.path.join(pref,
                                          "LWhydefocux-zn%i-dz%g-n%g.png/PNG" % ( zn , cdz, rnoise ) ),
                        bbox=bbox,
                        valrange=valrange)

        mperf.mult(-1)
        m.add(mperf)
        implot.plotmap( m,
                        colmap="heat",
                        fout=os.path.join(pref,
                                          "LDiffWhydefocux-zn%i-dz%g-n%g.png/PNG" % ( zn , cdz, rnoise )),
                        bbox=bbox)
                        
    
def FarFRes( apmod, wl):

    farf= pyoof.FarF ( apmod.getphase(),wl )

    mamp = pyplot.Map( apmod.getphase() )
    mphase = pyplot.Map( apmod.getphase() )
    mpower = pyplot.Map( apmod.getphase() )


    farf.Power( apmod.getamp(), apmod.getphase(),  mpower)
    farf.AmpPhase( apmod.getamp(), apmod.getphase(),  mamp, mphase)

    return mamp, mphase, mpower
