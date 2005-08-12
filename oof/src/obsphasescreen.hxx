/*
  Bojan Nikolic
  $Id: obsphasescreen.hxx,v 1.2 2005/08/12 18:43:15 bnikolic Exp $

  An abstract class to represent a phase screen present during an
  observed map, e.g., defocus or a pointing shift
*/
#ifndef _OOF_OBSPHASESCREEN_HXX__
#define _OOF_OBSPHASESCREEN_HXX__

#include <astromap_fwd.hxx>

namespace OOF {

  class ObsPhaseScreen {

  public:

    /*! This will _add_ the calculated phase screen to the supplied
     *       map 
     */
    virtual void DePhase( AstroMap::Map  & res) = 0;

  };



}

#endif
