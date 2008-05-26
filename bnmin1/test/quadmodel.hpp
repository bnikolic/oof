/// Bojan Nikolic <bojan@bnikolic.co.uk>

#include "minimmodel.hxx"
#include <cmath>

class QuadModel :
  public Minim::Model
{

public:
  
  double a, b ,c;

  QuadModel():
    a(0),
    b(0),
    c(0)
  {
  }
  
  double eval(const std::vector<double> & x,
	      std::vector<double> & res)
  {
    res.resize(x.size() );
    for (size_t i = 0 ; i< x.size() ; ++i)
    {
      res[i]= c*pow(x[i],2) + b* x[i] + a ;
    }
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
  std::vector<double> scratch;
public:
 
  QuadModel  qm;

  QuadObs( const std::vector<double> &x,
	   const std::vector<double> &obs):
    x(x),
    obs(obs),
    scratch(obs.size())
  {}
  
  unsigned   nres (void)
  {
    return obs.size();
  }

  void  residuals ( std::vector< double > & res )
  {
    qm.eval( x, scratch);
    for(size_t i =0; i<obs.size(); ++i)
      res[i]=obs[i]-scratch[i];
  }
  

  void AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    qm.AddParams(pars);
  }


};

