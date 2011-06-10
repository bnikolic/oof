// Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
// Initial version June 2011
//
// This file is part of BNMin1 and is licensed as described in file
// COPYING
/**
   \file gen1dfit.hxx
*/
#ifndef _BNMIN1_APP_GEN1DFIT_HXX__
#define _BNMIN1_APP_GEN1DFIT_HXX__

#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "../src/minimmodel.hxx"

namespace Minim {

  class Gen1Model:
        public Minim::Model
  {

  public:
    
    virtual ~Gen1Model();
    
    virtual double f(double  x) const = 0;

  };

  class Gen1Line:
    public Gen1Model
  {

  public:
    
    double a;
    double b;

    virtual double f(double  x) const;
    void AddParams(std::vector<Minim::DParamCtr> &pars);
  };

  class Gen1Plaw:
    public Gen1Model
  {

  public:
    
    double l_a;
    double p;

    virtual double f(double  x) const;
    void AddParams(std::vector<Minim::DParamCtr> &pars);
  };

  class Gen1ConstScale:
    public Gen1Model
  {

  public:
    
    double l_c;

    virtual double f(double  x) const;
    void AddParams(std::vector<Minim::DParamCtr> &pars);
  };

  class Gen1Comp:
    public Gen1Model
  {

    boost::ptr_vector<Gen1Model> vm;

  public:

    /**
       Takes ownwership of the supplied object
     */
    void add(Gen1Model *m);
    
    virtual double f(double  x) const;
    void AddParams(std::vector<Minim::DParamCtr> &pars);
  };

  

  /** Generalised 1D observation with error only in the observed value
   */
  struct Gen1Datum {
    double x;
    double y;
    double y_err;
  };

  /**
   */
  class Gen1Obs:
    public Minim::MLikelihood
  {
    /// This is the model for the observations
    boost::scoped_ptr<Gen1Model> m;
    
    /// These are the observations
    std::vector<Gen1Datum> o;

  public:
    
    Gen1Obs(Gen1Model *m);
    
    /** Add a new observed point to the set
     */
    void add(double x,
	     double y,
	     double y_err);    
    
    // ---------- Inherited from MLikelihood -----------
    void AddParams(std::vector<Minim::DParamCtr> &pars);
    double lLikely(void) const;
    
  };
  

}

#endif
