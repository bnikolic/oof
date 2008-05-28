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


#include "../test/quadmodel.hpp"


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

	   %template(ListDV) list<vector<double> >; 
}

%include "../src/bnmin_main.hxx"
%include "../src/minimmodel.hxx"
%include "../src/monitor.hxx"
%include "../src/minim.hxx"
%include "../src/minimio.hxx"
%include "../src/lmmin.hxx"
%include "../src/lmminutils.hxx"
%include "../src/metropolis.hxx"

%include "../test/quadmodel.hpp"

