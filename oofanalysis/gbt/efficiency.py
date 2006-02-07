# Bojan Nikolic
# $Id: efficiency.py,v 1.2 2006/02/07 00:54:06 bnikolic Exp $
# Some basic efficiency plots




def PlotModelEff(modname,
                 errbar=0.03,
                 condmodel=False):

    "Plot efficiency expected from a model fit"

    effdata=[]
    for el in [ 10 + i*5 for i in range(14)]:

        mphase, mamp = oofplot.MkApFile("models/%s/surfacepars-el%i.fits" % (modname,
                                                                             el))
        wrms=pyplot.MapRMS( mphase, mamp)
        print el, wrms

        effdata.append(( el, math.exp(-1.0  * wrms) , 0.03 ))

    if condmodel:
        addp=lambda g : g.plot(pyxplot.graph.data.function(
        "y=exp(-1.0 * ((x-52)/54)**2)"))
    else:
        addp=None

    pyxplot.scatter( effdata,
                     "plots/Mod%sGCurve.eps" % modname,
                     width=pyxplot.THESIS,
                     xax=pyxplot.axis(r"$\theta\,$(deg)", xmin=0 , xmax=90),
                     yax=pyxplot.axis(r"$\eta_{\rm LSS}$"),
                     symbsize=0.05,
                     addp=addp)
        

    

                                        
        

