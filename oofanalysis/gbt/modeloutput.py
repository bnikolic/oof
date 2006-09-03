# Bojan Nikolic
# $Id: modeloutput.py,v 1.1 2006/09/03 11:30:48 bnikolic Exp $
# Output for OOF models
#

import pyfits
import iofits4

import ooffitconv


def WriteHookModel( data, fnameout,
                    wavel=0.006956 ):

    """

    data are supplied as a dictionary keyed by zernike polynomial name
    (as string, e.g. z4)  and with stored elements tuples (c , a ,b )

    wavel is the wavelength of observations (use this to convert to
    actuator movement)
    
    """

    coldefs1= [ pyfits.Column( "z" , "3A" , "none"), 
                pyfits.Column( "c" , "E" , "radians"), 
                pyfits.Column( "a" , "E" , "radians" ), 
                pyfits.Column( "b" , "E" , "radians" ) ]

    tabout1 = pyfits.new_table( coldefs1 ,
                                nrows=len(data.keys() ))
    tabout1.header.add_comment( "z is OOF convention zernike poly label"  )
    tabout1.header.add_comment( "c is Elevation independt term")
    tabout1.header.add_comment( "a is coefficient of sin(elev)" )
    tabout1.header.add_comment( "b is coefficient of cos(elev)" )
    
    for i,k in enumerate(data.keys()):

        tabout1.data[i].setfield("z", k)
        tabout1.data[i].setfield("c",  data[k][0] )
        tabout1.data[i].setfield("a", data[k][1]  )
        tabout1.data[i].setfield("b", data[k][2])

    tabout1.header.update("wavel", wavel,
                          comment="Wavelength of observations (m) ")

    coldefs2= [ pyfits.Column( "z" , "3A" , "none"), 
                pyfits.Column( "c" , "E" , "micron"), 
                pyfits.Column( "a" , "E" , "micron" ), 
                pyfits.Column( "b" , "E" , "micron" ) ]

    tabout2 = pyfits.new_table( coldefs2 ,
                                nrows=len(data.keys() ))

    tabout2.header.add_comment( "These are results in the *GBT* convention"  )    
    tabout2.header.add_comment( "z is GBT convention zernike poly label"  )
    tabout2.header.add_comment( "c is Elevation independt term ")
    tabout2.header.add_comment( "a is coefficient of sin(elev)" )
    tabout2.header.add_comment( "b is coefficient of cos(elev)" )

    res={}
    for j,l in enumerate( ["c" , "a" , "b"] ):
        oofdict={}
        for i,k in enumerate( data.keys() ):
            oofdict[k]=data[k][j]
        gbtdict=ooffitconv.ConvertOOFtoGBT (oofdict )
        ooffitconv.Scale(gbtdict, wavel)
        if res == {} :
            for i,k in enumerate( gbtdict.keys() ):
                res[k]= [ gbtdict[k] , 0 , 0]
        else:
            for i,k in enumerate( gbtdict.keys() ):
                res[k][j]= gbtdict[k]

    for i,k in enumerate(res.keys()):

        tabout2.data[i].setfield("z", k)
        tabout2.data[i].setfield("c",  res[k][0] )
        tabout2.data[i].setfield("a", res[k][1]  )
        tabout2.data[i].setfield("b", res[k][2])    


    fout=iofits4.PrepFitsOut(r"$Id: modeloutput.py,v 1.1 2006/09/03 11:30:48 bnikolic Exp $")
    fout.append(tabout1)
    fout.append(tabout2)    
    iofits4.Write( fout, fnameout , overwrite=1)    


        
        
        

    

    


               

    

