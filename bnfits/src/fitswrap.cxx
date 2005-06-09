/* Bojan Nikolic
   $Id: fitswrap.cxx,v 1.1 2005/06/09 12:30:23 bnikolic Exp $
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
    int scratch;
    if (fits_movabs_hdu(file, dataextno, &scratch, &status) )
      throw ( NoSuchHdr(FName(*this), dataextno, status));
  }


}
