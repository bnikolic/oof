# Bojan Nikolic
# $Id: bnmin1io.py,v 1.1 2005/08/21 02:42:02 bnikolic Exp $
#
# Input / output support for the minimiser routines

import pickle
import math

import pyfits
import numarray

import pybnmin1

import iofits4

modcvs = r"$Id: bnmin1io.py,v 1.1 2005/08/21 02:42:02 bnikolic Exp $"

def FSave(modeldesc , fnameout ):

    "Save the current state to a fits file"

    """

    """

    nrows = modeldesc.NTotParam() 

    coldefs= [
        pyfits.Column ( "ParName",   "30A" ),
        pyfits.Column ( "ParValue",   "E" ),
        pyfits.Column ( "DoFit",     "I" ),
        pyfits.Column ( "ParComment",     "80A" ) ]

    tabout=pyfits.new_table( coldefs , nrows=nrows )
    
    for i, rowout in enumerate( tabout.data) :

        cpar = modeldesc.getbynumb(i )

        rowout.setfield("ParName", cpar.getname())
        rowout.setfield("ParValue", cpar.getp())
        rowout.setfield("DoFit", cpar.dofit)
        rowout.setfield("ParComment", cpar.getcomment())

    fout=iofits4.PrepFitsOut(modcvs)
    fout.append(tabout)

    iofits4.Write(fout, fnameout , overwrite =True )

def FLoad( modeldsc, fnamein, ext=1, silent=False):
    
    "Load a fit from a fits file"

    """

    """
    
    fin=pyfits.open(fnamein)

    for rowin in fin[ext].data:

        cpar = modeldsc.getbyname( rowin.field("ParName"))

        if  cpar:
            cpar.setp( rowin.field("ParValue") )
        else:
            if not silent : print "%s doesn't exist in model" % rowin.field("ParName")


def FittedPars( m ):
    "Return the list of names of fitted parameters"

    res = []
    
    for  i in range( m.NTotParam() ):
        cpar = m.getbynumb(i)

        if cpar.dofit :
            res.append( cpar.getname() )

    return res

def CVCVSWrite(cvm, m , fnameout , norm=0, wikiform=0 ):
    "Write covariance matrix as comma separated file"

    fout=open(fnameout, "w")
    parlist=FittedPars(m)

    if wikiform:
        sep="|"
        linesep=sep
    else:
        sep=","
        linesep=""
        

    fout.write(linesep)
    for p in parlist:
        fout.write(" %s%s" % (sep,p))
    fout.write(linesep)        

    
    for i,p1 in enumerate(parlist):
        fout.write("\n %s %s " % (linesep, p1) )
        for j, p2 in enumerate(parlist):
            if norm:
                fout.write(" %s %g " % (sep, ( cvm[i,j] / ( cvm[i,i] * cvm[j,j] )**0.5 )))
            else:
                fout.write(" %s %g " % (sep, cvm[i,j] ))
        fout.write(linesep)
        

    
        


            
def CVSave( m , fnameout, tol=1e-10):

    "Save the covariance matrix"

    """
    Saves in python pickle and csv formats
    """

    
    cvraw = pybnmin1.CVMatrix(m, tol)

    cvm = numarray.array(cvraw)

    #set correct shape
    n=int( math.sqrt (len(cvm)))
    cvm.shape=(n,n)

    # Output the pickled version
    cvpickle = open(fnameout + ".pickle", "w")
    pickle.dump(cvm,cvpickle)

    CVCVSWrite(cvm, m ,
               fnameout+".csv" ,
               norm=1, wikiform=0 )
    
        
    
    
        
        
        

    
        
        
        

    
