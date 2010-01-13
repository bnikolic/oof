/**
   \file pda.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>
   
   Interface definition to the PDA routines
*/

#define F77FUNC( name ) name ## __

extern "C" {

void F77FUNC(pda_lmdif) ( void (*fcn)(int *m, int *n , double *x, double *fvec, int * iflag),
			  int *m,
			  int *n,
			  double *x,
			  double *fvec,
			  double *ftol,
			  double *xtol,
			  double *gtol,
			  int * maxfev,
			  double *epsfcn,
			  double *diag,
			  int * mode,
			  double *factor,
			  int *nprint,
			  int *info,
			  int *nfev,
			  double *fjac,
			  int *ldfjac,
			  int *ipvt,
			  double *qtf,
			  double *wa1, double *wa2, double *wa3,
			  double *wa4);

  double F77FUNC(pda_d1mach) (int *i);

}
