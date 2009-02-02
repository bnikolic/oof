# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Input / output support for the minimiser routines

import pickle
import math
import string

import pyfits
import numpy

import pybnmin1
import bnmin1utils

import iofits4

modcvs = r""

def FSave(modeldesc , fnameout ):
    """Save the current state of a model to a FITS file

    The output format is a simple binary table in the first FITS
    extension hdu

    :param fnameout: The output filename. Note that it will be
    overwritten if it exists.

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

def fittedParsNums(mod):
    """Return sequence of the indices of parameters which are being fitted
    for"""
    res =[i for i in range(mod.NTotParam()) if mod.getbynumb(i).dofit]
    return res


def fSaveChain(modeldesc,
               chain,
               fnameout,
               kwrds={}):
    """
    Save a MCMC chain to a FITS file

    The chain is saved to the first extension HDU as a binary table
    with parameter for column names. 

    :param modeldesc: The model which the chain desribes (parameter
    names are retrieved through this). OR, a list of strings, in which
    case we assume these are column names.
    
    :param chain: The actual chain

    :param fnameout: The FITS file name to write to. Will be
    overwritten.
    
    :param kwrds: Keywords to add to the primary header to
    
    """
    fout=iofits4.PrepFitsOut(modcvs)
    for k in kwrds.keys():
        fout[0].header.update(k, kwrds[k])
    nrows=len(chain)
    if type(modeldesc) is list:
        colnames=modeldesc
        ncols=len(colnames)
    else:
        ncols=modeldesc.NParam()
        colnames=[modeldesc.getbynumb(i).name 
                  for i in fittedParsNums(modeldesc)]
    coldefs=[pyfits.Column(colname,"E") 
             for colname in colnames]
    tabout=pyfits.new_table(coldefs,
                            nrows=nrows)
    if type(chain) is not numpy.ndarray:
        chain=bnmin1utils.ChainToArray(chain)
    for i in range(ncols):
        tabout.data.field(i)[:]=chain[:,i]
    fout.append(tabout)
    iofits4.Write(fout, 
                  fnameout, 
                  overwrite=True)    


def FLoad(modeldsc, fnamein, ext=1, silent=False):
    """Load a fit (that is a set of parameter values) from a FITS file
    
    :param modeldsc: Model which should be set to the supplied fit
    
    :param fnamein: the name of the file with the fit to set (see
    FSave)
    
    :param ext: extension of the FITS file containing fit information

    :param silent: Do not report parameters in the FITS file that do
    not exist in the supplied model
    """
    
    fin=pyfits.open(fnamein)

    for rowin in fin[ext].data:

        cpar = modeldsc.getbyname( rowin.field("ParName"))

        if  cpar:
            cpar.setp( float(rowin.field("ParValue")) )
        else:
            if not silent : print "%s doesn't exist in model" % rowin.field("ParName")

def FAdd( modeldsc, fnamein, ext=1 , silent=False):

    "Add a fit from a file to the current fit"

    """
     This basically offsets the current fit by the value of a previous fit
    """

    fin=pyfits.open(fnamein)

    for rowin in fin[ext].data:

        cpar = modeldsc.getbyname( rowin.field("ParName"))

        if  cpar:
            cpar.setp( cpar.getp() + rowin.field("ParValue") )
        else:
            if not silent : print "%s doesn't exist in model" % rowin.field("ParName")    

def FGetPar( fnamein , parname):
    "Retrieve the value of a single parameter from a fit saved to a file"

    dat=pyfits.open(fnamein)[1].data

    sres = dat.field("ParName").search(parname)
    if len( sres[0] ) == 0:
        raise "Parameter %s not found" % parname

    parindex = sres[0][0]

    return dat.field("ParValue")[parindex]


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
                if cvm[i,j] == 0.0 :
                    val = 0.0
                else:
                    val = ( cvm[i,j] / ( cvm[i,i] * cvm[j,j] )**0.5 )
            else:
                fout.write(" %s %g " % (sep, cvm[i,j] ))

            fout.write(" %s %g " % (sep, val))

        fout.write(linesep)
        

def LoadCVSFile(fnamein):

    r=[]

    for l in open(fnamein):
        ld= string.split(l, ",")
        if ld[0] == " ":
            print ld[1:]
        else:
            rr=[ float(x) for x in ld[1:] ]
            r.append(rr)

    return numpy.array(r)
            
        
        
        


            
def CVSave( m , fnameout, tol=1e-10):

    "Save the covariance matrix"

    """
    Saves in python pickle and csv formats
    """

    
    cvraw = pybnmin1.CVMatrix(m, tol)

    cvm = numpy.array(cvraw)

    #set correct shape
    n=int( math.sqrt (len(cvm)))
    cvm.shape=(n,n)

    # Output the pickled version
    cvpickle = open(fnameout + ".pickle", "w")
    pickle.dump(cvm,cvpickle)

    CVCVSWrite(cvm, m ,
               fnameout+".csv" ,
               norm=1, wikiform=0 )
    
        

        
        
        

    
        
        
        

    
