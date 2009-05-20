/**
   \file mcmonitor.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/


#include <iostream>

#include "mcmonitor.hxx"
#include "mcpoint.hxx"

namespace Minim 
{

  MCMonitorBase::~MCMonitorBase()
  {
  }

  SOutMCMon::SOutMCMon(void):
    ia(0),
    ip(0),
    na(1),
    np(1),
    os(std::cout)
  {
  }

  void SOutMCMon::accept(const MCPoint& p)
  {
    if ( (ia % na) == 0)
    {
      os<<"Accepted: ";
      for (size_t i=0; i<p.p.size(); ++i)
	os<<p.p[i]<<",";
      os<<std::endl;
    }
    ++ia;
    ip=0;
  }

 void SOutMCMon::propose(const MCPoint& p)
 {
   if ( (ip % np) == 0)
    {
      os<<"Proposed: ";
      for (size_t i=0; i<p.p.size(); ++i)
	os<<p.p[i]<<",";
      os<<std::endl;
    }
    ++ip;
 }
  
  
    

}


