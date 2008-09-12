/** 
    \file fitsops.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Some operations on FITS files.
*/
#ifndef _BNFITS_FITSOPS_HXX__
#define _BNFITS_FITSOPS_HXX__

#include <string>
#include <vector>
#include <valarray>

#include "fitserr.hxx"


namespace BNFits {

  class FitsF;

  /*! Returns the name of the file associated with this FITS object */
  std::string  FName (FitsF & file);

  /*! Returns the number of rows in this table extension */
  unsigned long NRows (FitsF & file, unsigned extno);

  /*! Returns number of rows in the current extnesion */
  unsigned long NRows (FitsF & file);

  /*! Return the number of dimensions */
  unsigned NAxis(FitsF & file);

  /*! Return the dimension of the image */
  std::vector<long> ImgDims(FitsF & file);

  /*! As above but avoid silly copy */
  void ImgDims(FitsF & file, std::vector<long> & res);

  /*! Copy a column from file f1 to file f2 */
  void CopyCol( FitsF &f1,
		FitsF &f2,
		unsigned incolnum,
		unsigned outcolnum,
		bool create) throw(BNFits::FIOExc) ;

  /*! 
    Return info about column types 

    \par repeat returns the vector repeat count on the binary table
    TFORMn keyword value. (ASCII table columns always have repeat = 1)

    \par width parameter returns the width in bytes of a single column
    element (e.g., a '10D' binary table column will have width = 8, an
    ASCII table 'F12.2' column will have width = 12, and a binary
    table'60A' character string column will have width = 60)
  */
  void GetColInfo(FitsF &file, unsigned colno,
		  int &typecode,
		  long &repeat,
		  long &width);

  /*! Return the CFits type-code  for specified column */
  int GetColType(FitsF &file, unsigned colno) throw(BNFits::FIOExc)  ;

  /*! Copy column data from file f1 to file f2, starting from
      specified row. Output table is extend as necesary. */
  void CopyColData( FitsF &f1,
		    FitsF &f2,
		    size_t incolnum,
		    size_t outcolnum,
		    size_t outfirstrow ) throw(BNFits::FIOExc) ;

  /*! Delete specified row numbers */
  void DeleteRows( FitsF &f1,
		   std::valarray<long> &rowlist ) throw(BNFits::FIOExc);

  void DeleteRows( FitsF &f1,
		   std::vector<long> &rowlist ) throw(BNFits::FIOExc);


  


}
#endif


