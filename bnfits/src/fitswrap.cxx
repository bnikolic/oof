/* Bojan Nikolic
   $Id: fitswrap.cxx,v 1.2 2005/07/02 21:06:27 bnikolic Exp $
*/

#include "fitswrap.hxx"

#include <fitsio.h>

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


}
