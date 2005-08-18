/*! Bojan Nikolic
    $Id:

    Some operations on FITS files.
*/
#ifndef _BNFITS_FITSOPS_HXX__
#define _BNFITS_FITSOPS_HXX__

#include <string>
#include <vector>


namespace BNFits {

  class FitsF;

  /*! Returns the name of the file associated with this FITS object */
  std::string  FName (FitsF & file);

  /*! Returns the number of rows in this table extension */
  unsigned long NRows (FitsF & file, unsigned extno);

  /*! Return the number of dimensions */
  unsigned NAxis(FitsF & file);

  /*! Return the dimension of the image */
  std::vector<long> ImgDims(FitsF & file);


  


}
#endif


