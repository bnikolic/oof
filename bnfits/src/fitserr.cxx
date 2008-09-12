/**
   \file fitserr.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
*/

#include "fitserr.hxx"

#include <sstream>

namespace BNFits {

  std::string MkMsg(const std::string &fname, 
		    const std::string &msg, 
		    int fitsstatus) 
  {
    std::ostringstream s;
    
    s<<msg<<". File being processed: " << fname <<". CFITSIO error code: " << fitsstatus;

    return s.str();
  }

  FIOExc::FIOExc(const std::string &fname,
		 const std::string &msg, 
		 int fitsstatus):
    std::runtime_error(MkMsg( fname, msg , fitsstatus))
  {
  }

  
  NoSuchHdr::NoSuchHdr(const std::string &fname, 
		       const unsigned &hdrno, 
		       int fitsstatus):
    FIOExc (fname , 
	    std::string("Requested header could not be read"),
	    fitsstatus)
  {
  }

}


