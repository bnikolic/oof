# Bojan Nikolic
# $Id: oofillustrate.py,v 1.2 2005/10/20 19:46:18 bnikolic Exp $
#
# Make illustrations for an OOF talk

import pybnlib
import pyplot
import pyoof
import pybnmin1

import implot

def MkSimpleTel():

    tel1=pyoof.PrimeFocusGeo()                         
    tel1.PrimRadius=1
    tel1.PrimF=1

    return tel1

def PlotZern(nmax=6):

    npix = 512
    tel1 = MkSimpleTel()
    
    m = pyplot.Map(npix, npix)
    pyplot.MkApCS(m, 1.2)

    mask = pyoof.Clone(m)
    tel1.DishMask(mask)

    for n in range(1,nmax):
        for i in range (0, n+1 ):
            l= -n + 2*i

            zfn=pybnlib.ZernPoly(n,l)
            pyplot.WorldSet( m , zfn)
            m.mult( mask)

            implot.plotmap( m,
                            fout="plots/ZPoly-%i%i.eps/CPS" % (n,l),
                            colmap="heat")

    # Plot inverted 5,1
    zfn=pybnlib.ZernPoly(5,1)
    pyplot.WorldSet( m , zfn)
    m.mult( mask)
    m.mult(-1)
    
    implot.plotmap( m,
                    fout="plots/ZPoly-51-inv.eps/CPS" ,
                    colmap="heat")

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
                        fout="plots/ZPpower-zn%i-dz%g.eps/CPS" % ( zn , cdz ),
                        bbox=[-0.007, 0.007, -0.007,0.007])
    
    
