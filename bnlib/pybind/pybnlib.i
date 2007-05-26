%module pybnlib
%{

#include "../src/unaryfn.hxx"
#include "../src/unaryfnutils.hxx"
#include "../src/binaryfn.hxx"
#include "../src/tophat.hxx"
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
#include "../src/kolmogorov_wrap.hxx"

%}

%include "carrays.i"
%include "typemaps.i"

%array_class( double , doubleArray);

%apply size_t & OUTPUT { size_t &iOUT, size_t &jOUT };

%include "../src/unaryfn.hxx"
%include "../src/unaryfnutils.hxx"
%include "../src/binaryfn.hxx"
%include "../src/tophat.hxx"
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
%include "../src/kolmogorov_wrap.hxx"

%extend BNLib::ConstUDD {
	
	BNLib::UnaryDD *downcast(void) 
	{
	return self;
	}
}

