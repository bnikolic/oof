/*
  Bojan Nikolic
  $Id: gsl_utils.hxx,v 1.1 2005/07/17 19:25:58 bnikolic Exp $

  Some helper classes for dealing with gsl
*/
#ifndef _ADAS_GSL_UTILS_HXX__
#define _ADAS_GSL_UTILS_HXX__

#include <gsl/gsl_errno.h>

namespace BNLib
{

  /*!
   * Turns off the default "Dump core" gsl error handler
   */
  class GSLCheck {

    gsl_error_handler_t * h;

  public:

    GSLCheck(void)     { 
      h=gsl_set_error_handler_off () ;
    };

    ~GSLCheck()  { 
      gsl_set_error_handler (h); 
    }

  };
}
  

#endif 
