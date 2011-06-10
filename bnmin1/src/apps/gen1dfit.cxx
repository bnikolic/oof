// Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
// Initial version June 2011
//
// This file is part of BNMin1 and is licensed as described in file
// COPYING
/**
   \file gen1dfit.cxx
*/

#include <cmath>
#include <boost/format.hpp>

#include "gen1dfit.hxx"

namespace Minim {

  double Gen1Line::f(double  x) const
  {
    return a*x+b;
  }
  
  void Gen1Line::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    pars.push_back(Minim::DParamCtr (&a,      
				     "a", 
				     true     ,                       
				     "Slope of the line"
				      ));
    pars.push_back(Minim::DParamCtr (&b,      
				     "b", 
				     true     ,                       
				     "Constant"
				      ));
  }

  double Gen1Plaw::f(double  x) const
  {
    return std::pow(x/a,p);
  }
  
  void Gen1Plaw::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    pars.push_back(Minim::DParamCtr (&a,      
				     "a", 
				     true     ,                       
				     "Ordinate at which power law is normalised"
				      ));
    pars.push_back(Minim::DParamCtr (&p,      
				     "p", 
				     true     ,                       
				     "Index of the power law"
				      ));
  }

  void Gen1Comp::add(Gen1Model *m)
  {
    vm.push_back(m);
  }
  
  double Gen1Comp::f(double  x) const
  {
    double res=0;
    BOOST_FOREACH(const Gen1Model &m, vm)
      res+=m.f(x);
    return res;
  }

  void Gen1Comp::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    for(size_t i=0; i<vm.size(); ++i)
    {
      std::string pref(boost::str(boost::format("c%i") %i));
      vm[i].AddParams(pars, 
		      pref);
    }
  }

  Line1Obs::Line1Obs(Gen1Model *m):
    m(m)
  {
  }

  void Line1Obs::add(double x,
		     double y,
		     double y_err)
  {
    Gen1Datum d;
    d.x=x;
    d.y=y;
    d.y_err=y_err;
    o.push_back(d);
  }

  void Line1Obs::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    m->AddParams(pars);
  }

  double Line1Obs::lLikely(void) const
  {
    const size_t n=o.size();
    double res=0;
    for(size_t i=0; i<n; ++i)
    {
      const double vm=m->f(o[i].x);
      const double v=o[i].y;
      const double fnoise=o[i].y_err;
      res += 0.5* std::pow( (v - vm)/fnoise, 2);
      res += 0.5*std::log(2*M_PI*pow(fnoise,2));
    }
    return res;
  }

}


