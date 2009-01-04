/**
   \file robustline.cxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version 2008

*/

#include "robustline.hxx"

#include <cmath>

namespace Minim {

  RobustLineObsMod::RobustLineObsMod(std::vector<double> xobs,
				     std::vector<double> yobs):
    nobs(xobs.size()),
    xobs(xobs),
    yobs(yobs),
    ysigma(xobs.size(),1.0)
  {
  }

  void RobustLineObsMod::residuals(std::vector<double> &res) const
  {
    res.resize(nobs);
    for(size_t i =0; i<nobs; ++i)
    {
      res[i]=(yobs[i]-xobs[i]*a-b)/ysigma[i];
    }
  }

  void RobustLineObsMod::dres_da(std::vector<double> &res) const
  {
    res.resize(nobs);
    for(size_t i =0; i<nobs; ++i)
    {
      res[i]=-xobs[i]/ysigma[i];
    }
  }

  void RobustLineObsMod::dres_db(std::vector<double> &res) const
  {
    res.resize(nobs);
    for(size_t i =0; i<nobs; ++i)
    {
      res[i]=-1.0/ysigma[i];
    }
  }

  double RobustLineObsMod::lLikely(void) const
  {
    std::vector<double> res;
    residuals(res);

    double tot=0;
    for(size_t i=0; i<nobs; ++i)
    {
      tot+=fabs(res[i]);
    }
    return tot;
  }

  void RobustLineObsMod::lGrd(std::vector< double > &out) const
  {
    out=std::vector<double>(2,0);

    std::vector<double> res;
    residuals(res);

    std::vector<double> da,db;
    dres_da(da);
    dres_db(db);    

    size_t nobs=xobs.size();
    for(size_t i=0; i<nobs; ++i)
    {
      if(res[i]==0)
      {
	out[0]+=0;
	out[1]+=0;
      }
      else if(res[i]>0)
      {
	out[0] += da[i];
	out[1] += db[i];
      }
      else
      {
	out[0] -= da[i];
	out[1] -= db[i];
      }
    }
  }
  
  
  void RobustLineObsMod::AddParams(std::vector< Minim::DParamCtr > &pars)
  {
    ParamCtr<double> pa(&a, 
			"a", 
			true, 
			"Linear term");
    ParamCtr<double> pb(&b, 
			"b", 
			true, 
			"Constant term");
    pars.push_back(pa);
    pars.push_back(pb);
  }
    

}
