/* Bojan Nikolic
   $Id: fitswrap.hxx,v 1.1 2005/06/09 12:30:23 bnikolic Exp $
   
   Simple wrapper for cfitsio
*/
#ifndef BNFITS_FITSWRAP_HXX__
#define BNFITS_FITSWRAP_HXX__

#include <fitsio.h>


namespace BNFits {

  /*! 
   * This is intentinally a very simple wrapper for fits files.
   */
  class FitsF {

    fitsfile *file;

  public:
    
    enum openmode {read ,write } ;

    FitsF( const char * fname, openmode mode  );

    ~FitsF();
    
    operator fitsfile* ();

    void HDUseek( unsigned dataextno ) ;

  };


}

#endif
