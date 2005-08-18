/*
  Bojan Nikolic
  $Id: csfileio.cxx,v 1.1 2005/08/18 14:33:55 bnikolic Exp $

*/

#include "csfileio.hxx"

#include <iostream>

#include <fitswrap.hxx>
#include <tfitsops.hxx>
#include <fitserr.hxx>

#include "coordsys.hxx"

namespace AstroMap {

  void FitsWrite(  CoordSys & cs, BNFits::FitsF & fout,
		   int nx, int ny)
  {
    
    int crpixx = nx /2;
    int crpixy=  ny /2;

    double crvalx; double crvaly;
    cs.pxtoworld( crpixx, crpixy, crvalx, crvaly ) ;

    double crdeltx; double temp;
    cs.pxtoworld( crpixx + 1, crpixy, crdeltx, temp ) ;
    crdeltx -= crvalx;

    double crdelty;
    cs.pxtoworld( crpixx , crpixy+1, temp  , crdelty ) ;
    crdelty -= crvaly;

    try {
      UpdateKeywrd( fout,  
		    "CRPIX1", 
		    crpixx,
		    "");
      
      UpdateKeywrd( fout,  
		    "CRPIX2", 
		    crpixy,
		    "");

      UpdateKeywrd( fout,  
		    "CRVAL1", 
		    crvalx,
		    "");
      
      UpdateKeywrd( fout,  
		    "CRVAL2", 
		    crvaly,
		    "");
      
      UpdateKeywrd( fout,  
		    "CDELT1", 
		    crdeltx,
		    "");
      
      UpdateKeywrd( fout,  
		    "CDELT2", 
		    crdelty,
		    "");
    } 
    catch (BNFits::FIOExc exc ) 
      {
	std::cerr<<"\n ERROR: Writing coordinate system failed with following error:\n";
	std::cerr<<exc.what();
	std::cerr<<"Undefined coordsystem is attached to this image";
      }
    

    

  }

}


