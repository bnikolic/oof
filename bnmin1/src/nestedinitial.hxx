/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version November 2009

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file nestedinitial.hxx

   Strategies for picking the initial point to start from when doing
   constrained prior sampling

*/
#ifndef _BNMIN1_NESTEDINITIAL_HXX__
#define _BNMIN1_NESTEDINITIAL_HXX__

#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>

namespace Minim {

  class MCPoint;
  class NestedS;

  /** Base class for strategies for picking the inital point for the
      nested sampling, i.e., where to start sampling the prior with
      the likelihood constraint
   */
  class NestedInitial {

  public:

    virtual ~NestedInitial();
    
    /** \brief Return a point to start from 
	
	\note The returned reference *must* point to an object owned
	by "ns" to ensure the reference doesn't dangle
     */
    virtual const MCPoint & operator()(const NestedS &ns) =0;

  };

  /** Start the prior sampling from the worst point in the live set
   */
  class InitialWorst:
    public NestedInitial
  {
  public:

    const MCPoint & operator()(const NestedS &ns);
  };

  /** Start the prior sampling from a random point in the live set
   */
  class InitialRandom:
    public NestedInitial
  {
    boost::mt19937 eng;
    boost::uniform_int<size_t> gen;
			   
  public:

    /**
       \param n_ss number of elements in the live set
     */
    InitialRandom(size_t n_ss);

    const MCPoint & operator()(const NestedS &ns);
  };


}

#endif
