/*
  Bojan Nikolic
  $Id: tfitsops.hxx,v 1.4 2005/08/18 14:33:37 bnikolic Exp $

  Templated fits file operations 
*/

#ifndef _BNFITS_TFITSOPS_HXX__
#define _BNFITS_TFITSOPS_HXX__

#include <fitsio.h>


#include "fitswrap.hxx"
#include "fitserr.hxx"
#include "fitsops.hxx"

#include <valarray>

namespace BNFits {

  /*! Write an array into the current image extension */
  template<class T> void WriteImg (FitsF &file,
				   std::valarray<T> &data )
  {

    int datatype ;
    if (typeid(T) == typeid(double)  ) 
      {
	datatype=TDOUBLE;
      } 
    else 
      {
	throw ( FIOExc( FName(file),
			"Do not know how to write supplied data type",
			-99));
      }

    int status =0;

    std::vector<long> imgdims = ImgDims( file);

    long firstpix[2];
    firstpix[0]=1;
    firstpix[1]=1;

    std::valarray<long> fpixel(  imgdims.size() );
    fpixel = 1;

    for ( unsigned i = 0 ; i < imgdims.size() ; ++i )
      imgdims[i] -= 1;
    
    
    if ( fits_write_pix( file,
			 datatype,
			 &fpixel[0],
			 //firstpix,
			 data.size(),
			 &data[0],
			 &status ) )
      throw ( FIOExc( FName(file),
		      "Data not written successfully",
		      status));


  }

  /*! Update header keywords in current header */
  template<class T> void UpdateKeywrd (FitsF &file,
				       char * keywrd,
				       T value,
				       char * comment)
  {

    int datatype ;
    if (typeid(T) == typeid(double)  ) 
      {
	datatype=TDOUBLE;
      } 
    else if ( typeid(T) == typeid(int)   )
      {
	datatype=TINT;
      }
    else 
      {
	throw ( FIOExc( FName(file),
			"Do not know how to write supplied data type",
			-99));
      }

    int status=0;

    if ( fits_update_key    (file, 
			     datatype, 
			     keywrd, 
			     &value,
			     comment,
			     &status))
      {
	throw ( FIOExc( FName(file),
			std::string("Failed to write keyword ") + keywrd,
			status));
      }
    
  }
				       


  /*! Loads a column from a table */
  template<class T> void LoadCol ( FitsF &file,
				   unsigned extno,
				   const char  * colname,
				   std::valarray<T> &data )
  {

    int datatype ;

    /*! Define Null values here */
    double Dnullval =0;
    unsigned UINTnullval=0;
    
    void *nullval(0); 

    if (typeid(T) == typeid(double)  ) 
      {
	datatype=TDOUBLE;
	nullval = (void *) &Dnullval; 
      } 
    else if ( typeid(T) == typeid(unsigned) ) 
      {
	datatype=TUINT;
	nullval = (void *) &UINTnullval; 
      } 
    else if ( typeid(T) == typeid(char * ) ) 
      {
	datatype=TSTRING;
      }
    else 
      {
	throw ( 0 );
      }

    int colno = file.ColNo(extno , colname);

    int ann = 0;
    int status = 0;

    if (fits_read_col(file, 
		      datatype , 
		      colno, 
		      1, 1, 
		      data.size(), 
		      nullval, 
		      &data[0], 
		      &ann, 
		      &status) )
      throw FIOExc( FName(file),
		    "Failed to read column " + std::string(colname) ,
		    status );
    
    


  }
  


}

#endif
