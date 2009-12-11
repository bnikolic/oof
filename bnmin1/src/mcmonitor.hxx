/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2009

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file mcmonitor.hxx

   Interface for monitoring Markov Chain type sampling
*/

#ifndef _BNMIN1_MCMONITOR_HXX__
#define _BNMIN1_MCMONITOR_HXX__

#include <cstddef>
#include <iosfwd>

namespace Minim 
{
  // Forward declarations
  struct MCPoint;

  /** \brief Base class defining the interface for monitoring
      
   */
  class MCMonitorBase
  {

  public:
    // -------------- Construction/Destruction ---------------------
    
    virtual ~MCMonitorBase();
    
    // -------------- Public Interface ----------------------

    /** Called when point p has been accepted into the chain
     */
    virtual void accept(const MCPoint& p)
    {};
    
    /** Called when point p has been proposed for the chain
     */
    virtual void propose(const MCPoint& p)
    {};

  };

  /** Simple monitoring by printing every na-th accepted and np-th
      propsed point
   */
  class SOutMCMon :
    public MCMonitorBase
  {
    
    /// Counter for the accepted points
    size_t ia;
    
    /// Counter for the proposed points
    size_t ip;

  public:

    // -------------- Public Data -----------------------------
    
    /** Every na-th accepted point will be shown
     */
    size_t na;

    /** Every np-th propsed point will be shown
     */
    size_t np;

    /** Stream to output to 
     */
    std::ostream &os;

    // -------------- Construction/Destruction ---------------------
    
    SOutMCMon(void);

    // -------------- Public Interface -----------------------------

    // --------- Inherited from MCMonitorBase --------------
    virtual void accept(const MCPoint& p);
    virtual void propose(const MCPoint& p);
    
    

  };

}

#endif
