/// Bojan Nikolic <bojan@bnikolic.co.uk>

#include "../src/minimmodel.hxx"
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
	      std::vector<double> & res) const
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
  {}
  
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


};

