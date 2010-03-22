/**
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   Initial version March 2010, after code with orgini in 2005

   \file planetff.hxx
   
*/
#ifndef _OOF_PLANETFF_HXX___
#define _OOF_PLANETFF_HXX___

#include <boost/scoped_ptr.hpp>

#include "farf.hxx"

namespace OOF {

  /**
     \brief Represent a total power observation of a planet or similar
     resolved source
  */
  class PlanetFF: 
    public FarF 
  {
    
    /** Map of the objedt
     */
    boost::scoped_ptr<AstroMap::Map> planetm;    
    
    /** Radius of the object, in radian on the sky
     */
    double radius;

    const double wavel;

  public:

    // ---------- Constructors / destructors    -------------
    
    PlanetFF(double radius,
	     AstroMap::Map &apmapsample,
	     double wavel);

    virtual ~PlanetFF();

    // ---------- Functions inherited from FarF  -------------

    static AstroMap::Map *mkModel(const AstroMap::Map &ffsample,
				  double radius);

    virtual void Power ( const AstroMap::Map & amp, 
			 const AstroMap::Map & phase, 
			 AstroMap::Map & res);

    virtual const char * FFType (void) const; 

    // ------ Inherited functions rom Minim::Model ---------
    virtual void  AddParams(std::vector<Minim::DParamCtr> &pars);    

  };  
  

}


#endif

