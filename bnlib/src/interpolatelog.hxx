/*
  Bojan Nikolic
  $Id: interpolatelog.hxx,v 1.2 2005/08/29 21:02:05 bnikolic Exp $

  Routines to interpolate in log-space
*/
#ifndef BNLIB_INTERPOLATE_LOG__
#define BNLIB_INTERPOLATE_LOG__

#include "interpolate.hxx"

namespace BNLib {

  /*! Does the interpolation in log space. Currently implemented using
   *  InterpolatorGSL.
   */
  class InterpolateLog : public InterpolatorBase {
    
    InterpolatorBase * logspace;

    /*! realspace has the real space data -- use this to do the
     * integration */
    InterpolatorBase * realspace;

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
    InterpolateLog( double * xvals , double * yvals , size_t size ,
		    imethod logmethod, imethod realmethod);

    virtual ~InterpolateLog();

    /* ----------- Inherited from InterpolatorBase -------------*/

    virtual double operator() (double x)  ;
    virtual double Idx(double xmin, double xmax) ;
    

  };

  



}

#endif
