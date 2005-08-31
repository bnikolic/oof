%module pybnlib
%{

#include "../src/unaryfn.hxx"
#include "../src/binaryfn.hxx"
#include "../src/tophat.hxx"
#include "../src/zernikepoly.hxx"
#include "../src/interpolate.hxx"
#include "../src/interpolategsl.hxx"
#include "../src/interpolatelog.hxx"

%}

%include "carrays.i"

%array_class( double , doubleArray);

%include "../src/unaryfn.hxx"
%include "../src/binaryfn.hxx"
%include "../src/tophat.hxx"
%include "../src/zernikepoly.hxx"
%include "../src/interpolate.hxx"
%include "../src/interpolategsl.hxx"
%include "../src/interpolatelog.hxx"
