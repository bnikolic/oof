/*
  Bojan Nikolic
  $Id: bnrandom.hxx,v 1.1 2005/06/21 11:42:12 bnikolic Exp $

  Interface to random number generators

*/
#ifndef __BNLib_RANDOM_HXX__
#define __BNLib_RANDOM_HXX__

#include <memory>


namespace BNLib{

  /// A virtual base class for random number generators 
  class RDist {
  public:
    
    /// Returns a sample from the distribution
    virtual double sample(void)=0;
  };



  class iNormDist;

  /// A zero-mean normal distribution
  class NormDistZM : public RDist {

    /// This is the implementation class
    std::auto_ptr<iNormDist> ip;
    
    /// The standard deviation of the distribution.
    double sigma;

  public:
    
    /// sigma is the standard deviation
    NormDistZM ( double sigma );
    virtual ~NormDistZM() ;

    /// Return a sample from the normal distribution
    double sample(void);

    /// Re-seed the random number generator; 0=> default seed
    void reseed(unsigned long int Seed);
    
  };
  
  /// Returns a seed derived from the system clock
  unsigned long int  TimeSeed(void);

  class iUniformDist;
  /// Uniform random distribution in the range [0,1)
  class UniformDist : public RDist {

    std::auto_ptr<iUniformDist> ip;
    
  public:
    
    UniformDist();
    virtual ~UniformDist();

    double sample(void);

    void reseed(unsigned long int Seed);
    
  };



}

#endif
