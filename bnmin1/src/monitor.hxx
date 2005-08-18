/*
  Bojan Nikolic
  $Id: monitor.hxx,v 1.1 2005/08/18 04:57:08 bnikolic Exp $

  A base class for monitoring the progress of minimisation
*/
#ifndef _BNMIN1__MONITOR_HXX__
#define _BNMIN1__MONITOR_HXX__

namespace Minim {


  class Minimiser;

  class Monitor {

  public:

    virtual void Iter ( Minimiser * m) = 0;


  };

  /*! A very simple monitor ... just print out the chi square */
  class ChiSqMonitor : public Monitor {

  public:

    virtual void Iter ( Minimiser * m);    
    

  };



}


#endif 
