/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2003

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file minimmodel.hxx

   Models to be minimised

*/

#ifndef _BNMIN_MINIMMODEL_HXX__
#define _BNMIN_MINIMMODEL_HXX__

#include <vector>

#include "paramctr.hxx"

namespace Minim {


  
  /** \brief Interface for defining parameters contained in a model
      
      This class defines the model parameters but not the residuals.
   */
  class Model {
    
  public:
    

    // --- Constructors & Destructors -----

    Model(void) ; 

    /*! Should have a virtual destructor so that derived classes get
      properly destroyed*/
    virtual ~Model(void);

    // ---- Member functions  -------

    /**
       Each model class should add its parameters to the supplied
       parameter vector. This interface allows easy layering of
       parameters of complex models.

       Non-pure function since can be a no-op.

       \param pars vector to add this models parameters to.
     */
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );
    
    /** Adds a prefix to all parameters -- use to resolve clashes.
     */
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars , 
				    std::string &prefix);
  }; 

  /** \brief A model that defines its likelihood function

      These classes can be explored both by MCMC and maximum
      likelihood.
   */
  class MLikelihood :
    public Model
  {

  public:

    // ---------- Public interface  --------------------------

    /** \brief Return the negative log-likelihood of the current model
     */
    virtual double lLikely(void) const = 0;
    

  };

  /*! \brief A model that also defines residuals to observation
    
    These models can be exmplred by L-M algorithm
   */
  class Minimisable  : 
    public MLikelihood {
    
  public:

    // ---------- Public interface  --------------------------
    
    /// Calculates the residuals for the current model
    virtual void  residuals ( std::vector< double > & res ) const = 0;

    /// Returns the number of functions to be minimised == the number
    /// of residuals that will be evaluated
    virtual unsigned   nres (void) const  =0 ; 

    // ---------- Inherited from  MLikelihood  --------------------------

    /** Minimisation routines will already assume a gaussian error
	model on the residuals so we can do the same here and compute
	the lLikelihood from residuals.
     */
    virtual double lLikely(void) const;

     
  };

  
  /** \brief Compute the total number of parameters the model
   */
  size_t nPars(Model &m);
  

}

#endif //_BNMIN_MINIMMODEL_HXX__
  
