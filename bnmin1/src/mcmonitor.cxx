/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2009

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file mcmonitor.cxx

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


