/** 
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version 2010

   This file is part of the OOF package and licensed under GNU General
   Public License version 2
   
   \file directcompare.hxx

   Direct comparison between abstract models and observation, in the
   far-field and not necesarrily with a aperture-plane model
*/
#ifndef __OOF_DIRECTCOMPARE_HXX__
#define __OOF_DIRECTCOMPARE_HXX__

#include <boost/scoped_ptr.hpp>

#include <minimmodel.hxx>

namespace AstroMap {
  class FittableMap;
}

namespace OOF {

  /** \brief Compare directly a far-field model to observations
   */
  class FFCompare:
    public Minim::Minimisable 
  {

    boost::scoped

  public:

    
    FFCompare(AstroMap::FittableMap *m);

  };


}

#endif
