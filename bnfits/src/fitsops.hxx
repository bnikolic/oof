/*! Bojan Nikolic
    $Id:

    Some operations on FITS files.
*/
#ifndef _BNFITS_FITSOPS_HXX__
#define _BNFITS_FITSOPS_HXX__

#include <string>
#include <vector>

#include "fitserr.hxx"


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

  /*! Copy a column from file f1 to file f2 */
  void CopyCol( FitsF &f1,
		FitsF &f2,
		unsigned incolnum,
		unsigned outcolnum,
		bool create) throw(BNFits::FIOExc) ;

  /*! Return the CFits type-code  for specified column */
  int GetColType(FitsF &file, unsigned colno) throw(BNFits::FIOExc)  ;

  /*! Copy column data from file f1 to file f2, starting from specified row */
  void CopyColData( FitsF &f1,
		    FitsF &f2,
		    size_t incolnum,
		    size_t outcolnum,
		    size_t outfirstrow ) throw(BNFits::FIOExc) ;


  


}
#endif


