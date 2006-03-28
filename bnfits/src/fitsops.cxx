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


}



