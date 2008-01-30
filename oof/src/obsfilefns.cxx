/**
   \file obsfilefns.cxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>
*/

#include "obsfilefns.hxx"

#include <astromapio.hxx>
#include <astromap.hxx>
#include <vector>

#include "obscompare.hxx"
#include "aperture/aperturemod.hxx"



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

  void WriteAperture(ObsCompare &oc, 
		     const char * fname)
  {
    std::vector<AstroMap::Map *> aps;

    aps.push_back( new AstroMap::Map( * (oc.GetAperture()->getamp()) ));
    aps.push_back( new AstroMap::Map( * (oc.GetAperture()->getphase()) ));

    FitsWrite( aps, fname);
    
    for ( unsigned i = 0 ; i < aps.size() ; ++i )
      delete(aps[i]);
  }


}


