# Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>,
# <b.nikolic@mrao.cam.ac.uk>
#
# Utilities for plotting OOF data

import os

import pyfits
import numpy

import implot
import pyplot
import pyoof
import pybnmin1
import bnmin1io


import oofreduce
import oofcol

def PlotDir(dirnamein, bbox=None, hardcopy=False, odir="plots",
            fwhm=None , extent = None, npix= None,
            ncont=None,
            decorate=True,
            obsdir=None):

    "Make all the relevant plots"

    """

    If( hardcopy) make hardcopy friendly plots

    if obsdir is set look for observed data sets here

    """
    if obsdir != None:
        rname=        obsdsfname=  oofcol.getpar(dirnamein,  "fitinfo.fits", "obsfilename")
        obsdsfname=  os.path.join( obsdir, os.path.basename(rname))
    else:
        obsdsfname=  oofcol.getpar(dirnamein,  "fitinfo.fits", "obsfilename")
        
    npix= npix or int(oofcol.getpar(dirnamein,  "fitinfo.fits", "npix") )
    oversample= float( oofcol.getpar(dirnamein,  "fitinfo.fits", "oversample") )
    fwhm=fwhm or float(oofcol.getpar(dirnamein,  "fitinfo.fits", "ds_fwhm") )
    extent=extent or float(oofcol.getpar(dirnamein,  "fitinfo.fits", "ds_extent") )

    PlotDSFile( obsdsfname,
                os.path.join(dirnamein, odir),
                prefix="obsbeam",
                oversample= oversample,
                npix=npix,
                fwhm=fwhm,
                extent=extent,
                bbox=bbox,
                ncont=ncont,
                hardcopy=hardcopy,
                decorate=decorate)

    PlotSimDrizzleBeams( obsdsfname,
                         os.path.join(dirnamein, "fitbeams.fits"),
                         os.path.join(dirnamein, odir),
                         prefix="bestfitbeams",
                         bbox=bbox,
                         fwhm=fwhm,
                         extent=extent,
                         npix=npix,
                         oversample=oversample,
                         ncont=ncont,
                         hardcopy=hardcopy,
                         decorate=decorate)

    PlotSimDrizzleBeams( obsdsfname,
                         os.path.join(dirnamein, "perfectbeams.fits"),
                         os.path.join(dirnamein, odir),
                         prefix="perfectbeams",
                         bbox=bbox,
                         fwhm=fwhm,
                         extent=extent,
                         npix=npix,
                         oversample=oversample,
                         ncont=ncont,
                         hardcopy=hardcopy,
                         decorate=decorate)

    PlotAperture( os.path.join(dirnamein, "aperture-notilt.fits"),
                  os.path.join(dirnamein, odir),
                  oversample=oversample,
                  hardcopy=hardcopy)

    if os.access( os.path.join(dirnamein, "offsetbeams.fits"),
                  os.F_OK):
        PlotSimDrizzleBeams( obsdsfname,
                             os.path.join(dirnamein, "offsetbeams.fits"),
                             os.path.join(dirnamein, odir),
                             prefix="offsetbeams",
                             bbox=bbox,
                             fwhm=fwhm,
                             extent=extent,
                             npix=npix,
                             oversample=oversample,
                             ncont=ncont,
                             hardcopy=hardcopy,
                             decorate=decorate)

        PlotAperture( os.path.join(dirnamein, "aperture-offset.fits"),
                      os.path.join(dirnamein, odir),
                      oversample=oversample,
                      prefix="offsetaperture",
                      hardcopy=hardcopy)
        
                         

    
def MkFFMap (fnamein,
             npix=128,
             oversample=2.0):

    "Create the far field map with correct coordinate system"

    
    wavel= oofreduce.GetObsWaveL(fnamein)
    ap =oofreduce.MkSampleAp(fnamein)
    m=pyplot.Map(npix,npix)
    
    pyoof.SetFarFCS( ap.getphase() ,
                     wavel,
                     m);
    return m

    
    

