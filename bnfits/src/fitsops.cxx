/*! Bojan Nikolic
    $Id:

*/

#include "fitsops.hxx"

#include "fitswrap.hxx"

namespace BNFits {

  std::string  FName (FitsF & file)
  {

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


}



