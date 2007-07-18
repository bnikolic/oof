/*! Bojan Nikolic
    $Id:

*/

#include "fitsops.hxx"

#include "fitswrap.hxx"
#include "fitserr.hxx"

#include <iostream>
#include <valarray>


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

  unsigned long NRows (FitsF & file)
  {

    file.TableChk();

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

  /*! Return info about column types */
  void GetColInfo(FitsF &file, unsigned colno,
		  int &typecode,
		  long &repeat,
		  long &width)
  {
    /* This checks we are on a table hdu */
    file.TableChk();

    int status=0;

    if (fits_get_coltype( file, colno, 
			  &typecode, 
			  &repeat,
			  &width,
			  &status) )
      throw ( FIOExc(FName(file),
		     "Could not retrieve info about column",
		     status));

  }

  int GetColType(FitsF &file, unsigned colno)
    throw(BNFits::FIOExc)  
  {
    
    int typecode;
    long repeat;
    long width;

    GetColInfo( file, colno, typecode, repeat, width );
    return typecode;

  }

  void CopyColData( FitsF &f1,
		    FitsF &f2,
		    size_t incolnum,
		    size_t outcolnum,
		    size_t outfirstrow ) throw(BNFits::FIOExc) 
  {

    int typecode;
    long repeat;
    long width;

    GetColInfo( f1, incolnum, 
		typecode, repeat, width );

    
    size_t nrows = NRows(f1);

    // Unfortunetely cfitsio is hopeless on 64-bit machines....
    width = width *2;

    std::valarray<char> data  ( width * repeat * nrows);

    // Read input data

    int anynul= 0;
    int status=0;
    if( fits_read_col(f1, typecode, incolnum,
		      1  , 1 , repeat* nrows,
		      NULL,
		      &data[0],
		      &anynul,
		      &status) )
      throw ( FIOExc(FName(f1),
		     "Could not read data from input column",
		     status));

    // Write to output column

    if ( fits_write_col( f2, typecode, outcolnum,
			 outfirstrow, 
			 1,
			 repeat*nrows,
			 &data[0],
			 &status ))
      throw ( FIOExc(FName(f2),
		     "Could not write data to output column",
		     status));

    

  }

  void DeleteRows( FitsF &f1,
		   std::valarray<long> &rowlist )
    throw(BNFits::FIOExc)
  {
    
    f1.TableChk();

    int status=0;
    if ( fits_delete_rowlist( f1,
			      &rowlist[0],
			      rowlist.size(),
			      &status))
      throw ( FIOExc(FName(f1),
		     "Could not delete rows",
		     status));
    
  }

  void DeleteRows( FitsF &f1,
		   std::vector<long> &rowlist )
    throw(BNFits::FIOExc)
  {
    std::valarray<long> rl (&rowlist[0],
			    rowlist.size());

    DeleteRows(f1, rl);
  }


}



