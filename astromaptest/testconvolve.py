# Bojan Nikolic
# $Id: testconvolve.py,v 1.1 2006/02/16 00:03:21 bnikolic Exp $
#
# Test the convolution procedures

import pyplot
import implot


m1 = pyplot.Map(100, 100)
m1.set(50,50, 10)

m2 = pyplot.Map(100, 100)
m2.set(50,50, 10)
m2.set(50,51, 10)
m2.set(51,50, 10)
m2.set(51,51, 10)

m2 = pyplot.FFTConvolve(m1,m2)


