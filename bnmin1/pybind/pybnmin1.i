%module pybnmin1 

 // This define is required to work around symbol name clashes when
 // loading
 // multiple modules -- see for example:
 // http://sourceforge.net/tracker/?func=detail&atid=101645&aid=1863647&group_id=1645
#define PySwigIterator bnmin1_PySwigIterator

%{
#include "../src/bnmin_main.hxx"
#include "../src/paramctr.hxx"
#include "../src/minimmodel.hxx"
#include "../src/monitor.hxx"
#include "../src/minim.hxx"
#include "../src/minimio.hxx"
#include "../src/lmmin.hxx"
#include "../src/lmminutils.hxx"
#include "../src/mcpoint.hxx"
#include "../src/metropolis.hxx"
#include "../src/priors.hxx"
#include "../src/twoerrline.hxx"

#include "../src/nestederr.hxx"
#include "../src/nestedsampler.hxx"
#include "../src/prior_sampler.hxx"
#include "../src/nestedinitial.hxx"
#include "../src/apps/gaussmodel.hxx"
#include "../src/apps/bayesline.hxx"

%}

%feature("autodoc", "1");

%include "std_string.i"
%include "std_vector.i"
%include "std_list.i"
%include "std_set.i"

%include "../src/bnmin_main.hxx"
%include "../src/paramctr.hxx"

namespace Minim {
   %template(DParamCtr) ParamCtr<double> ; 
} 

namespace std {
	   %template(DoubleVector) vector<double>; 

	   %template(ListDV) list<Minim::MCPoint>; 
	   %template(ListWP) list<Minim::WPPoint>; 

	   %template(SetMC) set<Minim::MCPoint>; 
}


%include "../src/minimmodel.hxx"
%include "../src/monitor.hxx"
%include "../src/minim.hxx"
%include "../src/minimio.hxx"
%include "../src/lmmin.hxx"
%include "../src/lmminutils.hxx"
%include "../src/mcpoint.hxx"
%include "../src/metropolis.hxx"
%include "../src/priors.hxx"
%include "../src/twoerrline.hxx"
%include "../src/nestederr.hxx"

%catches(Minim::NestedSmallStart) Minim::NestedS::NestedS(PriorNLikelihood &,
			        	 	 const std::list<MCPoint> &,
					         const std::vector<double> &,
			                         unsigned seed=43);		    
%include "../src/nestedsampler.hxx"

%include "../src/prior_sampler.hxx"
%include "../src/nestedinitial.hxx"

namespace boost { namespace numeric{ namespace ublas {}}};

%include "../src/apps/gaussmodel.hxx"
%include "../src/apps/bayesline.hxx"

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


