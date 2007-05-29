/**
   \file kolmogorov_spec.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   Initial version: May 2007

   Specification of Kolmogorov Spectra
*/

#ifndef __BNLIB_KOLMOGOROV_SPEC_HXX__
#define __BNLIB_KOLMOGOROV_SPEC_HXX__

#include "unaryfn.hxx"

namespace BNLib {

  /**
     \brief Base class defining interface for specifying Kolmogorov structure functions.

     Base class for functions specifying Kolmogorov spectra /
     structure function (which is actually what is specified). Just
     the operator() is defined specifying the structure function.
  */
  class KolStructureFn : 
    public UnaryDD 
  {

  public:

  };

  /**
     \brief Kolmogorov power-law structure function.
  */
  class KolPowerLawFn : 
    public KolStructureFn
  {

  public:
    
    enum LawsPreDefined { D3Thin, D3Thick};
    
    // Power law index 
    const double xi;
    
    // --------------- Construction / Destruction ----------

    /** \brief Specify an arbitary power law index
     */
    KolPowerLawFn (double xi);

    /** \brief Specify one of the predefined laws 
     */
    KolPowerLawFn (LawsPreDefined l);    

    // --------------- Public interface --------------------

    static double GetPowerLaw( LawsPreDefined l );
    
    virtual double operator() (double x);


  };


}

#endif

