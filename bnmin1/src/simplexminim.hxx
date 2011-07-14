/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2011

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file simplexminim.hxx
   
   Minimisation without gradients using simplex methods
*/
#ifndef _BNMIN_SIMPLEXMINIM_HXX__
#define _BNMIN_SIMPLEXMINIM_HXX__

#include "minim.hxx"

namespace Minim {

  class MLikelihood;

  class SimplexMinim :
    public ModelDesc
  {
    MLikelihood &m;

  public:

    // --------- Constructors / Desctructors -------------------

    SimplexMinim(MLikelihood &m);    
    virtual ~SimplexMinim();

    // ------------------ Inherited from Minimiser -------------
    virtual void solve(void);
    
  };



}

#endif
