%module pybnlib
%{

#include "../src/unaryfn.hxx"
#include "../src/unaryfnutils.hxx"
#include "../src/binaryfn.hxx"
#include "../src/tophat.hxx"
#include "../src/quadratic_bfn.hxx"
#include "../src/bnrandom.hxx"
#include "../src/zernikepoly.hxx"
#include "../src/interpolate.hxx"
#include "../src/interpolategsl.hxx"
#include "../src/interpolatelog.hxx"
#include "../src/integrateutils.hxx"
#include "../src/phyconstants.hxx"
#include "../src/phyfunc.hxx"
#include "../src/phycosmo.hxx"
#include "../src/integrate.hxx"
#include "../src/kolmogorov.hxx"
#include "../src/kolmogorov_iters.hxx"
#include "../src/kolmogorov_spec.hxx"
#include "../src/kolmogorov_wrap.hxx"
#include "../src/kolmogorov_3diters.hxx"
#include "../src/kolmogorov_3d.hxx"
#include "../src/kernels_3d.hxx"

%}

%include "carrays.i"
%include "typemaps.i"
%include "std_vector.i"

%array_class( double , doubleArray);

%apply size_t & OUTPUT { size_t &iOUT, size_t &jOUT, size_t &kOUT };

%apply double * OUTPUT { double * OUTalpha, 
			 double *OUTbeta,
			 double *OUTgamma,
			 double *OUTdelta};

namespace std {
   %template(K3DParentV) vector<BNLib::K3DParent>; 
   %template(Displacement3DV) vector<BNLib::Displacement3D>;
   %template(doubleV) vector<double>;
   %template(Position3DV) vector<BNLib::Position3D>;
}

%include "../src/unaryfn.hxx"
%include "../src/unaryfnutils.hxx"
%include "../src/binaryfn.hxx"
%include "../src/tophat.hxx"
%include "../src/quadratic_bfn.hxx"
%include "../src/bnrandom.hxx"
%include "../src/zernikepoly.hxx"
%include "../src/interpolate.hxx"
%include "../src/interpolategsl.hxx"
%include "../src/interpolatelog.hxx"
%include "../src/integrate.hxx"
%include "../src/integrateutils.hxx"
%include "../src/phyconstants.hxx"
%include "../src/phyfunc.hxx"
%include "../src/phycosmo.hxx"
%include "../src/kolmogorov_iters.hxx"
%include "../src/kolmogorov_spec.hxx"
%include "../src/kolmogorov.hxx"
%include "../src/kolmogorov_wrap.hxx"
%include "../src/kolmogorov_3diters.hxx"
%include "../src/kolmogorov_3d.hxx"
%include "../src/kernels_3d.hxx"

%extend BNLib::ConstUDD {
	
	BNLib::UnaryDD *downcast(void) 
	{
	return self;
	}
}

