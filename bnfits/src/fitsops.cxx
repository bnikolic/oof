/*! Bojan Nikolic
    $Id:

*/

#include "fitsops.hxx"

#include "fitswrap.hxx"
#include "fitserr.hxx"

#include <iostream>


namespace BNFits {

  std::string  FName (FitsF & file)
  {
    /* Clunky of what */
    char filename[1024];
    int status =0 ;
    fits_file_name  (file, filename,& status );
    
    return std::string(filename);

  }

  unsigned long NRows (FitsF & file, unsigned extno)
  {
    file.HDUseek (extno);

    long nrows = 0;
    int status = 0;
    fits_get_num_rows(file, &nrows, &status);

    return nrows;

  }

  unsigned NAxis(FitsF & file)
  {
    int status =0 ;
    int naxis  =0;
    
    if ( fits_get_img_dim( file, &naxis, &status))
      throw (FIOExc(FName(file) ,
		    "Could not determine number of axes (maybe not an image?) ",
		    status ));
    
    return (unsigned) naxis;
  }

  std::vector<long> ImgDims(FitsF & file)
  {
    int status;
    unsigned naxis = NAxis(file);

    std::vector<long> res(naxis);

    fits_get_img_size( file, 
		       naxis,
		       &res[0],
		       &status);
    
    return res;
  }

  void CopyCol( FitsF &f1,
		FitsF &f2,
		unsigned incolnum,
		unsigned outcolnum,
		bool create)
    throw(FIOExc) 
  {

    int status = 0;

    if(   fits_copy_col( f1, f2, 
			 incolnum, outcolnum,
			 create,
			 &status) )
      {
	std::cerr<<"Failed to copy column"<<std::endl;
	throw (FIOExc(FName(f1) ,
		      "Could not copy column ",
		      status ));
      }

  }

  int GetColType(FitsF &file, unsigned colno)
    throw(BNFits::FIOExc)  
  {
    
    /* This checks we are on a table hdu */
    file.TableChk();
    
    int typecode;
    long repeat;
    long width;
    int status=0;

    if (fits_get_coltype( file, colno, 
			  &typecode, 
			  &repeat,
			  &width,
			  &status) )
      throw ( FIOExc(FName(file),
		     "Could not retrieve info about column",
		     status));
    
    return typecode;

  }

  void CopyColData( FitsF &f1,
		    FitsF &f2,
		    size_t incolnum,
		    size_t outcolnum,
		    size_t outfirstrow ) throw(BNFits::FIOExc) 
  {
    

  }


}



