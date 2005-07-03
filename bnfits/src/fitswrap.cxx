/* Bojan Nikolic
   $Id: fitswrap.cxx,v 1.3 2005/07/03 14:38:12 bnikolic Exp $
*/

#include "fitswrap.hxx"

#include <fitsio.h>
#include <memory>

#include "fitserr.hxx"
#include "fitsops.hxx"

namespace BNFits {

  FitsF::FitsF( const char * fname, openmode mode  )
  {
    int status = 0;
    if ( fits_open_file(&file, fname , READONLY, &status))
      throw ( FIOExc(fname ,"Error opening FITS file", status) ); 
  }

  FitsF::~FitsF()
  {
    int status =0;
    if ( fits_close_file(file, &status) )
      throw ( FIOExc(FName(*this) ,"Error closing file", status) ); 
  }

  FitsF::operator fitsfile* ()
  {
    return file;
  }

  void FitsF::HDUseek( unsigned dataextno ) 
  {
    int status = 0;
    if (fits_movabs_hdu(file, dataextno, &hdutype, &status) )
      throw ( NoSuchHdr(FName(*this), dataextno, status));
  }

  bool FitsF::TableP (  unsigned extno)
  {
    HDUseek( extno);        

    return hdutype == ASCII_TBL || hdutype == BINARY_TBL ;
    
  }

  void FitsF::TableChk (unsigned dataextno) 
  {

    if ( not TableP(dataextno) )
      throw ( FIOExc ( FName (*this) , 
		       "Tried a table operation on a non-table HDU",
		       99));

  }

  int FitsF::ColNo (unsigned extno, char * colname )
  {
    TableChk(extno);

    int colno =0 ;
    int status =0;
    
    if( fits_get_colnum   ( (*this), 0, colname , &colno,   &status) )
      throw ( FIOExc(FName(*this) ,
		     "Column  " + std::string(colname) + "not found",
		     status)
	      )	;     

    return colno;
	      
    
  }

  int FitsF::ColNo (unsigned extno, const char * colname )
  {
    
    std::string scname (colname);

    std::auto_ptr<char>  temp( new char[scname.size() +1 ] );

    scname.copy( & temp.get()[0] , scname.size()  );
    temp.get()[scname.size()] = 0;

    return ColNo(extno, temp.get() );

  }


}
