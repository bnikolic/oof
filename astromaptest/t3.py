# Bojan Nikolic
# Tests of the OOF system
#

import pyoof
import oofreduce
import implot
import pyplot

import pybnmin1


#oc=oofreduce.MkObsCompare("/home/bnikolic/temp/oofsample.fits")
oc=oofreduce.MkObsCompare("/home/bnikolic/temp/s114-l-db.fits")

def pb(oc,i):

    m = oc.Beam(i)
    mm = pyplot.Map(m)
    implot.plotmap(mm, colmap="heat")


if 0:
    ds1=pyplot.LoadFITSDS("/home/bnikolic/temp/s114-l-db.fits",3)
    pyplot.SimpleDrizzle( ds1, mm, 2 , 4)    

#lmm=pybnmin1.LMMin(oc.downcast())
#lmm.getbyname("sigma").setp(3)
#lmm.mon = pybnmin1.ChiSqMonitor()


if 0:
    tel1=pyoof.TelSwitch("GBT")
    m = pyplot.Map(128,128)
    pyplot.MkApCS(m, 70)
    tel1.DishMask(m)
    implot.plotmap(m, colmap="heat")
    pyplot.FitsWrite(m, "!test.fits")



