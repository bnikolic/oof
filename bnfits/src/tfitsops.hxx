/*
  Bojan Nikolic
  $Id: tfitsops.hxx,v 1.1 2005/07/03 14:38:12 bnikolic Exp $

  Templated fits file operations 
*/

#ifndef _BNFITS_TFITSOPS_HXX__
#define _BNFITS_TFITSOPS_HXX__

#include <fitsio.h>


#include "fitswrap.hxx"
#include "fitserr.hxx"


#include <valarray>

namespace BNFits {



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
