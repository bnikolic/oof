/**
   \file robustline.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version 2008

   Robust line fitting model
*/
#ifndef _BNMIN_ROBUSTLINE_HXX__
#define _BNMIN_ROBUSTLINE_HXX__

#include "gradientmodel.hxx"

namespace Minim {

  /** Line Model and robust line observation rolled into one
   */
  class RobustLineObsMod :
    public LGradientModel
  {

    std::vector<double> xobs;
    std::vector<double> yobs;

    std::vector<double> ysigma;
    
  public:

    // ---------- Public data  -----------------------

    /// The linear coefficient of the line
    double a;

    /// The constant coefficient of the line
    double b;

    // ---------- Construction / Destruction --------------

    RobustLineObsMod(std::vector<double> xobs,
		     std::vector<double> yobs);


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
    void AddParams(std::vector< Minim::DParamCtr > &pars);

    
		     

  };


};

#endif
