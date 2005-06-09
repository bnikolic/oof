/*! Bojan Nikolic
    $Id: fitserr.hxx,v 1.1 2005/06/09 12:30:23 bnikolic Exp $

    Some basic facilities for signaling and processing errors arrising
    out of FITS I/O
*/
#ifndef _BNFITS_FITSERR_HXX__ 
#define _BNFITS_FITSERR_HXX__ 

#include <stdexcept>

namespace BNFits {

  

  /*! Make up a nice message about what went wrong */
  std::string MkMsg (std::string fname, std::string msg, int fitsstatus) ;

  class FIOExc : public std::runtime_error {

  public:
    
    FIOExc ( std::string fname, std::string msg, int fitsstatus);

  };

  class NoSuchHdr : public FIOExc {
    
  public:
    
    NoSuchHdr( std::string fname, unsigned hdrno, int fitsstatus);
  };




}


#endif
