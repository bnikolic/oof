/**
   \file mcpoint.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Structure representing a Markov Chain point
*/

#ifndef _BNMIN1_MCPOINT_HXX__
#define _BNMIN1_MCPOINT_HXX__

#include <vector>
#include <list>
#include <set>

namespace Minim {

  /** \brief Data to be recorded at each point in an MCMC distribution
  */
  struct MCPoint
  {
    /// The actual parameters
    std::vector<double> p;
    /// Log-likelihood of this point
    double ll;
    /// A vector to store derived quantities at sample of the
    /// distribution
    std::vector<double> fval;

    /// Default constructor allowed, fill in the data later
    MCPoint(void);

    /** \Construct with supplied position vector
     */
    MCPoint(const std::vector<double> &p);

    /** \brief The parameter vector has n values
     */
    MCPoint(size_t np);

    MCPoint(const MCPoint &other);

    MCPoint & operator=(const MCPoint &other);
    
    
  };

  /** \brief Define ordering of MCPoints on basis of their likelihood

      Should be useful for nested sampling
  */
  inline bool operator< (const MCPoint &a, const MCPoint &b)
  {
    return a.ll < b.ll;
  }

  /** \brief Weighted posterior point

      As produced by non markov chain posterior exploration
   */
  struct WPPoint:
    public MCPoint
  {
    /** \brief Weight factor
     */
    double w;
    
    WPPoint(void):
      w(0.0)
    {
    }

    WPPoint(const std::vector<double> &p,
	    double w):
      MCPoint(p),
      w(w)
    {
    }

    /** \brief Construct from MCPoint and a supplied weight
     */
    WPPoint(const MCPoint &mp,
	    double w):
      MCPoint(mp),
      w(w)
    {
    }
    
  };

  /** \brief Calculate the first moment of each parameter
   */
  void moment1(const std::list<WPPoint> &l,
	       std::vector<double> &res);

  void moment1(const std::list<WPPoint> &l,
	       double Z,
	       std::vector<double> &res);

  /** \brief Calculate the second moment of each parameter
   */
  void moment2(const std::list<WPPoint> &l,
	       const std::vector<double> &m1,
	       std::vector<double> &res);

  void moment2(const std::list<WPPoint> &l,
	       const std::vector<double> &m1,
	       double Z,
	       std::vector<double> &res);


  void moment1(const std::set<MCPoint> &s,
	       std::vector<double> &res);

  void moment2(const std::set<MCPoint> &s,
	       const std::vector<double> &m1,
	       std::vector<double> &res);

  void StdDev(const std::set<MCPoint> &s,
	      std::vector<double> &res);
  



}

#endif
