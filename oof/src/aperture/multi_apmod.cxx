/**
   \file multi_apmod.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   
*/

#include "multi_apmod.hxx"

#include <boost/format.hpp>

#include <astromap.hxx>


namespace OOF {

  MultiAmp_ApModel::MultiAmp_ApModel(PhaseMod * phasemodel,
				     AmpliMod * amplimodel,
				     double wavel,
				     AstroMap::Map &mapsample,
				     size_t nobs):
    ApertureMod(phasemodel,
		amplimodel,
		wavel,
		mapsample),
    amp_r(nobs-1,
	  1.0),
    mamp(AstroMap::Clone(mapsample))
  {
  }

  MultiAmp_ApModel::~MultiAmp_ApModel()
  {
  }

  const AstroMap::Map * MultiAmp_ApModel::getAmp(size_t i)
  {
    if ( i==0 )
    {
      return getamp();
    }
    else
    {
      (*mamp) = (*getamp());
      (*mamp) *= amp_r[i-1];
      return mamp.get();
    }
  }

  void MultiAmp_ApModel::AddParams(std::vector< Minim::DParamCtr > &pars)
  {
    ApertureMod::AddParams(pars);
    for (size_t i=0; i<amp_r.size(); ++i)
    {
      std::string pname = (boost::format("amp_r%i") % (i+1)).str();
      std::string pdesc = (boost::format("%i-th / zeroth obs v. amplitude") % (i+1)).str();
      
      pars.push_back(Minim::DParamCtr(&amp_r[i],      
				      pname, 
				      true,                       
				      pdesc
				      ));
    }
  }
  
  


}

