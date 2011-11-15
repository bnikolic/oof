/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2003

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file lmmin.cxx

*/

#include "../config.h"

#include <memory.h>
#include "lmmin.hxx"
#include <boost/assert.hpp>
#include <iostream>

#include "/home/bnikolic/p/inmin-test/include/inmin_lm.h"

  extern "C" void inmin_fres_helper (const double *x,
				     double *res,
				     void   *data)
  {
    Minim::Minimisable *mm=static_cast<Minim::Minimisable*>(data);
    Minim::ModelDesc md(*mm);
    md.copytopars(x);
    std::vector<double> vres(mm->nres());
    mm->residuals(vres);
    for(size_t i=0; i<vres.size(); ++i)
    {
      res[i]=vres[i];
    }
  }

extern "C" void * inmin_minimisable_copy (void *d)
{
  Minim::Minimisable *mm=static_cast<Minim::Minimisable*>(d);
  return (void *)mm->clone();
}

extern "C" void  inmin_minimisable_del (void *d)
{
  Minim::Minimisable *mm=static_cast<Minim::Minimisable*>(d);
  delete(mm);
}

void simple_stdout_trace(size_t level,
			 const char *msg,
			 void *state)
{
  std::cout<<level<<": "<<msg<<std::endl;
}





#include "pda.hxx"



namespace Minim {

  static Minim::LMMin* LMMin_this;
  static int LMMin_lock (0);

  extern "C" void LMMin_helper (int *m,
				int *n,
				double *x,
				double *fvec,
				int *iflag)
  {
    LMMin_this->copytopars(x);
    LMMin_this->ResEval();
    LMMin_this->copyres(fvec);
  }
  
  
  LMMin::LMMin( Minimisable &pm ): 
    Minimiser(pm),
    mm(pm),
    ftol(1e-3), 
    xtol(1e-3),
    gtol(1e-3),
    maxfev(1000),
    epsfcn(0.0),
    fjac(NParam() * NRes()),
    ldfjac(NRes()),
    ipvt(NParam())
  {   
    MonitorChi_stride=NParam();
  }
  
  
  void LMMin::solve(void)
  {
    
    if ( LMMin_lock ) 
      {
	return;
      }
    else 
      {
	LMMin_lock  =1;
      }
    
    
    
    // this is needed to communicate with the 
    LMMin_this = this; 
    
    InitRes();
    
    int n= NParam(); 
    int m= NRes();
    
    std::vector< double >   x0(  n ); 
    copyfrompars(&x0[0]);
    
    std::vector< double>    fvec( m );
    
    fjac.resize( n * m);
    ldfjac = m;
    ipvt.resize(n);
    
    
    std::vector< double>    diag( n);
    int mode =1;
    double factor = 100.0;
    int nprint = 0;
    int info=0;
    int nfev=0;
    
    std::vector<double> qtf ( n);
    
    std::vector<double> wa1( n) , wa2( n), wa3( n) , wa4( m);
    
#ifndef BNMIN1_NO_PDA
    
    pda_lmdif__( LMMin_helper,
		 &m,
		 &n,
		 &x0[0],
		 &fvec[0],
		 &ftol, &xtol , &gtol , &maxfev, &epsfcn,
		 &diag[0],
		 &mode ,
		 &factor,
		 &nprint, 
		 &info,
		 &nfev,
		 &fjac[0],
		 &ldfjac,
		 &ipvt[0],
		 &qtf[0],
		 &wa1[0],&wa2[0],&wa3[0],&wa4[0]
		 );
#else
    throw "No PDA algorithms so don't know how to do Lavenberg-Marquarndt";
#endif
    
    LMMin_lock  =0;
  }


  void LMMin::solve_mt(void)
  {
    InitRes();

    inmin_lm_in in;
    memset(&in, 0, sizeof(inmin_lm_in));
    in.N=NParam();
    in.M=NRes();
    in.f=inmin_fres_helper;
    in.ftol=ftol;
    in.xtol=xtol;
    in.gtol=gtol;
    in.maxfev=10000;
    in.box=NULL;

    in.parll.doparallel=0;
    in.parll.f_copy=inmin_minimisable_copy;
    in.parll.f_del=inmin_minimisable_del;

    in.mon.trace_f=simple_stdout_trace;
    in.mon.trace_l=9;

    BOOST_ASSERT(in.M>=in.N);

    std::vector<double> res(in.N);
    inmin_lm_out out;
    out.x=&res[0];
    out.covar=NULL;

    std::vector<double>  pinit(in.N); 
    copyfrompars(&pinit[0]);
    
    inmin_lm_run_eigen(&in,
			&pinit[0],
			&out,
			(void *)&mm);
    copytopars(&res[0]);
  }
  
  
}
