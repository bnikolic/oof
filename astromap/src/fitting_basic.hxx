/**
  \file fitting_basic.hxx
  Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>
  Initial version January 2008.
  
  Basic fitting routines on maps.

*/
#ifndef _ASTROMAP_FITTING_BASIC_HXX__
#define _ASTROMAP_FITTING_BASIC_HXX__

#include "../config.h"

#include "minimmodel.hxx"
#include "astromap.hxx"
#include "gaussian.hxx"

// Forward declarations
namespace BNLib{
  class BinaryDD;
}

namespace AstroMap {

  /**
     \brief Fit functions to a in a map
   */
  class FittableMap :
    public Minim::Minimisable
  {
    /**  \brief The model to be fitted for
     */
    BNLib::BinaryDD * model;
    
    const Map & map;

    /// A scratch map to compute the model on
    mutable Map mtemp;

  public:

    // ---------- Public data ------------

    /**
       If this parameter is false the fitting will be carried out in
       pixel coordinates rather then world coordinates.
     */
    bool worldcs;

    // ---------- Construction/Destruction -------------

    /**

       \param map the map to fit for. 
       
       \note still need to add parameters after construction
     */
    FittableMap(const Map &map);

    // ---------- Public interface         -------------

    /** \brief Set the model to fit for
     */
    void SetModel(BNLib::BinaryDD *mod);

    /** \brief return a copy of the scratch map
	
     */
    Map *ScratchCopy(void);

    /** \brief Set a map according to the current model
     */
    virtual void eval(Map &m) const;
    

    // ---------- Inherited from Minimisable -----------
    virtual void residuals( std::vector< double > &res) const;
    virtual unsigned nres(void) const; 
  };

  /**
     \brief Fit a gaussian to a map.
   */
  class GaussMapModel:
    public FittableMap 
  {
  public:

    // ---------- Public data ------------

    /**
       The gaussian model. Publicly expose for easy introspection.
     */
    BNLib::GaussianDD gm;
    

    // ------------ Construction/ destruction ----------
    
    GaussMapModel(const Map  &map);

    // ---------- Inherited  from FittableMap ---------------
    virtual void eval(Map &m) const;
    // ---------- Inherited from Minimisable -----------
    virtual void AddParams(std::vector< Minim::DParamCtr > &pars);
  };

  /**
     \brief Fit for a gaussain convolved with another map
   */
  class GaussConvMap:
    public GaussMapModel
  {
    /// The map to convolve with 
    const Map conv;
    
  public:

    // ------------ Construction/ destruction ----------
    
    /**
       \param obsmap The observed map
       \param conv The map to convolve with
     */
    GaussConvMap(const Map &obsmap,
		 const Map &conv);

    // ---------- Inherited  from FittableMap ---------------
    virtual void eval(Map &m) const;
    // ---------- Inherited from Minimisable -----------
    virtual void AddParams(std::vector< Minim::DParamCtr > &pars);
  };

}

#endif