def PlotDSFile( fnamein,
                dirout,
                prefix="beam",
                npix=128,
                oversample=2.0,
                fwhm=2.0,
                extent=4.0,
                bbox=None,
                ncont=None,
                hardcopy=False,
                decorate=True
               ):
    "Plot beams contained in a dataseries file"

    fin=pyfits.open(fnamein)

    m= MkFFMap( fnamein, npix=npix, oversample=oversample)

    #Create the output directory if necessary
    if not os.path.exists(dirout):
        os.makedirs(dirout)

    if hardcopy : end=".eps/CPS"
    else:         end=".png/PNG"        

    for i in range(1,len(fin)):
        ds1=pyplot.LoadFITSDS(fnamein,i+1)

        pyplot.SimpleDrizzle( ds1, m, fwhm , extent)    
        implot.plotmap( m,
                        fout=os.path.join(dirout,
                                          prefix + "-%i%s" % (i, end) ),
                        colmap="heat",
                        bbox=bbox,
                        contours=ncont and implot.MkChopContours(m, nlevels=ncont),
                        plotbox=decorate,
                        plotwedge=decorate)
                                          

def PlotSimDrizzleBeams(obsfilename, beamfilename,
                        dirout,
                        prefix="simdrizbeam",
                        fwhm=1.0, extent=2.0,
                        oversample=2.0,
                        npix=128,
                        bbox=None,
                        ncont=None,
                        hardcopy=False,
                        decorate=True):

    "Create a simulated ds from model beams and then drizzle"

    ds = oofreduce.SimBeamDS(obsfilename, beamfilename)

    if hardcopy : end=".eps/CPS"
    else:         end=".png/PNG"

    for i in range(len(ds)):
        skym=MkFFMap(obsfilename, npix=npix, oversample=oversample)
        pyplot.SimpleDrizzle( ds[i], skym, fwhm , extent)
        implot.plotmap(skym,
                       fout=os.path.join(dirout,
                                         prefix + "-%i%s" % (i, end) ),
                       colmap="heat",
                       bbox=bbox,
                       contours=ncont and implot.MkChopContours(skym, nlevels=ncont),
                       plotbox=decorate,
                       plotwedge=decorate
                       )

def PlotAperture(apfname,
                 dirout,
                 prefix="aperture",
                 oversample=2.0,
                 hardcopy=False):

    "Plot aperture phase and amplitude"

    phasemap=pyplot.FitsMapLoad(apfname,2)
    ampmap  =pyplot.FitsMapLoad(apfname,1)    

    bbox = implot.GetMapBBox(phasemap)
    bbox = [ x/oversample *1.05 for x in bbox]

    if hardcopy:
        end=".eps/PS"
        contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2]
        colmap=None
    else:
        end=".png/PNG"
        contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2]
        colmap="heat"

    implot.plotmap( phasemap,
                    fout=os.path.join(dirout,
                                      prefix+"-phase"+end),
                    bbox=bbox,
                    colmap=colmap,
                    contours=contours,
                    contcolour=0,
                    title=apfname)

    implot.plotmap( ampmap,
                    fout=os.path.join(dirout,
                                      prefix+"-amplitude"+end),
                    bbox=bbox,
                    colmap=colmap   )


def MkApFile(fnamein,
             npix=256,
             telgeo=pyoof.GBTGeo()):

    "Make the aperture phase, illumination pair from a file"

    mphase = pyplot.Map(npix,npix)
    pyplot.MkApCS(mphase, telgeo.DishEffRadius() * 1.05)

    zm = pyoof.RZernModel ( 5 , mphase , telgeo )

    md=pybnmin1.ModelDesc(zm.downcast())

    bnmin1io.FLoad( md, fnamein, silent=True)

    for zn in ["z1" ,"z2"  ] :
        md.getbyname(zn).setp(0)

    zm.Calc(mphase)

    mamp = pyplot.Map(npix,npix)
    pyplot.MkApCS(mamp, telgeo.DishEffRadius() * 1.05)

    im = pyoof.GaussAmpMod ( telgeo , mamp  )

    md=pybnmin1.ModelDesc(im.downcast())
    bnmin1io.FLoad( md, fnamein, silent=True)

    im.Calc(mamp)

    return mphase, mamp

    
    

