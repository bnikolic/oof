# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# GBT single beam illustraton



def MkGBT():

    tel=pyoof.TelSwitch("GBT")
    npix = 512
    
    apmod = pyoof.MkSimpleAp( tel,
                              7e-3,
                              npix,
                              4,
                              4)

    return apmod , tel

def MkDefocusBeam(dz, apmod,tel):

    phasemap=pyplot.Map( apmod.getphase() )
    phasemap.mult(0)
    res=pyplot.Map( apmod.getphase().nx,apmod.getphase().ny)

    tel.MkDefocus(dz, phasemap)

    farf=pyoof.FarF ( apmod.getphase(),
                      7e-3)


    farf.Power( apmod.getamp(),
                phasemap,
                res)

    return phasemap, res
    


