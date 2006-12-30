# Bojan Nikolic
# $Id: plotmodel.py,v 1.3 2006/12/30 21:35:49 bnikolic Exp $
#
# Make a reasonable plot of the hook model

import pickle
from itertools import izip
import ooffitconv


from pyx import *
#text.set(mode="latex")
#text.preamble(r"\usepackage{mathptmx}")

def plot(pname, width=8):

    elevs, vals, model = pickle.load( open("model/%s.pickle" % pname) )

    d1= graph.data.list ( [ (x, y ) for x,y in izip( elevs, vals) ] , x=1 , y=2 )
    d2= graph.data.list ( [ (x, y ) for x,y in izip( elevs, model) ] , x=1 , y=2 )

    g = graph.graphxy(width=width,
                      x=graph.axis.lin(title="Elevation (deg)" , min=10, max=80),
                      y=graph.axis.lin(title="Phase (rad)",
                                       min=-1,
                                       max=1.5)
                      )

    g.plot(d1,
           [graph.style.symbol(graph.style.symbol.cross, size=0.1)]
           )
    g.plot(d2,
           [graph.style.line([style.linewidth.Thin, style.linestyle.solid]) ])

    unit.set(xscale=1.25)

    n,l=ooffitconv.OOFktoOOFnl( int(pname[1:]))
    g.text( 5,0.25 , "$n=%i$, $l=%i$" % (n,l)
            )
    unit.set(xscale=1)
    
    g.writetofile("model/%s.eps" % pname)


def doplot():

    for i in range(3,21):
        plot("z%i" %i )
