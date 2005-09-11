#
# Bojan Nikolic
#
# $Id: ooffitconv.py,v 1.2 2005/09/12 00:22:36 bnikolic Exp $
#
# Routines to convert OOF fits between various formats

def OOFktoOOFnl(k):
    "Converts between the sequential and n,l numbering used in the OOF software"

    nmin= int( math.sqrt(2*k) ) - 1
    nmax= int( math.sqrt(2*k) ) + 1

    n=None
    remainder=None
    for ntrial in range(nmin, nmax):
        if ( (ntrial)*(ntrial+1)/2 <= k):
            n=ntrial
            remainder= k - (ntrial)*(ntrial+1)/2 

    l= -1 * n + 2* remainder
    return  n , l

def OOFnltoOOFk(n,l):
    return n*(n+1)/2 + (n+l)/2

def SchwabnltoSchwabk(n,l):
    return n*(n+1)/2 + (n+l)/2 +1

def OOFktoSchwabk(k):

    """

    Converts the sequential zernike number as output by the oof
    software to the k numbering shown in F. Schwab & M. Mello's memo

    """

    oof_n , oof_l =  OOFktoOOFnl(k)

    ## first, sin and cos terms in Schwab convention are reversed--> reverse l
    sch_n = oof_n
    sch_l = -1 * oof_l

    ## now convert to the sequential number k and return:
    sch_k = SchwabnltoSchwabk(sch_n,sch_l)
    return sch_k

def SchwabktoOOFk(schk):

    for i in range(100):
        if OOFktoSchwabk(i) == schk :
            return i

