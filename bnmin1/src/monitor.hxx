/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2003

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file monitor.hxx

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

  /**
     \brief Monitors the chi-square value  */
  class ChiSqMonitor: 
    public Monitor 
  {

  public:

    virtual void Iter ( Minimiser * m);    
    

  };

  /** \brief Monitors the value of the parameters */
  class ParsMonitor: 
    public Monitor 
  {
    
  public:
    
    virtual void Iter ( Minimiser * m);    

  };



}


#endif 
