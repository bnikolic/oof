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
  
  Gen1Model::~Gen1Model()
  {
  }

  double Gen1Const::f(double  x) const
  {
    return c;
  }
  
  void Gen1Const::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    pars.push_back(Minim::DParamCtr (&c,      
				     "c", 
				     true     ,                       
				     "Constant"
				      ));
  }

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

  double Gen1LineBroken::f(double  x) const
  {
    if (x<breakx)
    {
      return (a+breakmag)*(x-breakx) + a*breakx +b;
    }
    else
    {
      return a*x+b;
    }
  }
  
  void Gen1LineBroken::AddParams(std::vector<Minim::DParamCtr> &pars)
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

    pars.push_back(Minim::DParamCtr (&breakx,      
				     "breakx", 
				     true     ,                       
				     "Position of the break"
				      ));
  }

  double Gen1LineNorm::f(double  x) const
  {
    const double norm=0.5*(a*a0+a*a1)*(a1-a0);
    return a*x-norm+b;
  }
  
  void Gen1LineNorm::AddParams(std::vector<Minim::DParamCtr> &pars)
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
    return std::pow(10,l_a)*std::pow(x,p);
  }
  
  void Gen1Plaw::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    pars.push_back(Minim::DParamCtr (&l_a,      
				     "l_a", 
				     true     ,                       
				     "Log10 amplitude at unit ordinate"
				      ));
    pars.push_back(Minim::DParamCtr (&p,      
				     "p", 
				     true     ,                       
				     "Index of the power law"
				      ));
  }

  double Gen1ConstScale::f(double  x) const
  {
    return std::pow(10,l_c);
  }
  
  void Gen1ConstScale::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    pars.push_back(Minim::DParamCtr (&l_c,      
				     "l_c", 
				     true     ,                       
				     "Log10 of the constant value"
				      ));
  }

  void Gen1Comp::add(Gen1Model *m)
  {
    vm.push_back(m);
  }
  
  double Gen1Comp::f(double  x) const
  {
    double res=0;
    for (size_t i=0; i<vm.size(); ++i)
      res+=vm[i].f(x);
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

  void Gen1CompExp::add(Gen1Model *m)
  {
    vm.push_back(m);
  }
  
  double Gen1CompExp::f(double  x) const
  {
    double res=0;
    for (size_t i=0; i<vm.size(); ++i)
      res+=std::pow(10,vm[i].f(x));
    return std::log10(res);
  }

  void Gen1CompExp::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    for(size_t i=0; i<vm.size(); ++i)
    {
      std::string pref(boost::str(boost::format("c%i") %i));
      vm[i].AddParams(pars, 
		      pref);
    }
  }

  Gen1Obs::Gen1Obs(Gen1Model *m):
    m(m)
  {
  }

  void Gen1Obs::add(double x,
		     double y,
		     double y_err)
  {
    Gen1Datum d;
    d.x=x;
    d.y=y;
    d.y_err=y_err;
    o.push_back(d);
  }

  void Gen1Obs::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    m->AddParams(pars);
  }

  double Gen1Obs::lLikely(void) const
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


