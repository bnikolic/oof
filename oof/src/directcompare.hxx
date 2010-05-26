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
#include <astromap.hxx>

namespace AstroMap {
  class ModelMap;
}

namespace OOF {

  class MapToResidual;

  /** \brief Compare directly a far-field model to observations
   */
  class FFCompare:
    public Minim::Minimisable 
  {

    boost::scoped_ptr<AstroMap::ModelMap> m;
    boost::scoped_ptr<MapToResidual> o;

    mutable AstroMap::Map mtemp;

  public:

    /**
       \param m The model  (we takes ownership of m)

       \param o The observed data (e take ownership of o)
       
       \param msample Sample map to figure out things like number of
       pixels and the coordinate system
     */
    FFCompare(AstroMap::ModelMap *m,
	      MapToResidual *o,
	      const AstroMap::Map &msample);

    virtual ~FFCompare();

    
    //------------- Inherited from Minim::Minimisable-------------

    virtual unsigned nres(void) const  ; 
    virtual void residuals(std::vector<double> &res) const;
    virtual void AddParams(std::vector<Minim::DParamCtr> &pars);

  };


}

#endif
