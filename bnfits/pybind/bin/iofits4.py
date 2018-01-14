# Bojan Nikolic  <bojan@bnikolic.co.uk>
#
# Routines to support operations on FITS tables

import os
import datetime
import re

from itertools import izip

import numpy
import pyfits

def PrepFitsOut (cvsid):
    "Create a basic layout FITS file"

    """

    """
    

    fout=pyfits.HDUList()
    phdu=pyfits.PrimaryHDU()
    fout.append(phdu)
    
    phdu.header.update("author", "BNikolic")
    phdu.header.update("DateOut",
                       "%s" %  datetime.datetime.today() ,
                       comment="Date and time when file was produced")

    phdu.header.add_comment("CVSVer: %s" % cvsid)
                            
    
    return fout

def AddBzrVersionInfo(hdu):

    "Add the version info from bzr as comments to supplied hdu"

    """
    Will fail miserably if not in a bzr repository
    """

    exec(os.popen("bzr version-info --format=python").read())

    hdu.header.add_comment( 'Bzr Revision: %(revno)d' % version_info)
    #hdu.header.add_comment( 'nick: %(branch_nick)s' % version_info)
    hdu.header.add_comment( 'revision id: %(revision_id)s'  % version_info )

def Prep ( fname, overwrite , mkpath):

    "Prepare for writing out a fits file"
    
    if mkpath:
        dirout=os.path.dirname(fname)
        
        if dirout != "" and not os.path.exists(dirout):
            os.makedirs(dirout)
    if overwrite and os.access(fname, os.F_OK ):  os.remove(fname)



def Write( hdulist , foutname , overwrite=0 , mkpath=1):

    "Write out a FITS file"

    Prep ( foutname , overwrite=overwrite , mkpath=mkpath)
    pyfits.HDUList(hdulist).writeto(foutname)

def WriteOut(coldefs, foutname, cvsid,
             overwrite=0, keydict=None):
    "Writes out columns to a fits file"

    Prep(foutname, overwrite, 1)

    fout=PrepFitsOut(cvsid)
    fout[0].header.update("iofits4" ,
                          "$Id: iofits4.py,v 1.11 2006/04/18 10:37:19 bnikolic Exp $",
                          "Version of iofits3 script" )
    
    tabout = pyfits.new_table( coldefs )

    if keydict != None:
        for k in keydict:
                tabout.header.update(k, keydict[k][0] , keydict[k][1])

    
    fout.append(tabout)
    fout.writeto(foutname)

def FnParTable(d, cvsid):
    "Creates a fits table representing parameters to a function"

    coldefs= [ pyfits.Column( "Parameter" , "30A" ) ,
               pyfits.Column( "Value" , "80A" ) ]

    tabout=pyfits.new_table( coldefs , nrows=len(d) )
    tabout.header.update("cvsid", cvsid)

    for x,rowout in izip(d, tabout.data ):
        rowout.setfield("Parameter", x )
        rowout.setfield("Value", str(d[x])       )
        

    return  tabout

def Select(dirin, filein , selfn, dirout,
           overwrite=False):
    "Select a subsample from ma table "

    """
    If overwrite is False, will skip existing files in destination
    directory.
    """

    mask=[ selfn(row) for row in pyfits.open(filein)[1].data ]
    mind=[ x for x,f in  enumerate (mask) if f]
    nrows=len(mind)

    print "Selected %i rows." % nrows
    
    fitsel=re.compile(".*fits?")
    flist = [ fnamein for fnamein in os.listdir(dirin) if fitsel.match(fnamein) ]
    
    for fnamein in flist:
        foutname=os.path.join(dirout,fnamein)

        if os.access(foutname, os.F_OK) and (not overwrite):
            print "Skipping %s as it already exists" % fnamein
        else:
            fin=pyfits.open(os.path.join(dirin,fnamein))

            newtab=pyfits.new_table( fin[1].get_coldefs() , nrows= nrows)
            for cname in fin[1].get_coldefs().names:
                newtab.data.field(cname)._copyFrom( fin[1].data.field(cname)[ mind] )

        
            Write([pyfits.PrimaryHDU(), newtab],
                  foutname,
                  overwrite=1)
            

def CopyColDefs( tabin , prefix =""):

    "Make a copy of table column definitions with optional prefix"

    tabcds= tabin.get_coldefs()
    
    coldefs = [ pyfits.Column( prefix+name ,
                               format ,
                               unit ) for name,format,unit in izip(tabcds.names,
                                                                   tabcds.formats,
                                                                   tabcds.units) ]
    return coldefs
    

    
