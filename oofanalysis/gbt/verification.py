# Bojan Nikolic
# $Id: verification.py,v 1.5 2007/01/13 16:50:45 bnikolic Exp $
#
# Plot OOF verification results

import string

from setup import *

import pyxplot
from pyx import *
from pyxplot import graph

# Format of data file
#Source   Scan Pol El    UT    Antenna Temp.    Aperture Eff.   Model

def ParseData(fin):

    """
    Format of data file:
    Source   Scan Pol El    UT    Antenna Temp.    Aperture Eff.   Model    
    """

    res = []
    for line in fin:
        ld=string.split(line)
        if len(ld) > 1:
            pol= ld[2]
            src = ld[0]
            elev=float(ld[3])
            uttime=float(ld[4])

            apeff= float(ld[8])
            apefferr= float(ld[10])
            model   = ld[11]

            if model == "(None)":
                model = 0
            elif model == "(2005SpringV1)" :
                model = "2005SpringV1" 
            elif model == "(2005WinterV1)" :
                model = "2005WinterV1"

            res.append ( ( pol, elev,( apeff, apefferr ) , model , src, uttime))

    return res

def PlotGain( d,
              model,
              utmin=0,
              utmax=24,
              mineff=0.2,
              maxeff=0.5,
              src=None):

    def ProcD(d2):

        pt=[]
        md = {}

        for x in d2:
            if md.has_key(x[4] ):
                md[x[4]].append (  ( x[1 ] , x[2][0] , x[2][1]  ) )
            else:
                md[x[4]]= [ ( x[1 ] , x[2][0] , x[2][1]  ) ]

        for i,k in enumerate(md.keys()):
            print "Series %i  is %s " % ( i, k)
            pt.append( pyxplot.graph.data.list( md[k], x=1, y=2, dy=3))

        return pt
        
    if src == None:
        rcpnone = [ x for x in d if x[0]=="RCP" and x[3]==0 and x[5] > utmin and x[5] < utmax ]
        rcpv1 = [ x for x in d if x[0]=="RCP" and x[3]==model and x[5] > utmin and x[5] < utmax ]
    else:
        rcpnone = [ x for x in d if x[0]=="RCP" and x[3]==0 and x[5] > utmin and x[5] < utmax and x[4] ==src ]
        rcpv1 = [ x for x in d if x[0]=="RCP" and x[3]==model and x[5] > utmin and x[5] < utmax and x[4]==src]


    pt      = [ pyxplot.graph.data.list( rcpnone, x=1, y=2, dy=3),
                pyxplot.graph.data.list( rcpv1, x=1, y=2, dy=3),                
                ]

    c = canvas.canvas()
    
    gon = c.insert(pyxplot.graph.graphxy(width=pyxplot.MNRAS_SC,
                                          x=pyxplot.axis(r"$E\,$(degrees)",
                                                         xmin=0, xmax=90) ,
                                          y=pyxplot.axis(r"$\eta_{\rm a}$",
                                                         xmin=mineff, xmax=maxeff),
                                          ))
    gon.plot(ProcD(rcpv1),
             [ graph.style.symbol(graph.style.symbol.changesquare,
                                  symbolattrs=[deco.filled()]
                                  ),
               graph.style.errorbar()
               ]
             )

    goff  = c.insert(pyxplot.graph.graphxy(width=pyxplot.MNRAS_SC,
                                           ypos =gon.height+0.5,
                                           x=graph.axis.linkedaxis(gon.axes["x"]),
                                           y=pyxplot.axis(r"$\eta_{\rm a}$",
                                                          xmin=mineff, xmax=maxeff),
                                           ))

    goff.plot(ProcD(rcpnone),
             [ graph.style.symbol(graph.style.symbol.changesquare),
               graph.style.errorbar()
               ]
             )


    c.writetofile("plots/gaincurve.eps")
    c.writetofile("plots/gaincurve.pdf")

    gon=pyxplot.graph.graphxy(width=pyxplot.MNRAS_SC,
                              x=pyxplot.axis(r"$E\,$(degrees)",
                                             xmin=0, xmax=90) ,
                              y=pyxplot.axis(r"$\eta_{\rm a}$",
                                             xmin=mineff, xmax=maxeff),
                              )
    
    gon.plot(ProcD(rcpv1),
             [ graph.style.symbol(graph.style.symbol.changesquare,
                                  symbolattrs=[deco.filled()]
                                  ),
               graph.style.errorbar()
               ]
             )
             
    gon.writetofile("plots/gaincurve_on.pdf")

    goff  = pyxplot.graph.graphxy(width=pyxplot.MNRAS_SC,
                                  x=pyxplot.axis(r"$E\,$(degrees)",
                                                 xmin=0, xmax=90) ,
                                  y=pyxplot.axis(r"$\eta_{\rm a}$",
                                                 xmin=mineff, xmax=maxeff),
                                  )

    goff.plot(ProcD(rcpnone),
             [ graph.style.symbol(graph.style.symbol.changesquare),
               graph.style.errorbar()
               ]
             )
    goff.writetofile("plots/gaincurve_off.pdf")    
    
  



#d=ParseData(open("cdata/efficiency050411.txt"))        
#PlotGain(d , "2005SpringV1", 3, 12.5, 0.25, 0.55)
#changesquare
#attr.changelist([square, triangle, circle, diamond, cross, plus])
