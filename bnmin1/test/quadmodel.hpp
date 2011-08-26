/// Bojan Nikolic <bojan@bnikolic.co.uk>

#include "../src/minimmodel.hxx"
#include "../src/gradientmodel.hxx"
#include <cmath>

class QuadModel :
  public Minim::Model
{

public:
  
  double a, b ,c;
  
  const size_t m;

  QuadModel():
    a(0),
    b(0),
    c(0),
    m(3)
  {
  }
  
  double eval(const std::vector<double> & x,
	      std::vector<double> & res) const
  {
    res.resize(x.size() );
    for (size_t i = 0 ; i< x.size() ; ++i)
    {
      res[i]= c*pow(x[i],2) + b* x[i] + a ;
    }
  }

  double grad(double x,
	      std::vector<double> & res) const
  {
    res=std::vector<double>(3,0.0);
    
    res[0] += 1;
    res[1] += x;
    res[2] += pow(x,2);

  }

  void AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    using namespace Minim;

    ParamCtr<double> pa( &a, 
			 "a", 
			 true, 
			 "Constant term");
    ParamCtr<double> pb( &b, 
			 "b", 
			 true, 
			 "Linear term");

    ParamCtr<double> pc( &c, 
			 "c", 
			 true, 
			 "Quadratic term");
    
    pars.push_back(pa);
    pars.push_back(pb);
    pars.push_back(pc);
  }
};


class QuadObs :
  public Minim::Minimisable
{
  std::vector<double> x;
  std::vector<double> obs;
  mutable std::vector<double> scratch;
public:
 
  QuadModel  qm;
  double sigma;

  QuadObs( const std::vector<double> &x,
	   const std::vector<double> &obs):
    x(x),
    obs(obs),
    scratch(obs.size()),
    sigma(1.0)
  {
  }
  
  unsigned   nres (void) const
  {
    return obs.size();
  }

  void  residuals ( std::vector< double > & res ) const
  {
    qm.eval( x, scratch);
    for(size_t i =0; i<obs.size(); ++i)
      res[i]=(obs[i]-scratch[i])/sigma;
  }
  

  void AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    qm.AddParams(pars);
  }

  QuadObs * clone(void)
  {
    return new QuadObs(x, obs);
  }


};

/**
   Derive from a hirearchy that allows goodness of fit other thatn
   residuals-square. 

 */
class QuadGrad :
  public Minim::LGradientModel
{
  std::vector<double> x;
  std::vector<double> obs;
  mutable std::vector<double> vscratch;
  mutable std::vector<double> gscratch;
public:
 
  QuadModel  qm;
  double sigma;

  QuadGrad( const std::vector<double> &x,
	    const std::vector<double> &obs):
    x(x),
    obs(obs),
    vscratch(obs.size()),
    gscratch(obs.size()),
    sigma(1.0)
  {
    qm.c=1.0;
  }
  
  unsigned   nres (void) const
  {
    return obs.size();
  }

  void  residuals ( std::vector< double > & res ) const
  {
    res.resize(x.size());
    qm.eval( x, vscratch);
    for(size_t i =0; i<obs.size(); ++i)
      res[i]=(obs[i]-vscratch[i])/sigma;
  }

  double lLikely(void) const
  {
    double tot=0;
    std::vector<double> res;
    residuals(res);
    for (size_t i=0; i<res.size(); ++i)
    {
      tot+=pow(res[i],2);
    }
    return tot;
  }

  void lGrd(std::vector< double > &res) const
  {
    const size_t m = 3;

    const size_t n = x.size();
    qm.eval(x, vscratch);

    res=std::vector<double>(m,0.0);

    for (size_t j=0; j<n; ++j)
    {
      qm.grad(x[j],
	      gscratch);

      for (size_t i =0; i<m; ++i)
      {
	res[i]+= -2.0*(obs[j]-vscratch[j])*gscratch[i]/pow(sigma,2);
      }
    }
  }

  void AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    qm.AddParams(pars);
  }


};

