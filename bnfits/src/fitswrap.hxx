/* Bojan Nikolic
   $Id: fitswrap.hxx,v 1.4 2005/08/18 04:56:37 bnikolic Exp $
   
   Simple wrapper for cfitsio
*/
#ifndef BNFITS_FITSWRAP_HXX__
#define BNFITS_FITSWRAP_HXX__

#include <fitsio.h>
#include <vector>


namespace BNFits {

  /*! 
   * This is intentinally a very simple wrapper for fits files.
   */
  class FitsF {

    fitsfile *file;

    /*! After a seek the extension type will be placed here */
    int hdutype;

  public:
    
    enum openmode {read ,readwrite, create } ;

    FitsF( const char * fname, openmode mode  );

    ~FitsF();
    
    operator fitsfile* ();

    void HDUseek( unsigned dataextno ) ;
    
    /*! Is extno a table? */
    bool TableP ( unsigned dataextno );

    /*! If not a table throw an exception */
    void TableChk (unsigned dataextno) ;

    /*! Return the column number correspondong to colname */
    int ColNo (unsigned extno, char * colname );

    int ColNo (unsigned extno, const char * colname );

    /* ---------- Writing Images -------------- */
    
    /*! Create an image extension. For now assume all are double type. */
    void MkImage ( std::vector<long> axes , int bitpix );
    

  };

  /* Some helpful functions */
  





}

#endif
