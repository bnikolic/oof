%module pyoof
%{

#include <minimmodel.hxx>
#include <astromap.hxx>

#include "../src/telgeo/telgeo.hxx"
#include "../src/telgeo/telswitch.hxx"

#include "../src/aperture/phasemod.hxx"
#include "../src/aperture/zernmodel.hxx"
#include "../src/aperture/aperturemod.hxx"

#include "../src/aperture/amplimod.hxx"
#include "../src/aperture/gaussampmod.hxx"

%}
  
%include "minimmodel.hxx"
#include "astromap.hxx"


%include "../src/telgeo/telgeo.hxx"
%include "../src/telgeo/telswitch.hxx"

%include "../src/aperture/phasemod.hxx"
%include "../src/aperture/zernmodel.hxx"
%include "../src/aperture/aperturemod.hxx"

%include "../src/aperture/amplimod.hxx"
%include "../src/aperture/gaussampmod.hxx"
