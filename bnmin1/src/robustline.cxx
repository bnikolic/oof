/**
   \file robustline.cxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version 2008

*/

#include "robustline.hxx"

#include <cmath>
#include <iostream>

namespace Minim {

  RobustLineObsMod::RobustLineObsMod(const std::vector<double> &xobs,
				     const std::vector<double> &yobs):
    nobs(xobs.size()),
    xobs(xobs),
    yobs(yobs),
    ysigma(xobs.size(),1.0)
  {
    a=1;
    b=0;
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
      res[i]= (-1.0 * xobs[i]/ysigma[i]);
    }
  }

  void RobustLineObsMod::dres_db(std::vector<double> &res) const
  {
    res.resize(nobs);
    for(size_t i =0; i<nobs; ++i)
    {
      res[i]= (-1.0/ysigma[i]) ;
    }
  }

  double RobustLineObsMod::lLikely(void) const
  {
    std::vector<double> res;
    residuals(res);

    double tot=0;
    for(size_t i=0; i<nobs; ++i)
    {
      if (fabs(res[i])  < ysigma[i])
      {
	tot += pow(res[i],2);
      }
      else
      {
	tot+=fabs(res[i]);
      }
    }
    return tot;
  }

  void RobustLineObsMod::lGrd(std::vector< double > &out) const
  {
    out.resize(2);
    out[0]=out[1]=0;

    std::vector<double> res;
    residuals(res);

    std::vector<double> da,db;
    dres_da(da);
    dres_db(db);    

    for(size_t i=0; i<nobs; ++i)
    {
      if(fabs(res[i]) < ysigma[i])
      {
	out[0]+= -2 * res[i] * xobs[i]/ pow(ysigma[i],2);
	out[1]+= -2 * res[i] / pow(ysigma[i],2);
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

}
