/*
  Bojan Nikolic
  $Id: minimmodel.hxx,v 1.1 2005/06/02 13:43:18 bnikolic Exp $

  Models to be minimised

*/

#ifndef _BNMIN_MINIMMODEL_HXX__
#define _BNMIN_MINIMMODEL_HXX__

#include <vector>

#include "paramctr.hxx"

namespace Minim {


  
  /*! This class defines the model parameters but not the residuals.
   */
  class Model {
    
  public:

    Model(void) {} ; 
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );
    
    /// Adds a prefix to all parameters -- use to resolve clashes.
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars , std::string prefix);

  }; 

  /*! This also defines the residuals 
   */
  class Minimisable  : public Model {
    
  public:
    
    /// Calculates the residuals for the current model
    virtual void  residuals ( std::vector< double > & res ) = 0;

    /// Returns the number of functions to be minimised == the number
    /// of residuals that will be evaluated
    virtual unsigned   nres (void)  =0 ; 

    
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars )  {};
     
  };

  

}

#endif //_BNMIN_MINIMMODEL_HXX__
  
