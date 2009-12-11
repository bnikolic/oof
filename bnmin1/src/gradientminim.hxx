/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2008

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file gradientminim.hxx
   
   Minimisation with gradients of the likelihood function
*/
#ifndef _BNMIN_GRADIENTMINIM_HXX__
#define _BNMIN_GRADIENTMINIM_HXX__

#include "minim.hxx"


namespace Minim {


  // Forwards
  class LGradientModel;

  /** \brief Minimisation using the Broyden-Fletcher-Goldfarb-Shanno
     version 2 algorithm

   */
  class BFGS2Minim :
    public ModelDesc
  {
    LGradientModel &lgm;

  public:

    // --------- Constructors / Desctructors -------------------

    BFGS2Minim(LGradientModel &pm);    
    virtual ~BFGS2Minim(){};    

    // ------------------ Inherited from Minimiser -------------
    virtual void solve(void);
    
  };

  

}

#endif
