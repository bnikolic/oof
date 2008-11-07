/*!
  Bojan Nikolic
  $Id: dsfileops.cxx,v 1.4 2005/07/26 22:15:37 bnikolic Exp $

*/

#include "dsfileops.hxx"

#include <memory>
#include <iostream>
#include <typeinfo>

#include <bndebug.hxx>
#include <fitswrap.hxx>
#include <fitsops.hxx>
#include <tfitsops.hxx>



#include "dataseries.hxx"


namespace AstroMap {


  DataSeries * LoadFITSDS( const char * fname , unsigned extno)
  {
    using namespace BNFits;

    try {
      /* open file for reading */
      FitsF fin (fname, FitsF::read) ;

      /* First attempt to access this extension -- will throw here if
	 something wrong!*/
      const unsigned long nrows = NRows(fin, extno);
      
      std::auto_ptr<DataSeries> res (ENFORCE(new DataSeries(nrows )));
      
      std::valarray<double> scratch ( nrows);
      
      LoadCol( fin , extno , "DX" , scratch);
      for (unsigned long  i =0 ; i < nrows  ; ++i )
	(*res)[i].dX = scratch[i] ;
      
      LoadCol( fin , extno , "DY" , scratch);
      for (unsigned long  i =0 ; i < nrows  ; ++i )
	(*res)[i].dY = scratch[i] ;
      
      LoadCol( fin , extno , "FNU" , scratch);
      for (unsigned long  i =0 ; i < nrows  ; ++i )
	  (*res)[i].fnu = scratch[i] ;
      
      LoadCol( fin , extno , "UFNU" , scratch);
      for (unsigned long  i =0 ; i < nrows  ; ++i )
	(*res)[i].ufnu = scratch[i] ;

      return res.release();
    }
    catch (FIOExc exc ) 
      {
	std::cerr<<"\n ERROR: Loadidng Dataseries failed with following error:\n";
	std::cerr<<exc.what();
	std::cerr<<"\n Return empty dataseries";
	return new DataSeries(0);
	
      }

    



  }



}


