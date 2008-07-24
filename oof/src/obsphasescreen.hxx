/**
  \file obsphasescreen.hxx
  Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
  
*/
#ifndef _OOF_OBSPHASESCREEN_HXX__
#define _OOF_OBSPHASESCREEN_HXX__

#include <astromap_fwd.hxx>

namespace OOF {

  /**
     An abstract class to represent a phase screen present during an
     observed map, e.g., defocus or a pointing shift
   */
  class ObsPhaseScreen {

  public:

    // ------------- Constructor / Destructor Section ----------------

    virtual ~ObsPhaseScreen(void);


    // ------------- Member functions -------------------------------

    /*! This will _add_ the calculated phase screen to the supplied
     *       map 
     */
    virtual void DePhase( AstroMap::Map  & res) = 0;

  };



}

#endif
