/* Bojan Nikolic
   $Id: fitswrap.hxx,v 1.8 2006/04/02 23:34:36 bnikolic Exp $
   
   Simple wrapper for cfitsio
*/
#ifndef BNFITS_FITSWRAP_HXX__
#define BNFITS_FITSWRAP_HXX__

#include <fitsio.h>
#include <vector>

#include "fitserr.hxx"


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

    FitsF( const char * fname, openmode mode  )
      throw(BNFits::FIOExc);

    ~FitsF();
    
    operator fitsfile* ();

    void HDUseek( unsigned dataextno ) ;
    
    /*! Is extno a table? */
    bool TableP ( unsigned dataextno );

    /*! If not a table throw an exception */
    void TableChk (unsigned dataextno) ;

    /*! Throw execpetion if current hdu is not a table */
    void TableChk () ;

    /*! Return the column number correspondong to colname */
    int ColNo (unsigned extno, char * colname )
      throw(BNFits::FIOExc);

    int ColNo (unsigned extno, const char * colname );

    /* ---------- Writing Images -------------- */
    
    /*! Create an image extension. For now assume all are double type. */
    void MkImage ( std::vector<long> axes , int bitpix );

    /* --------- Creating tables  ------------- */

    /*! Create an empty table */
    void CreateTbl(size_t nrows, char * extname)
      throw(BNFits::FIOExc);
    
    

  };

  /* Some helpful functions */
  





}

#endif
