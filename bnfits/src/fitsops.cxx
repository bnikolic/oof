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
  


}



