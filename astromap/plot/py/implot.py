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
            bbox=None ,
            plotbox=1 ,
            title=None,
            width=0,
            colmap=None,
            valrange=None,
            contours=None,
            contcolour=None):


    "Plots a general map"

    """
    bbox: a list definig the part of the map that should be plotted.

    valrange: if range is defined, restrict the range of values plotted
           to the that specified. Othervise cover the whole range of
           the data from the minimum to maximum value.


    """
    mapp  = pyplot.Map(mapp)
    mapp.cs= mapp.cs.Clone()

    # Reinterpret as definitely pyplot type
    mapp=pyplot.Map(mapp)

    if pgbeg:
        pyplot.cpgbeg(0,fout,0,0)
        pyplot.cpgpap(width,1.0)

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
        valrange = (mapp.min() , mapp.max() )
    if valrange[0] == None:valrange[0]= mapp.min()         
    if valrange[1] == None:valrange[1]= mapp.max() 
        
        
    if plotwedge:
        pyplot.cpgwedg("RI",1,2, valrange[0] , valrange[1], " ")
        

    pyplot.Plot(mapp, valrange[0] , valrange[1])
    
    if title != None :
        pyplot.cpglab("","", title )

    if contcolour != None:
        pyplot.cpgsci(contcolour)

    if contours != None:
        pyplot.Contour( mapp , ConvVect(contours) )

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

def MkSynthesisContours( m , step=0.5, nlevels=5):

    "Make contours which look good on synthesis maps"

    """
    Positive and negatives scales are identical
    """

    contours =       [ m.max() * step**i for i in range(nlevels)  ]
    contours.extend( [ -m.max() * step**i for i in range(nlevels)  ])

    return contours

def PlotSynthesisFile(fnamein,
                      fnameout,
                      nc=7,
                      ext=1,
                      colour=False):

    "Plot an aperture synthesis map from file"
    
    """
    nc is the number of contours
    """

    m1=pyplot.FitsMapLoad(fnamein ,
                          ext)

    if not colour:
        plotmap(m1, fnameout,
                contours=MkSynthesisContours(m1, nlevels=nc))
    else:
        if fnameout.find("png") > 0 :
            contcolour=1
        else:
            contcolour=0            
        plotmap(m1, fnameout, colmap="heat",
                contours=MkSynthesisContours(m1, nlevels=nc),
                contcolour=contcolour)
