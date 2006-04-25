# Bojan Nikolic
# $Id: verification.py,v 1.2 2006/04/25 14:57:00 bnikolic Exp $
#
# Plot OOF verification results

import string

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

            apeff= float(ld[8])
            apefferr= float(ld[10])
            model   = ld[11]

            if model == "(None)": model = 0
            elif model == "(2005WinterV1)" : model =1

            res.append ( ( pol, elev,( apeff, apefferr ) , model , src))

    return res

def PlotGain( d):

    rcpnone = [ ( x[1 ] , x[2][0] , x[2][1] ) for x in d if x[0]=="RCP" and x[3]==0 ]
    rcpv1 = [ ( x[1 ] , x[2][0] , x[2][1] ) for x in d if x[0]=="RCP" and x[3]==1 ]    

    pt      = [ pyxplot.graph.data.list( rcpnone, x=1, y=2, dy=3),
                pyxplot.graph.data.list( rcpv1, x=1, y=2, dy=3),                
                ]

    c = canvas.canvas()
    
    gon = c.insert(pyxplot.graph.graphxy(width=pyxplot.MNRAS_SC,
                                          x=pyxplot.axis(r"$\theta\,$(degrees)",
                                                         xmin=0, xmax=90) ,
                                          y=pyxplot.axis(r"$\eta_{\rm a}$",
                                                         xmin=0.2, xmax=0.6),
                                          ))
    gon.plot(pt[1],
             [ graph.style.symbol(graph.style.symbol.changecircle,
                                  symbolattrs=[deco.filled()]
                                  ),
               graph.style.errorbar()
               ]
             )

    goff  = c.insert(pyxplot.graph.graphxy(width=pyxplot.MNRAS_SC,
                                           ypos =gon.height+0.5,
                                           x=gon.axes["x"].createlinkaxis(),
                                          y=pyxplot.axis(r"$\eta_{\rm a}$",
                                                         xmin=0.2, xmax=0.6),
                                           ))


    goff.plot(pt[0],
             [ graph.style.symbol(graph.style.symbol.changesquare),
               graph.style.errorbar()
               ]
             )


    c.writetofile("plots/gaincurve.eps")



        
