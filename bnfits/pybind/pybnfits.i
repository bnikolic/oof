%module pybnfits
%{
#include "../src/fitserr.hxx"
#include "../src/fitswrap.hxx"
#include "../src/fitsops.hxx"


%}

%include "std_vector.i"


namespace std {
   %template(LongVector) vector<long>; 
}

%include "../src/fitserr.hxx"
%include "../src/fitswrap.hxx"
%include "../src/fitsops.hxx"
 

