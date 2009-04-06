/** 
    \file twoerrline_imp.cxx

    Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
    Initial version 2009    


*/

#include "twoerrline_ml.hxx"

#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/io.hpp>


namespace Minim {

  LineTwoErrML::LineTwoErrML(const std::vector<double> &xvals,
			     const std::vector<double> &yvals,
			     double sigmax,
			     double sigmay):
    xobs(xvals.size()),
    yobs(yvals.size()),
    sigmax(sigmax),
    sigmay(sigmay),
    nobs(xvals.size())
  {
    for (size_t i=0; i<xobs.size(); ++i)
    {
      xobs[i]=xvals[i];
      yobs[i]=yvals[i];
    }
  }

  void LineTwoErrML::residuals(u::vector<double> &res) const
  {
    u::scalar_vector<double> ub(xobs.size(),b);
    res=yobs-xobs*a-ub;
  }

  double LineTwoErrML::lLikely(void) const
  {
    u::scalar_vector<double> ub(xobs.size(),b);
    const double ressq=std::pow(u::norm_2(yobs-xobs*a-ub),2);
    const double r=0.5*ressq/(pow(sigmay,2)+ pow(sigmax*a,2));
    return r;
  }

  void LineTwoErrML::lGrd(std::vector< double > &res) const
  {
    res.resize(2);
    u::scalar_vector<double> ub(xobs.size(),b);
    const u::vector<double> rr(yobs-xobs*a-ub);
    
    const double st=(pow(sigmay,2)+ pow(sigmax*a,2));

    res[0]= -1.0* u::inner_prod(xobs,rr) / st - u::inner_prod(rr,rr)/ pow(st,2)* a* pow(sigmax,2);
    res[1]= -1.0* u::sum(rr) / st;
  }

  LineTwoErr_LavMarq::LineTwoErr_LavMarq(const std::vector<double> &xvals,
					 const std::vector<double> &yvals,
					 double sigmax,
					 double sigmay):
    m(xvals,
      yvals,
      sigmax,
      sigmay)
  {
    m.a=1.0;
    m.b=1.0;
  }

  unsigned LineTwoErr_LavMarq::nres (void) const
  {
    return m.nobs;
  }


  void  LineTwoErr_LavMarq::residuals (std::vector<double> &res) const
  {
    res.resize(m.nobs);
    u::vector<double> rr(m.nobs);
    m.residuals(rr);
    const double st= pow((pow(m.sigmay,2)+ pow(m.sigmax*m.a,2)), 0.5);
    rr=rr/st;
    std::copy(rr.begin(),
	      rr.end(),
	      res.begin());
  }

  void LineTwoErr_LavMarq::AddParams(std::vector< Minim::DParamCtr > &pars)
  {
    m.AddParams(pars);
  }



}




