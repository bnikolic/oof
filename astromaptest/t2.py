# Bojan Nikolic
# Do tests by plotting zernikes

import pyplot
import pyoof
import implot
import pybnmin1


tel1=pyoof.TelSwitch("ALMA")

m = pyplot.Map(128,128)
pyplot.MkApCS(m, 8)
tel1.DishMask(m)

if 0:
    fftf=pyplot.FFTFact( m.nx , m.ny  , pyplot.FFTFact.forward , pyplot.FFTFact.center)

    m2 = pyplot.Map(128,128)
    m3 = pyplot.Map(128,128)
    fftf.FFTAmpPh_Power(m, m2 , m3)

#implot.plotmap(m3, colmap="heat", transf=1)

if 0:
    ds1=pyplot.LoadFITSDS("/home/bnikolic/m/v/prog/cpp/adas/oof/analysis/apex/temp/mars1-db-029/model-ds.fits" , 2)
    #ds1=pyplot.LoadFITSDS("/home/bnikolic/m/v/prog/cpp/adas/oof/analysis/apex/temp/mars1-db-029/tt.fits" , 2)
    m4 = pyplot.Map(128,128)
    pyplot.MkApCS(m4, 4.8e-6*100)
    pyplot.SimpleDrizzle( ds1, m4, 5 , 3)
    implot.plotmap( m4, colmap="heat")


if 0:
    mlc= pyplot.LCMaps()
    pyplot.NormDist(m, 1)
    mlc.AddMap(m)

    pyplot.NormDist(m, 1)
    mlc.AddMap(m)

    mlc.setc(0,1)
    mlc.Calc(m)
    implot.plotmap( m, colmap="heat")

if 0:

    oversamp  =3
    mamp = pyoof.MkApMap( tel1, 128, oversamp )
    mphase = pyoof.MkApMap( tel1, 128, oversamp )

    farf= pyoof.FarF ( mamp, 1.1e-3) 


    zm=pyoof.RZernModel( 5, mphase , tel1)
    zmm=pybnmin1.ModelDesc( zm.downcast() )
    zmm.getbyname("z3").setp(2)
    zmm.getbyname("z5").setp(1)
    zm.Calc(mphase)

    im=pyoof.GaussAmpMod(tel1, mphase)
    im.Calc(mamp)

    farf.Power( mamp, mphase, m)
    implot.plotmap( m, colmap="heat")

if 0:

    apmod = pyoof.MkSimpleAp( tel1,
                              1.1e-3,
                              128,
                              5,
                              3)

    
    amm=pybnmin1.ModelDesc( apmod.downcast() )

    amm.getbyname("z3").setp(2)
    amm.getbyname("z5").setp(1)

    farf= pyoof.FarF ( apmod.getphase(),
                       1.1e-3)

    farf.Power( apmod.getamp(), apmod.getphase(),  m)
    implot.plotmap( m, colmap="heat")
    
    