def Combine( flist , fout,
             overwrite=0):
    "Combines columns from various fits files"

    """flist needs to be of format ( (fname, col-prefix), ... ) """

    tabins= [ (pyfits.open( x[0] )[1], x[1]) for x in flist ]

    coldefs = []
    for tab,prefix in tabins:
        tabcds=tab.get_coldefs()
        print tabcds.formats
        coldefs.extend( CopyColDefs( tab, prefix))

        
    tabout= pyfits.new_table( coldefs , nrows=len(tabins[0][0].data))

    for tab,prefix in tabins:
        tabcds=tab.get_coldefs()
        for cname in tabcds.names:
            tabout.data.field(prefix+cname)._copyFrom(tab.data.field(cname))

    
    
    Write([pyfits.PrimaryHDU(), tabout],
          fout,
          overwrite=overwrite)

    

def RepPHDU ( phin):

    "Replicate a primary HDU"

    keyrejlist= [ "SIMPLE" , "BITPIX" , "NAXIS" , "EXTEND", "AUTHOR" , "DATEOUT" , "CVSVER" ]
    keycopylist = [ k[0] for k in phin.header.items() if k[0] not in keyrejlist]

    phout= pyfits.PrimaryHDU()

    for k in keycopylist:
        phout.header.update(k, phin.header[k])

    return phout

def RepTable ( tabin ,
               rowmask=None ,
               colsel=None,
               keycopylist = ["dz"]
               ):

    "Replicate a fits table"


    
    if rowmask ==None:
        rowmask = numpy.ones(len(tabin.data),
                             numpy.bool)

    nrowsout=sum(rowmask)

    
    tabout=pyfits.new_table( CopyColDefs(tabin),
                             nrows=nrowsout)

    for k in keycopylist:
        if tabin.header.has_key(k):
            tabout.header.update ( k , tabin.header[k] )

    if colsel == None:
        colsel = tabin.get_coldefs().names

    if nrowsout > 0 :
        for cname in colsel:
            tabout.data.field(cname)._copyFrom( tabin.data.field(cname)[ rowmask] )

    return tabout
                                
    
def TableSelect( fnamein,
                 fnameout,
                 hduselfn= lambda hduno , hduname, hdu : True,
                 rowselfn= lambda hdudata : numpy.ones(len(hdudata),
                                                       numpy.bool)
                 ):

    "Selects hdus/and rows from a fits files and copies them over to new file"

    fin = pyfits.open(fnamein)

    #Copy the primary header over
    fout = [ RepPHDU ( fin[0] )  ]


    for hduno in range(1, len(fin)):
        
        hdu=fin[hduno]
        hduname=""
        
        if hduselfn(hduno, hduname, hdu):
            
            rowmask = rowselfn(hdu.data)
            newhdu=RepTable (hdu, rowmask=rowmask )
            
            fout.append(newhdu)

            
    Write(fout, fnameout, overwrite=1)



def TableRearange(fnamein,
                  fnameout,
                  rowlist,
                  colnamelist=None):

    "Create new table with rows re-arranged from the old table according to rowlist"

    """
    row order will be rowlist[0] rowlist[1] etc....

    if colnamelist is specified, only these columns are copied over.
    """

    nrows = len(rowlist)

    fin=pyfits.open(fnamein,
                    memmap=True)
    din=fin[1].data

    if colnamelist == None:
        colnamelist = din.names


    coldefs =[]
    for colname in colnamelist:
        colindex = din.names.index(colname)

        coldefs.append( pyfits.Column( colname ,
                                       din.formats[colindex],
                                       ""))

    tabout= pyfits.new_table( coldefs , nrows=nrows)    

    for nrowout,nrowin in enumerate(rowlist):
        for colname in colnamelist:
            if nrowin >= 0:
                tabout.data.field(colname)[nrowout]= din.field(colname)[nrowin]
            elif ( din.formats[din.names.index(colname)] == "E" ):
                tabout.data.field(colname)[nrowout]= -9999

    fout=PrepFitsOut(r"$Id: iofits4.py,v 1.11 2006/04/18 10:37:19 bnikolic Exp $")
    fout.append(tabout)
    Write( fout,
           fnameout,
           overwrite=1)                

def AddKeyword(fname,
               kname,
               kval):

    "Add a keyword to the primary header of the supplied"

    fin=pyfits.open(fname)
    
    fin[0].header.update(kname,kval)

    Write( fin, fname, overwrite=1)
    

    
