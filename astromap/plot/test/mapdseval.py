# Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>
# Initial version May 2007
# Rev. Jan 2008
#
# Testing for routines which make interpolations from maps.

import setup

import pyplot
import implot

m1=pyplot.Map(128,128)

lc=pyplot.MkGaussCoffs( 64, 64, m1, 1.0 , 3.0)

# should be zero of course...
print lc(m1, 1100)

lc2=pyplot.MkCircleCoeffs(64,64, m1, 3)


xx=pyplot.MkBiLinearCoeffs(1,1, m1)
xx._print()
