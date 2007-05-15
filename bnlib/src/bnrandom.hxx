/**
   \file bnrandom.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bnikolic@nrao.edu>,
   <bojan@bnikolic.co.uk> 2004-2007

   Interface to random number generators
*/
#ifndef __BNLib_RANDOM_HXX__
#define __BNLib_RANDOM_HXX__

#include <memory>
#include <vector>


namespace BNLib{

  /// A virtual base class for random number generators 
  class RDist {
  public:
    
    // ------  Construction / Destruction -------------
    virtual ~RDist() {};

    // ------  Public interface -----------------------
    
    /// Returns a sample from the distribution
    virtual double sample(void)=0;

    /**
       Fill out the supplied vector res with random numbers sampled
       from this ditribution. Returns one further random sample.
       
       Virtual to allow more efficient implementation if a random
       number generator allows it.
       
    */
    virtual double samplefill( std::vector<double> & res );
  };


  class iNormDist;

  /// A zero-mean normal distribution
  class NormDistZM : 
    public RDist 
  {

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
