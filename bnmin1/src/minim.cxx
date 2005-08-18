/* Bojan Nikolic
 * $Id: minim.cxx,v 1.2 2005/08/18 04:57:08 bnikolic Exp $
 */

#include "minim.hxx"

#include <cmath>

#include "monitor.hxx"


namespace Minim {
  
  ModelDesc::ModelDesc( Model &mod ) :
    mod(mod)
  {
    mod.AddParams(pars);
  }

  DParamCtr * ModelDesc::operator[] (std::string name) 
  {
    for ( std::vector<DParamCtr>::iterator i ( pars.begin() ) ;
	  i < pars.end() ;
	  ++i ) 
      if (i->name == name ) return &(*i);
    
    return NULL;
  }



Minimiser::Minimiser (Minim::Minimisable &pm) : 
  ModelDesc(pm),
  iter(0) , m(pm) ,
  MonitorChi_stride(1) , 
  MonitorChi_cno(0),
  mon(NULL)
{
  
}

  void Minim::Minimiser::ResEval       (void ) 
  { 
    
    m.residuals(res); 
    
    if ( MonitorChi_cno % MonitorChi_stride == 0 ) 
      {
	if (mon)
	  mon->Iter(this);
      }
    
    MonitorChi_cno++;
    
  }
  
  void Minimiser::InitRes (void) 
  {
    unsigned nresiduals ( m.nres() );
    
    
    res = std::vector<double> (  nresiduals);
  }
  
  void Minimiser::CollectParams ( Model & m ) 
  { 
    m.AddParams(pars) ; 
    MonitorChi_stride=NParam();
  };


  // Used to communicate with the search routine.
  unsigned Minimiser::NParam(void) const 
  {
    unsigned count(0);
    for (std::vector<DParamCtr>::const_iterator i (pars.begin() ) ; i< pars.end() ; ++i ) 
      if (i->dofit) ++count;
    return count;
  }

  void Minimiser::copytopars(double *x) 
  { 
    unsigned count(0);
    for ( std::vector<DParamCtr>::iterator i ( pars.begin() ) ;
	  i < pars.end();
	  i++ )  
      if (i->dofit) {
	    *(i-> p)  =  x[ count ]; 
	    ++count;
	  }
  }

  void Minimiser::copyfrompars(double *x) 
  { 
    unsigned count(0);
    for ( std::vector<DParamCtr>::iterator i ( pars.begin() ) ;
	  i < pars.end();
	  i++ ) if(i->dofit) {
	    x[ count ]  =  * (i-> p)  ; 
	    ++count;
	  }
  }





  double Minimiser::ChiSquared(void) {
    double total(0.0);
    for (unsigned i (0) ; i < res.size() ; ++i) total += pow(res[i],2);
    return total;
  }



}