def PlotZernFile( fnamein,
                  fnameout,
                  npix=256,
                  telgeo=pyoof.GBTGeo(),
                  phaserange=None,
                  plotwedge=True):

    #Should convert this to use MkApFile
    m = pyplot.Map(npix,npix)
    pyplot.MkApCS(m, telgeo.DishEffRadius() * 1.05)

    zm = pyoof.RZernModel ( 5 , m , telgeo )

    md=pybnmin1.ModelDesc(zm.downcast())

    bnmin1io.FLoad( md, fnamein, silent=True)

    for zn in ["z1" ,"z2"  ] :
        md.getbyname(zn).setp(0)

    zm.Calc(m)

    implot.plotmap( m,
                    fnameout,
                    colmap="heat",
                    contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2],
                    valrange=phaserange,
                    plotwedge=plotwedge)
    return m

def PlotZernDict(d,
                 fnameout,
                 npix=256,
                 telgeo=pyoof.GBTGeo(),
                 phaserange=None,
                 plotwedge=True):
    """
    Plot aperture phase distribution from a dictionary of Zernike
    polynomial coefficients.
    
    :param d: dictionary with zernike coefficients, in OOF numbering
    convention; i.e., { "z4" : 1.0 } means one radian of classical
    defocus

    :param fnameout: Name of file to plot to; PGPLOT convention
    
    :param npix: Size of map in pixels to rasterise the aperture on
    
    :param telgeo: Telescope geometry (used just for dish radius)

    :returns: the plotted map

    """

    m = pyplot.Map(npix,npix)
    pyplot.MkApCS(m, telgeo.DishEffRadius() * 1.05)

    zm = pyoof.RZernModel (5, 
                           m, 
                           telgeo )

    md=pybnmin1.ModelDesc(zm.downcast())
    for k in d.keys():
        if k not in ["z1", "z2"] and k[0]=="z":
            md.getbyname(k).setp(float(d[k]))

    zm.Calc(m)

    implot.plotmap( m,
                    fnameout,
                    colmap="heat",
                    contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2],
                    valrange=phaserange,
                    plotwedge=plotwedge)
    return m

    
def PlotIllumFile( fnamein,
                   fnameout,
                   npix=256,
                   telgeo=pyoof.GBTGeo()):

    "Plot illumination from a paremeter file"

    #Should convert this to use MkApFile
    m = pyplot.Map(npix,npix)
    pyplot.MkApCS(m, telgeo.DishEffRadius() * 1.05)

    im = pyoof.GaussAmpMod ( telgeo , m  )

    md=pybnmin1.ModelDesc(im.downcast())

    bnmin1io.FLoad( md, fnamein, silent=True)

    im.Calc(m)

    implot.plotmap( m,
                    fnameout,
                    colmap="heat"                  )

    return m


def dsToArray(ds):
    """Convert a data series to a numpy array"""
    res=[]
    for i in range(ds.length()):
        x=ds.getp(i)
        res.append([x.dX, x.dY, x.fnu, x.ufnu])
    return numpy.array(res)


def dsObsModel(obsfilename,
               beamfilename):
    """Return the observed and the model data series
    
    :param obsfilename: FITS file containing the observed time-stream
    data
    
    :param beamfilename: FITS file containing simulated beams. This would 
    typically be one of the "fitbeams.fits" files in the oofout directory.
    
    :returns: A list with one entry for each defocus setting, in same
    order as in the obsfilename observation file. 
    
    Each entry in this list is itself a list of two entries. The first
    is the observed flux data, the second is an array representation
    of model data. This array has columns "dx", "dy", "fnu", "ufnu"
    just as in FITS file. Therefore the flux (usually the quantitity
    of interest) is in the third column of this array!

    :note: Data are kept in same order as in the input file. This
    means that for multi-pixel mustang data, data belonging to each
    pixel will stay together.

    For example, to plot observed and model data:

    >>> r=oofplot.dsObsModel("td/allpx-noqd.fits", "oofout/allpx-noqd-000/z5/fitbeams.fits")
    >>> pylab.plot(r[0][0]) # First defocus setting, original data
    >>> pylab.plot(r[0][1][:,2]) # First defocus setting, model flux

    """
    res=[]
    sl=oofreduce.SimBeamDS(obsfilename,beamfilename)
    fin=pyfits.open(obsfilename)
    for i in range(len(sl)):
        x=dsToArray(sl[i])
        xo=fin[i+1].data.field("fnu")
        res.append( [xo,x])
    return res
    

def mkFlicker(fnamel,
              fnameout,
              delay=40
              ):
    """
    Make a flicker GIF of files in fnamel
    """
    cmdline="convert -delay %i "
    for fname in fnamel:
        cmdline+= (fname+" ")
    cmdline+=fnameout
    sw, sr = os.popen2(cmdline)
    
