/**
   \file robustline.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version 2008

   Robust line fitting model
*/
#ifndef _BNMIN_ROBUSTLINE_HXX__
#define _BNMIN_ROBUSTLINE_HXX__

#include "linemodel.hxx"

namespace Minim {

  /** Line Model and robust line observation rolled into one
   */
  class RobustLineObsMod :
    public LineMod
  {

    const size_t nobs;

    std::vector<double> xobs;
    std::vector<double> yobs;

    std::vector<double> ysigma;
    
  public:

    // ---------- Construction / Destruction --------------

    RobustLineObsMod(const std::vector<double> &xobs,
		     const std::vector<double> &yobs);


    void residuals (std::vector<double> &res) const;

    /** Derivative of residuals wrt parameter "a"
     */
    void dres_da(std::vector<double> &res) const;

    /** Derivative of residuals wrt parameter "b"
     */
    void dres_db(std::vector<double> &res) const;

    
    // -------------------- Inherited functions ---------------

    double lLikely(void) const;
    void lGrd(std::vector< double > &res) const;

  };


};

#endif
