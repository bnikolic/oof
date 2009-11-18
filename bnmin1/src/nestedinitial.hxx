/**
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version November 2009

   \file nestedinitial.hxx

*/
#ifndef _BNMIN1_NESTEDINITIAL_HXX__
#define _BNMIN1_NESTEDINITIAL_HXX__

namespace Minim {

  class MCPoint;
  class NestedS;

  /** Base class for strategies for picking the inital point for the
      nested sampling, i.e., where to start sampling the prior with
      the likelihood constraint
   */
  class NestedInitial {

  public:
    
    virtual const MCPoint & operator()(const NestedS &ns) =0;

  };

  class InitialWorst:
    public NestedInitial
  {
  public:

    const MCPoint & operator()(const NestedS &ns);
  };


}

#endif
