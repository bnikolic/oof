# Bojan Nikolic
# May 2007
#
# Tests of the Fresenel code

import sys
sys.path.extend(["/import/appcs/bn204/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

import pyplot
import pyoof
import implot

if 0:
    m = pyplot.Map(128,128)
    x=pyplot.dFresnelDir( m, 64, 64, 100)

tel=pyoof.TelSwitch("ALMA")

mamp=pyoof.MkApMap(tel, 128, 4.0)
ilmod=pyoof.GaussAmpMod( tel, mamp)
ilmod.SetSigma(0.3)
ilmod.Calc(mamp)
m3=pyplot.Map(mamp)
implot.plotmap(m3)
