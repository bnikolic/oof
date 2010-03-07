# Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
# Initial version March 2010
#
# This file is part of BNMin1 package and is licensed under GPL V2
"""
Input and output of the BNMin1 data structures to the HDF5 file format
"""

from tables import *
import numpy

import pybnmin1
import bnmin1utils

def mkNestedTableDef(mm):
    """
    Create the definition for storing the posterior distribution of
    the nested sampler
    """
    res={}
    N=mm.NParam()
    for i in range(N):
        pname=mm.getbynumb(i).getname()
        pcom=mm.getbynumb(i).getcomment()
        res[pname]=Float64Col(pos=i)
    res["ll"]=Float64Col(pos=N)
    res["w"]=Float64Col(pos=N+1)
    return res
    
def writePost(mm,
              hdffile,
              group):
    """
    Write the posterior distribution 

    :param group: The posterior table will be created under this group
    with name "post"

    :returns: The created table object, to allow easy further
    modifications to it

    """
    table=h5file.createTable(group, 
                             'post', 
                             mkNestedTableDef(mm), 
                             "Nested Sampler posterior distribution")
    r=table.row
    post=mm.g_post()
    N=mm.NParam()
    for p in post:
        for i in range(N):
            r[mm.getbynumb(i).getname()]=p.p[i]
        r["w"]=p.w
        r["ll"]=p.ll
        r.append()
    table.attrs.Z=mm.Z()
    return table

def readPost(table):
    """
    Read the posterior distribution from a table
    """
    res=pybnmin1.ListWP()
    # Number of fitted parameters
    N=len(table.coltypes)-2
    for r in table:
        x=pybnmin1.WPPoint()
        for i in range(N):
            x.p.push_back(r[i])
        x.w=r["w"]
        x.ll=r["ll"]
        res.push_back(x)
    return res
        
def setModel(m,
             table,
             rowno,
             excols=["w", "ll"]):
    """
    Set a model to the parameters in rowno of table
    
    :param excols: Columns to exclude from the setting procedure
    because the take non-parameter data
    """
    pnames=[x for x in table.colnames if x not in excols]
    for pname in pnames:
        md.getbyname(pname).setp(table.col(pname)[rowno])

def nestedPostW(table):
    """
    Compute the to total weighting for the posterior from the
    likelihoods and weights
    """
    return numpy.exp(-table.col("ll"))*table.col("w")


