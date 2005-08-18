/*
  Bojan Nikolic
  $Id: obsfilefns.cxx,v 1.2 2005/08/18 15:25:47 bnikolic Exp $

*/

#include "obsfilefns.hxx"

#include <astromapio.hxx>
#include <astromap.hxx>
#include <vector>

#include "obscompare.hxx"



namespace OOF {

  void WriteBeams( ObsCompare &oc, 
		   const char * fname)
  {
    std::vector<AstroMap::Map *> beams;
    
    for ( unsigned i = 0 ; i < oc.NObs() ; ++i )
      beams.push_back( oc.Beam(i));

    FitsWrite( beams, fname);
    
    for ( unsigned i = 0 ; i < oc.NObs() ; ++i )
      delete(beams[i]);

  }




}


