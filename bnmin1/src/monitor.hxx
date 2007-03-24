/*
  Bojan Nikolic
  $Id: monitor.hxx,v 1.2 2005/08/21 02:42:03 bnikolic Exp $

  A base class for monitoring the progress of minimisation
*/
#ifndef _BNMIN1__MONITOR_HXX__
#define _BNMIN1__MONITOR_HXX__

namespace Minim {


  class Minimiser;

  class Monitor {

  public:

    // --------- Construction / Destruction ---------

    virtual ~Monitor() {};

    // --------- Public Interface -------------------


    virtual void Iter ( Minimiser * m) = 0;


  };

  /*! A very simple monitor ... just print out the chi square */
  class ChiSqMonitor : public Monitor {

  public:

    virtual void Iter ( Minimiser * m);    
    

  };

  /*! Print out the parameters */
  class ParsMonitor : public Monitor {

  public:

    virtual void Iter ( Minimiser * m);    

  };



}


#endif 
