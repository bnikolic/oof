/**
   \file monitor.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>

   A base class for monitoring the progress of minimisation
*/
#ifndef _BNMIN1__MONITOR_HXX__
#define _BNMIN1__MONITOR_HXX__

namespace Minim {


  class Minimiser;

  /** \brief Defines an interface from monitoring the progress of a
      minimisation
   */
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
