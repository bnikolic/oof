/* Bojan Nikolic
 * $Id: minim.cxx,v 1.1 2005/06/02 13:43:18 bnikolic Exp $
 */

#include "minim.hxx"

#include <cmath>


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

}

Minim::Minimiser::Minimiser (Minim::Minimisable &pm) : 
  ModelDesc(pm),
  iter(0) , m(pm) ,
  MonitorChi(false) , MonitorChi_stride(1) , MonitorChi_cno(0),
  MonitorPars(false), TotallyQuiet(false)
{
  
}

void Minim::Minimiser::ResEval       (void ) 
{ 
  m.residuals(res); 
  if (MonitorChi && ( ! TotallyQuiet ) ) {
    if ( MonitorChi_cno % MonitorChi_stride == 0 ) {
    }
    MonitorChi_cno++;
  }
}

void Minim::Minimiser::InitRes (void) 
{
  unsigned nresiduals ( m.nres() );


  res = std::vector<double> (  nresiduals);
}

void Minim::Minimiser::CollectParams ( Model & m ) 
{ 
  m.AddParams(pars) ; 
};


// Used to communicate with the search routine.
unsigned Minim::Minimiser::NParam(void) const {
  unsigned count(0);
  for (std::vector<DParamCtr>::const_iterator i (pars.begin() ) ; i< pars.end() ; ++i ) 
    if (i->dofit) ++count;
  return count;
}

void Minim::Minimiser::copytopars(double *x) 
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

void Minim::Minimiser::copyfrompars(double *x) 
{ 
  unsigned count(0);
  for ( std::vector<DParamCtr>::iterator i ( pars.begin() ) ;
	i < pars.end();
	i++ ) if(i->dofit) {
	  x[ count ]  =  * (i-> p)  ; 
	  ++count;
	}
}





double Minim::Minimiser::ChiSquared(void) {
  double total(0.0);
  for (unsigned i (0) ; i < res.size() ; ++i) total += pow(res[i],2);
  return total;
}


void Minim::Minimiser::Monitor(bool t) {

  if (t) {
    MonitorChi = true;
    MonitorChi_cno = 0;
    MonitorChi_stride=NParam();
  } else {
    MonitorChi = false;
  }

}
