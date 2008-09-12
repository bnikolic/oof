/** \file fitserr.hxx
    
    Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>

    Some basic facilities for signaling and processing errors arrising
    out of FITS I/O
*/
#ifndef _BNFITS_FITSERR_HXX__ 
#define _BNFITS_FITSERR_HXX__ 

#include <stdexcept>

namespace BNFits {

  
  /*! Make up a nice message about what went wrong */
  std::string MkMsg (const std::string &fname, 
		     const std::string &msg, 
		     int fitsstatus);

  class FIOExc: 
    public std::runtime_error
  {

  public:
    
    FIOExc (const std::string &fname, 
	    const std::string &msg, 
	    int fitsstatus);

  };

  class NoSuchHdr: 
    public FIOExc 
  {
    
  public:
    
    NoSuchHdr(const std::string &fname, 
	      const unsigned &hdrno, 
	      int fitsstatus);
  };




}


#endif
