/* Bojan Nikolic
   $Id: fitswrap.hxx,v 1.2 2005/07/02 21:06:27 bnikolic Exp $
   
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

    /*! After a seek the extension type will be placed here */
    int hdutype;

  public:
    
    enum openmode {read ,write } ;

    FitsF( const char * fname, openmode mode  );

    ~FitsF();
    
    operator fitsfile* ();

    void HDUseek( unsigned dataextno ) ;
    
    /*! Is extno a table? */
    bool TableP ( unsigned dataextno );

    /*! If not a table throw an exception */
    void TableChk (unsigned dataextno) ;

  };

  /* Some helpful functions */
  





}

#endif
