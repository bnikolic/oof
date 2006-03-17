# Bojan Nikolic
# $Id: moonscanpp.py,v 1.3 2006/03/17 17:08:18 bnikolic Exp $
#
# Pretty plotting of the moonscan data
#

import pyfits
import numarray
import pyxplot

def PlotObsData():

    dnorm= pyfits.open("moonscand/obs75_full.fits")[1].data
    drand= pyfits.open("moonscand/obs79_full.fits")[1].data

    pyxplot.vect( [ dnorm.field("dx") , drand.field("dx")] ,
                  [ dnorm.field("fnu") - dnorm.field("fnu").max() ,
                    drand.field("fnu") - drand.field("fnu").max()] ,
                  "plots/obsdata.eps",
                  xax=pyxplot.axis("Azimuth Offset (arcmin)",
                                   xmin=None, xmax=None),
                  yax=pyxplot.axis("Rel Gain  (B)",
                                   xmin=-3),
                  multi=1,
                  width=pyxplot.THESIS)

def PlotModData(modname, fnameout):

    obsd=pyfits.open("moonscand/obs75.fits")[1].data

    m250 = pyfits.open(modname)[1].data

    pyxplot.vect( [ obsd.field("dx") , m250.field("dx")] ,
                  [ obsd.field("fnu") - obsd.field("fnu").max() ,
                    m250.field("fnu") - m250.field("fnu").max()] ,
                  fnameout,
                  xax=pyxplot.axis("Azimuth Offset (arcmin)",
                                   xmin=None, xmax=None),
                  yax=pyxplot.axis("Rel Gain  (B)",
                                   xmin=-3),
                  multi=1,
                  width=pyxplot.THESIS)

def PlotModDataR(modname, fnameout):

    obsd=pyfits.open("moonscand/obs75-right.fits")[1].data

    m250 = pyfits.open(modname)[1].data

    pyxplot.vect( [ obsd.field("dx") , m250.field("dx")] ,
                  [ obsd.field("fnu") - obsd.field("fnu").max() ,
                    m250.field("fnu") - m250.field("fnu").max()] ,
                  fnameout,
                  xax=pyxplot.axis("Azimuth Offset (arcmin)",
                                   xmin=None, xmax=None),
                  yax=pyxplot.axis("Rel Gain  (B)"),
                  multi=1,
                  width=pyxplot.THESIS)    

def CmpRandom():

    obsd=pyfits.open("moonscand/obs75.fits")[1].data

    m250 = pyfits.open("moonscand/obs79.fits")[1].data

    pyxplot.vect( [ obsd.field("dx") , m250.field("dx")] ,
                  [ obsd.field("fnu") - obsd.field("fnu").max() ,
                    m250.field("fnu") - m250.field("fnu").max()] ,
                  "plots/moonscanobscom.eps",
                  xax=pyxplot.axis("Azimuth Offset (arcmin)",
                                   xmin=None, xmax=None),
                  yax=pyxplot.axis("Rel Gain  (B)"),
                  multi=1,
                  width=pyxplot.THESIS)

def CmpRandomV2():

    obsd=pyfits.open("moonscand/obs79.fits")[1].data

    m250 = pyfits.open("moonscand/model500rms.fits")[1].data

    pyxplot.vect( [ obsd.field("dx") , m250.field("dx")] ,
                  [ obsd.field("fnu") - obsd.field("fnu").max() ,
                    m250.field("fnu") - m250.field("fnu").max()] ,
                  "plots/moonscanrandcom.eps",
                  xax=pyxplot.axis("Azimuth Offset (arcmin)",
                                   xmin=None, xmax=None),
                  yax=pyxplot.axis("Rel Gain  (B)"),
                  multi=1,
                  width=pyxplot.THESIS)    
    

def doPlotsV2():

    PlotModData( "moonscand/big250.fits",
                 "plots/moonscanmod250comp.eps")
    
def doPlots():

    PlotModData( "moonscand/model250rms.fits",
                 "plots/moonscanmod250comp.eps")

    PlotModDataR( "moonscand/model250rms-right.fits",
                 "plots/moonscanmod250comp-right.eps")

    PlotModData( "moonscand/model350rms.fits",
                 "plots/moonscanmod350comp.eps")

    PlotModData( "moonscand/model125rms.fits",
                 "plots/moonscanmod125comp.eps")

    PlotModData( "moonscand/model25pans.fits",
                 "plots/moonscanmod25pans.eps")
