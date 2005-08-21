%module pybnmin1 
%{

#include "../src/paramctr.hxx"
#include "../src/minimmodel.hxx"
#include "../src/monitor.hxx"
#include "../src/minim.hxx"
#include "../src/minimio.hxx"
#include "../src/lmmin.hxx"
#include "../src/lmminutils.hxx"


%}

%include "std_string.i"
%include "std_vector.i"

%include "../src/paramctr.hxx"

namespace Minim {
   %template(DParamCtr) ParamCtr<double> ; 
} 

namespace std {
	   %template(DoubleVector) vector<double>; 
}

%include "../src/minimmodel.hxx"
%include "../src/monitor.hxx"
%include "../src/minim.hxx"
%include "../src/minimio.hxx"
%include "../src/lmmin.hxx"
%include "../src/lmminutils.hxx"