def makeHTML(dirin):
    """
    Make an HTML summary page  (from D. Barkats)
    """
    fldir=os.path.join(dirin, "flicker")
    if not os.path.exists(fldir):
        os.mkdir(fldir)
    
    for i in range(3):
        mkFlicker([os.path.join(dirin, 
                                "plots",
                                "obsbeam-%i.png" % (i+1)),
                   os.path.join(dirin, 
                                "plots",
                                "bestfitbeams-%i.png" % (i)),],
                  os.path.join(fldir,
                               "beam%i_flick.gif" % (i+1)))
    
    outfile=open(os.path.join(dirin,
                              'flicker.html'),
                 'w')
    outfile.write('<html><head><title>Plots for %s</title></head><body> \n' %(dirin))
    outfile.write('<center> \n')
    outfile.write('<h2>Flicker Plots for %s </h2>\n ' %(dirin))
    outfile.write('</center> \n \n ')
    outfile.write('<a href="flicker/beam1_flick.gif"><img src=flicker/beam1_flick.gif width=25%></a> \n')
    outfile.write('<a href="flicker/beam2_flick.gif"><img src=flicker/beam2_flick.gif width=25%></a> \n')
    outfile.write('<a href="flicker/beam3_flick.gif"><img src=flicker/beam3_flick.gif width=25%></a> \n')
    outfile.write('</body> \n ')
    outfile.write(' </html>  \n ')
    outfile.close()

    outfile=open(os.path.join(dirin,
                              'plots.html'),
                 'w')
    outfile.write('<html><head><title>Plots for %s</title></head><body> \n' %(dirin))
    outfile.write('<center> \n')
    outfile.write('<h2>Plots for %s </h2>\n ' %(dirin))
    outfile.write('</center> \n \n ')
    outfile.write('<p> \n <table border=1, cellpadding=5> \n')
    outfile.write('<tr><td> Aperture amplitude </td><td> Aperture phase </td> </tr>\n' )

    outfile.write("""
<tr><td><a href="plots/aperture-amplitude.png"><img src="plots/aperture-amplitude.png" width=300></a></td>\n
    <td><a href="plots/aperture-phase.png"><img src="plots/aperture-phase.png" width=300></a></td>
</tr> \n
                 """)

    outfile.write(' </table>\n ')
    outfile.write('<p> \n <table border=1, cellpadding=0> \n')
    outfile.write('<tr><td> Observed beam 1 </td><td> Observed beam 2 </td> <td> Observed beam 3 </td> \n <td> best fit beams 1 </td> <td>  best fit beams 2 \
</td>  <td>  best fit beams 3  </td>  <td> Perfect beams 1</td>  <td> Perfect beams 2 </td>  <td> Perfect beams 3  </td> </tr>\n' )
    outfile.write('<tr><td><a href="plots/obsbeam-1.png"><img src="plots/obsbeam-1.png" width=150></a></td> \n <td><a href="plots/obsbeam-2.png"><img src="pl\
ots/obsbeam-2.png" width=150></a></td> \n<td><a href="plots/obsbeam-3.png"><img src="plots/obsbeam-3.png" width=150></a></td><td><a href="plots/bestfitbeams\
-0.png"><img src="plots/bestfitbeams-0.png" width=150></a></td> \n <td><a href="plots/bestfitbeams-1.png"><img src="plots/bestfitbeams-1.png" width=150></a>\
</td> \n<td><a href="plots/bestfitbeams-2.png"><img src="plots/bestfitbeams-2.png" width=150></a></td> \n <td><a href="plots/perfectbeams-0.png"><img src="p\
lots/perfectbeams-0.png" width=150></a></td> \n <td><a href="plots/perfectbeams-1.png"><img src="plots/perfectbeams-1.png" width=150></a></td> \n<td><a href\
="plots/perfectbeams-2.png"><img src="plots/perfectbeams-2.png" width=150></a></td></tr> \n ')
    outfile.write(' </table> <p>\n ')

    outfile.write('<a href="flicker.html">Flicker plots between observed beams and best fit beams</a> \n')
    outfile.write('</body> \n ')
    outfile.write(' </html>  \n ')
    outfile.close()
    
             
    


        

