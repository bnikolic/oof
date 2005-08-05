%module pybnmin1 
%{

#include "../src/paramctr.hxx"
#include "../src/minimmodel.hxx"
#include "../src/minim.hxx"
#include "../src/lmmin.hxx"


%}

%include "std_string.i"

%include "../src/paramctr.hxx"

namespace Minim {
   %template(DParamCtr) ParamCtr<double> ; 
} 

%include "../src/minimmodel.hxx"
%include "../src/minim.hxx"
%include "../src/lmmin.hxx"


