// Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
// Initial version December 2009
//
// This file is part of BNMin1 and is licensed as described in file
// COPYING

/**
   \file bayesline.cxx

*/

#include <cmath>

#include "bayesline.hxx"
#include "../mcpoint.hxx"

namespace Minim {

  LineLkl::LineLkl(const std::vector<double> &x,
		   const std::vector<double> &y,
		   double sigmax,
		   double sigmay):
    x(x), y(y),
    sigmax(sigmax),
    sigmay(sigmay)
  {
  }

  double LineLkl::lLikely(void) const
  {
    const double a= pow(10,Ry)/pow(10,Rx);
    const double b= y0- a*x0;
    const double R= sqrt(pow(10,Rx)*pow(10,Ry));

    const double A=a/(R*R) + 1.0/(sigmax*sigmax) + a*a/(sigmay*sigmay);

    const size_t N=x.size();
    
    double res= N * log(2 * M_PI * pow(10,Rx) * sigmax * sigmay);

    res += N*-0.5 * log(2 *M_PI / A);
    
    for (size_t i=0; i<N; ++i)
    {
      res += pow(y[i]-b, 2)/pow(sigmay,2);
      res += pow(x[i], 2)/pow(sigmax,2);
      res += a* pow(x0,2)/ pow(R,2);
      const double nm = a*x0/pow(R,2)- a*b/pow(sigmay,2) + a* y[i]/pow(sigmay,2) + x[i]/pow(sigmax,2);
      res -= pow( nm,2)/A;
    }
    return res;
  }

  void LineLkl::AddParams(std::vector< Minim::DParamCtr > &pars) 
  {
    pars.push_back(ParamCtr<double>(&x0, 
				    "x0", 
				    true, 
				    "Location of x-points"));
    pars.push_back(ParamCtr<double>(&y0, 
				    "y0", 
				    true, 
				    "Location of y-points"));

    pars.push_back(ParamCtr<double>(&Rx, 
				    "Rx", 
				    true, 
				    "Log10 range in x-direction"));
    pars.push_back(ParamCtr<double>(&Ry, 
				    "Ry", 
				    true, 
				    "Log10 range in y-direction"));

  }

  void margin(const std::list<WPPoint> &l,
	      double Z,
	      LineFit &res)
  {
    double a1=0;
    double a2=0;
    double b1=0;
    double b2=0;
    for(std::list<WPPoint>::const_iterator i=l.begin();
	i!= l.end();
	++i)
    {
      const double ww=i->w * exp(- i->ll);
      const double a= pow(10,i->p[3])/pow(10,i->p[2]);
      const double b= i->p[1]- a*i->p[0];      
      a1+=a*ww ;
      a2+=pow(a,2)* ww;
      b1+=b*ww;
      b2+=pow(b,2)*ww;
    }
    res.a=a1/Z;
    res.b=b1/Z;
    res.cv[0]=a2/Z-pow(res.a,2);
    res.cv[3]=b2/Z-pow(res.b,2);
  }


}



