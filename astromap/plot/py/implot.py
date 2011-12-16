# Bojan Nikolic <bojan@bnikolic.co.uk>
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
            bbox=None,
            abox=None,
            plotbox=1 ,
            title=None,
            width=0,
            colmap=None,
            valrange=None,
            contours=None,
            contcolour=None,
            contourmap=None,
            aspect=1.0):


    "Plots a general map"

    """
    bbox: a list definig the part of the map that should be plotted.

    :param abox: Defines a subset of the original array to
    plot. Unlike bbox this is the pixel coordinates and actually
    removes the data from the final image.

    valrange: if range is defined, restrict the range of values plotted
           to the that specified. Othervise cover the whole range of
           the data from the minimum to maximum value.

    aspect:    aspect  ratio of the plot

    :param contourmap: If not False, this is 

    """
    mapp  = pyplot.Map(mapp)
    mapp.cs= mapp.cs.Clone()

    # Reinterpret as definitely pyplot type
    mapp=pyplot.Map(mapp)

    if pgbeg:
        pyplot.cpgbeg(0,fout,0,0)
        pyplot.cpgpap(width,aspect)

    SetupBBox( mapp, bbox=bbox)        


    if plotbox:
        pyplot.cpgtbox("DYFOBCNS",0,0,"DYFOBCNS",0,0)
    else:
        pyplot.cpgtbox("BC",0,0,"BC",0,0)

    pyplot.cpgsitf(transf)

    if colmap == None :
        pyplot.SetPrintCT( 0,1)
    else:
        pyplot.SetFileColourTab(colmap)

    if valrange == None:
        valrange = mapp.min_max_fin()
    if valrange[0] == None:valrange[0]= mapp.min()         
    if valrange[1] == None:valrange[1]= mapp.max() 
        
    if plotwedge:
        pyplot.cpgwedg("RI",1,2, valrange[0] , valrange[1], " ")
        

    if abox is None:
        pyplot.Plot(mapp, valrange[0] , valrange[1])
    else:
        pyplot.Plot(mapp, 
                    valrange[0],
                    valrange[1],
                    *abox)
    
    if title != None :
        pyplot.cpglab("","", title )

    if contcolour != None:
        pyplot.cpgsci(contcolour)

    if contours != None and contourmap :
            mapp=contourmap

    if contours != None:
        if abox is None:
            pyplot.Contour(mapp, 
                           ConvVect(contours))
        else:
            pyplot.Contour(mapp,
                           ConvVect(contours),
                           *abox)

    finishplot(fout)

def ConvVect(dlist):

    res=pyplot.DoubleVector(len(dlist))
    for i,v in enumerate(dlist): res[i]=v
    return res

def finishplot(foutname):
    "Close the PGPLOT device if it is a hard-copy"

    fout=foutname
    if (string.find(fout, "/CPS") != -1 or
        string.find(fout, "/GIF") != -1 or
        string.find(fout, "/PNG") != -1 or
        string.find(fout, "/png") != -1 ) : 

        ## we are doing a hard copy...
        pyplot.cpgclos()

def MkChopContours( m, step=0.5 , nlevels=5, ctype="log"):

    "Make contours suitable for chopped maps"

    if ctype == "log":
        contours = [ m.max() * step**i for i in range(nlevels)  ]
        contours.extend( [ m.min() * step**i for i in range(nlevels)  ] )
    elif ctype == "lin" :
        contours = [ m.max() * i/float(nlevels) for i in range(nlevels)  ]
        contours.extend( [ m.min() * i/float(nlevels) for i in range(nlevels)  ] )

    return contours

def MkSynthesisContours( m , step=0.5,
                         nlevels=5):

    "Make contours which look good on synthesis maps"

    """
    Positive and negatives scales are identical
    """

    if nlevels==0 or nlevels is None:
        return None

    mmax=m.max_fin()
    
    contours =       [ mmax * step**i for i in range(nlevels)  ]
    contours.extend( [ -mmax * step**i for i in range(nlevels)  ])

    return contours

def PlotSynthesisFile(fnamein,
                      fnameout,
                      nc=7,
                      ext=1,
                      colour=False,
                      zoom=None,
                      center=False):

    "Plot an aperture synthesis map from file"
    
    """
    nc is the number of contours

    if zoom > 1, plot only that fraction of the map
    """

    m1=pyplot.FitsMapLoad(fnamein ,
                          ext)

    if center:
        pyplot.ZeroOffsetCS(m1)

    if  zoom > 1:
        zoom = 1.0 /zoom
        mapp=m1
        bbox=[ mapp.cs.x_pxtoworld(mapp.nx * 0.5 * (1-zoom) ,mapp.ny * 0.5 * (1-zoom)),
               mapp.cs.x_pxtoworld(mapp.nx * 0.5 * (1+zoom) ,mapp.ny * 0.5 * (1-zoom)),
               mapp.cs.y_pxtoworld(mapp.nx * 0.5 * (1-zoom) ,mapp.ny * 0.5 * (1-zoom)),
               mapp.cs.y_pxtoworld(mapp.nx * 0.5 * (1-zoom) ,mapp.ny * 0.5 * (1+zoom))]
    else:
        bbox=None
    
    if not colour:
        plotmap(m1, fnameout,
                contours=MkSynthesisContours(m1, nlevels=nc),
                bbox=bbox)
    else:
        if fnameout.find("png") > 0 :
            contcolour=1
        else:
            contcolour=0            
        plotmap(m1, fnameout, colmap="heat",
                contours=MkSynthesisContours(m1, nlevels=nc),
                contcolour=contcolour,
                bbox=bbox)
