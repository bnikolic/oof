# Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>
# May 2007
#
# Testing for routines which make interpolations from maps.

import sys
sys.path.extend(["/home/bnikolic/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

import pyplot
import implot

m1=pyplot.Map(128,128)

lc=pyplot.MkGaussCoffs( 64, 64, m1, 1.0 , 3.0)

# should be zero of course...
print lc(m1, 1100)

lc2=pyplot.MkCircleCoeffs(64,64, m1, 3)
