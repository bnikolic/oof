/**
   \file csfileio.cxx
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>

   Initial version 2002
*/

#include "csfileio.hxx"

#include <iostream>
#include <typeinfo>

#include <fitswrap.hxx>
#include <tfitsops.hxx>
#include <fitserr.hxx>

#include "coordsys.hxx"
#include "lincordsys.hxx"

namespace AstroMap {

  void FitsWrite(CoordSys &cs,
		 BNFits::FitsF &fout,
		 int nx,
		 int ny)
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

  CoordSys * FitsCSLoad(BNFits::FitsF &fin)
  {

    LinCS * res  = new LinCS();

    try 
    {
      double crpixx = BNFits::ReadKeywrd<double> (fin, "CRPIX1");
      double crpixy = BNFits::ReadKeywrd<double> (fin, "CRPIX2");

      double crvalx = BNFits::ReadKeywrd<double> (fin, "CRVAL1");
      double crvaly = BNFits::ReadKeywrd<double> (fin, "CRVAL2");

      double crdeltx = BNFits::ReadKeywrd<double> (fin, "CDELT1");
      double crdelty = BNFits::ReadKeywrd<double> (fin, "CDELT2");

      res->TM[0] = crdeltx ;
      res->TM[1] = 0 ;
      res->TM[2] = crvalx - crdeltx * crpixx ;

      res->TM[3] =0;
      res->TM[4] =crdelty;
      res->TM[5] = crvaly - crdelty * crpixy ;    

    }
    catch ( const BNFits::FIOExc & exc ) 
    {
      // No coordinate system recorded, no problem, contiue with
      // default
    }





    return res;

  }

}


