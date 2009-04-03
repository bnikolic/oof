/**
   \file linemodel.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version April 2009
   
*/
#ifndef _BNMIN1_LINEMODEL_HXX__
#define _BNMIN1_LINEMODEL_HXX__

#include "gradientmodel.hxx"

namespace Minim {
  
  class LineMod:
    public LGradientModel
  {

  public:

    // ---------- Public data  -----------------------

    /// The linear coefficient of the line
    double a;

    /// The constant coefficient of the line
    double b;

    // -------------------- Inherited functions ---------------
    void AddParams(std::vector< Minim::DParamCtr > &pars);    

  };


}

#endif
