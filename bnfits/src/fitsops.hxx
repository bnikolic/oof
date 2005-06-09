/*! Bojan Nikolic
    $Id:

    Some operations on FITS files.
*/
#ifndef _BNFITS_FITSOPS_HXX__
#define _BNFITS_FITSOPS_HXX__

#include <string>



namespace BNFits {

  class FitsF;

  /*! Returns the name of the file associated with this FITS object */
  std::string  FName (FitsF & file);


  


}
#endif


