# Bojan Nikolic
# Tests of the OOF system
#

import pyoof
import oofreduce
import implot
import pyplot

import pybnmin1
import bnmin1io


#oc=oofreduce.MkObsCompare("/home/bnikolic/temp/oofsample.fits")

def pb(oc,i):

    m = oc.Beam(i)
    mm = pyplot.Map(m)
    implot.plotmap(mm, colmap="heat")


oldlmm = []
for nzern in range(1,2):

    print "Nzern = %i " % nzern

    oc=oofreduce.MkObsCompare("/home/bnikolic/temp/s114-l-db.fits", nzern=nzern)

    lmm=pybnmin1.LMMin(oc.downcast())

    m1 = pybnmin1.ChiSqMonitor()
    m1.thisown = 0
    lmm.AddMon( m1)

    lmm.getbyname("beamgainf").dofit=1


    if len(oldlmm) != 0 :
        bnmin1io.FLoad(lmm, oldlmm[-1])
    
    lmm.solve()

    pyoof.WriteAperture(oc, "!t5.%iap.fits"%nzern)

    fitname = "t5.%ifit.fits" % nzern
    bnmin1io.FSave(lmm, fitname)
    oldlmm.append(fitname)




if 0:
    tel1=pyoof.TelSwitch("GBT")
    m = pyplot.Map(128,128)
    pyplot.MkApCS(m, 70)
    tel1.DishMask(m)
    implot.plotmap(m, colmap="heat")
    pyplot.FitsWrite(m, "!test.fits")



