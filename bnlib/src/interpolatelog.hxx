/*
  Copyright:
  Bojan Nikolic

  Routines to interpolate in log-space
*/
#ifndef BNLIB_INTERPOLATE_LOG__
#define BNLIB_INTERPOLATE_LOG__

#include "interpolate.hxx"

#include <memory>


namespace BNLib {

  /*! Does the interpolation in log space. Currently implemented using
   *  InterpolatorGSL.
   */
  class InterpolatorLog : public InterpolatorBase {

    /*! Already pulled in interpolate.hxx so use auto_ptr. Note for
     *  Dominic: I often don't use auto_ptr in class definitions when
     *  it would involve pulling in extra header files. They are most
     *  useful in functions to make sure everything gets deleted if
     *  the logic of the function is changed and/or exceptions thrown.
     */
    std::auto_ptr<InterpolatorBase> logspace;

    /*! realspace has the real space data -- use this to do the
     * integration .
     */
    std::auto_ptr<InterpolatorBase> realspace;

  public:

    /*! Log space interpolation. Two methods are supplied: logmethod
     *  is the method to use when evaluting the function at particular
     *  points -- this is the main aim of the class and actuall
     *  interpolation will be done in log space. 
     *  
     *  In order to support integration of the data a real space
     *  version of data is retained. The interpolation method used for
     *  this is realmethod. Setting this to linear should avoid any
     *  numerical problems.
     * 
     **/
    InterpolatorLog( const double * xvals , 
		     const double * yvals , 
		     size_t size ,
		     imethod logmethod, imethod realmethod);

    virtual ~InterpolatorLog();

    /* ----------- Inherited from InterpolatorBase -------------*/

    virtual double operator() (double x)  ;
    virtual double Idx(double xmin, double xmax) ;
    

  };

  



}

#endif
