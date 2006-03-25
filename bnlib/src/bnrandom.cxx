/*
  Bojan Nikolic
  $Id: bnrandom.cxx,v 1.2 2006/03/25 14:29:30 bnikolic Exp $

*/

#include "bnrandom.hxx"


// GSL stuff..
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

// Time stuff 
#include <sys/time.h>

namespace BNLib { 

  /*! Implements random number generation using GSL */
  class GSLRanGen {
    gsl_rng * generator;
  public:
    
    GSLRanGen(unsigned long int Seed=0);
    
    operator gsl_rng* () { return generator; };
    
    void seed(unsigned long seed) {
      gsl_rng_set(generator, seed);
    }
    
  };

  GSLRanGen::GSLRanGen(unsigned long int Seed) {
    generator=gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(generator, Seed);
  }
  
  /// Base class for implementations of random distributions using GSL
  class iGSLRNG {

  protected:
    
    /// The GSL random number generator
    std::auto_ptr<GSLRanGen> rangen;

  public:
    
    iGSLRNG () : 
      rangen( new GSLRanGen(0 ))
    {
    }
    
    void reseed(unsigned long int Seed ) {
      rangen->seed(Seed);
    }
  };


  class iNormDist : public iGSLRNG {
    
    /// the standard deviation of the distribution
    double sigma;

  public:

    iNormDist ( double sigma) : 
      sigma(sigma)
    {    };

    double sample(void) {
      return gsl_ran_gaussian(*rangen, sigma);
    };

  };


  NormDistZM::NormDistZM(double sigma) : 
    ip(new iNormDist(sigma)) ,
    sigma(sigma)
  {
  }
  
  double NormDistZM::sample(void){
    return ip->sample();
  }

  void NormDistZM::reseed(unsigned long int Seed) {
    ip->reseed(Seed);
  }
  
   NormDistZM::~NormDistZM() 
   {}
  
  unsigned long int  TimeSeed(void){
    timeval t;
    gettimeofday( &t, NULL );
    return t.tv_sec+t.tv_usec;

  }

  class iUniformDist  : public iGSLRNG {
    
  public:
    double sample(void) {
      return gsl_rng_uniform( *rangen);
    }
  };

  UniformDist::UniformDist() :
    ip( new  iUniformDist )
  {
  }

  UniformDist::~UniformDist() 
  {
  }

  double UniformDist::sample(void) {
    return ip->sample();
  }

  void UniformDist::reseed(unsigned long int Seed) {
    ip->reseed(Seed);
  }


    

}

