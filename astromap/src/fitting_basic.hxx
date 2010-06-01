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

  /** A model for a map 
   */
  class ModelMap:
    public Minim::Model
  {
  public:

    // ---------- Public data ------------

    /**
       If this parameter is false the fitting will be carried out in
       pixel coordinates rather then world coordinates.
     */
    bool worldcs;

    // -------------- Construction / Destruction ------------

    /**
       Default constructor to set the public data
     */
    ModelMap(void);

    virtual ~ModelMap();

    // -------------- Public interface ----------------------
    
    /** \brief Set a map according to the current model

	This function defines the interface of a ModelMap
     */
    virtual void eval(Map &m) const =0;

  };

  /**
     A map model based on a simple function of two variables
   */
  class ModelMapFn:
    public ModelMap
  {

    //// The model to be fit
    BNLib::BinaryDD * model;

  public:

    // -------------- Construction / Destruction ------------

    ModelMapFn(void);

    // -------------- Public interface ----------------------

    /** \brief Set the model to fit for
     */
    void SetModel(BNLib::BinaryDD *mod);

    // ------- Inhertied from ModelMap ----------------------
    virtual void eval(Map &m) const;    
    
  };
    

  /** \brief Fitting of map models to an observed map
   */
  class FittableMap :
    public ModelMapFn,
    public Minim::Minimisable
  {

    /// Observed map
    const Map & map;

    /// A scratch map to compute the model on
    mutable Map mtemp;

  public:

    // ---------- Construction/Destruction -------------

    /**

       \param map the map to be fitted to
       
       \note still need to add parameters after construction
     */
    FittableMap(const Map &map);

    // ---------- Public interface         -------------


    /** \brief return a copy of the scratch map
	
     */
    Map *ScratchCopy(void);


    // ---------- Inherited from Minimisable -----------
    virtual void residuals( std::vector< double > &res) const;
    virtual unsigned nres(void) const; 
  };

  /** \brief A gaussian model for a map

      This class defines just the model, and not the actual comparison
      to the observed data which is done in GaussMapModel
   */
  class GaussMapModel_:
    public ModelMapFn
  {
  public:

    // ---------- Public data ------------

    /**
       The gaussian model. Publicly expose for easy introspection.
     */
    BNLib::GaussianDD gm;

    // ------------ Construction/ destruction ----------
    
    GaussMapModel_(void);

    // ---------- Inherited  from MapModel ---------------
    virtual void eval(Map &m) const;
    virtual void AddParams(std::vector< Minim::DParamCtr > &pars);
  };

  /**
     \brief Fit a gaussian to a map.
   */
  class GaussMapModel:
    public FittableMap,
    public GaussMapModel_
  {
  public:

    // ------------ Construction/ destruction ----------
    
    GaussMapModel(const Map  &map);
  };

  /**
     \brief Model with Gaussian and convolution
   */
  class GaussConvMap_:
    public GaussMapModel_
  {
    /// The map to convolve with 
    const Map conv;
    
  public:

    // ------------ Construction/ destruction ----------
    
    /**
       \param obsmap The observed map
       \param conv The map to convolve with
     */
    GaussConvMap_(const Map &conv);

    virtual void eval(Map &m) const;
    virtual void AddParams(std::vector< Minim::DParamCtr > &pars);
  };

  /**
     \brief Fit for a gaussain convolved with another map
   */
  class GaussConvMap:
    public FittableMap,    
    public GaussConvMap_
  {
    
  public:

    // ------------ Construction/ destruction ----------
    
    /**
       \param obsmap The observed map
       \param conv The map to convolve with
     */
    GaussConvMap(const Map &obsmap,
		 const Map &conv);

    virtual void AddParams(std::vector< Minim::DParamCtr > &pars);
    virtual void eval(Map &m) const;    
  };

}

#endif
