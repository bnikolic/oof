# Bojan Nikolic
# $Id: implot.py,v 1.6 2005/08/28 04:25:35 bnikolic Exp $
#
# Routines for plotting maps

import string

import pyplot

def GetMapBBox( mapp ):

    "Return the full box of the map"

    return ( mapp.cs.x_pxtoworld(0,0),
             mapp.cs.x_pxtoworld(mapp.nx,0),
             mapp.cs.y_pxtoworld(0,0),
             mapp.cs.y_pxtoworld(0,mapp.ny ) )

def SetupBBox( mapp, bbox=None):

    "Sets up the view which is actually plotted"

    if bbox == None: bbox= GetMapBBox( mapp)
    pyplot.cpgswin( bbox[0], bbox[1], bbox[2], bbox[3])


def plotmap(mapp,
            fout="/xserve" ,
            plotwedge=1 ,
            pgbeg=1 ,
            transf=2  ,
            bbox=None ,
            plotbox=1 ,
            title=None,
            width=0,
            colmap=None):

    "Plots a general map"

    """
    bbox: a list definig the part of the map that should be plotted.

    """

    if pgbeg:
        pyplot.cpgbeg(0,fout,0,0)
        pyplot.cpgpap(width,1.0)

    SetupBBox( mapp, bbox=bbox)        


    if plotbox:
        pyplot.cpgtbox("DYFOBCNS",0,0,"DYFOBCNS",0,0)

    pyplot.cpgsitf(transf)

    if colmap == None :
        pyplot.SetPrintCT( 0,1)
    else:
        pyplot.SetFileColourTab(colmap)

    if plotwedge:
        pyplot.cpgwedg("RI",1,2, mapp.min(), mapp.max(), " ")
        

    pyplot.Plot(mapp)
    
    if title != None :
        pyplot.cpglab("","", title )

    finishplot(fout)



def finishplot(foutname):
    "Close the PGPLOT device if it is a hard-copy"

    fout=foutname
    if (string.find(fout, "/CPS") != -1 or
        string.find(fout, "/GIF") != -1 or
        string.find(fout, "/PNG") != -1 or
        string.find(fout, "/png") != -1 ) : 

        ## we are doing a hard copy...
        pyplot.cpgclos()
