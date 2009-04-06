%module pybnmin1 
%{
#include "../src/bnmin_main.hxx"
#include "../src/paramctr.hxx"
#include "../src/minimmodel.hxx"
#include "../src/monitor.hxx"
#include "../src/minim.hxx"
#include "../src/minimio.hxx"
#include "../src/lmmin.hxx"
#include "../src/lmminutils.hxx"
#include "../src/metropolis.hxx"
#include "../src/priors.hxx"
#include "../src/twoerrline.hxx"



%}

%include "std_string.i"
%include "std_vector.i"
%include "std_list.i"

%include "../src/paramctr.hxx"

namespace Minim {
   %template(DParamCtr) ParamCtr<double> ; 
} 

namespace std {
	   %template(DoubleVector) vector<double>; 

	   %template(ListDV) list<Minim::MCPoint>; 
}

%include "../src/bnmin_main.hxx"
%include "../src/minimmodel.hxx"
%include "../src/monitor.hxx"
%include "../src/minim.hxx"
%include "../src/minimio.hxx"
%include "../src/lmmin.hxx"
%include "../src/lmminutils.hxx"
%include "../src/metropolis.hxx"
%include "../src/priors.hxx"
%include "../src/twoerrline.hxx"

%extend Minim::LineFit {
	
	double get_a_var(void) 
	{
	return self->cv[0];
	}

	double get_b_var(void) 
	{
	return self->cv[3];
	}

	double get_ab(void) 
	{
	return self->cv[1];
	}
}



