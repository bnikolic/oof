# Tests/illustrations of the parametrised geometry

from setup import *

import pyoof


import pyplot
import pyoof
import implot





R=3
g=pyoof.ParamGeo(R, pyoof.ParsetVect( [ pyoof.ParPair("z3", 1.9) ]))

npix=512
m = pyplot.Map(npix, npix)
pyplot.MkApCS(m, R * 1.2)

g.MkDefocus(1, m)

implot.plotmap(m, colmap="heat", 
               contours=implot.MkChopContours(m, ctype="lin"),
               plotbox=False
)
