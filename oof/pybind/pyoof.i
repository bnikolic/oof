%module pyoof
%{

#include <minimmodel.hxx>
#include <astromap.hxx>
#include <fft.hxx>

#include "../src/telgeo/telgeo.hxx"
#include "../src/telgeo/telswitch.hxx"

#include "../src/aperture/phasemod.hxx"
#include "../src/aperture/zernmodel.hxx"
#include "../src/aperture/aperturemod.hxx"

#include "../src/aperture/amplimod.hxx"
#include "../src/aperture/gaussampmod.hxx"

#include "../src/aperture/mkapertures.hxx"

#include "../src/farfield/farffunctions.hxx"
#include "../src/farfield/farf.hxx"

#include "../src/maptoresidual.hxx"
#include "../src/maptoresidual_ds.hxx"
#include "../src/obsphasescreen.hxx"
#include "../src/obscompare.hxx"


%}
  
%include "minimmodel.hxx"
%include <fft.hxx>
#include "astromap.hxx"


%include "../src/telgeo/telgeo.hxx"
%include "../src/telgeo/telswitch.hxx"

%include "../src/aperture/phasemod.hxx"
%include "../src/aperture/zernmodel.hxx"
%include "../src/aperture/aperturemod.hxx"

%include "../src/aperture/amplimod.hxx"
%include "../src/aperture/gaussampmod.hxx"

%include "../src/aperture/mkapertures.hxx"

%include "../src/farfield/farffunctions.hxx"
%include "../src/farfield/farf.hxx"

%include "../src/maptoresidual.hxx"
%include "../src/maptoresidual_ds.hxx"
%include "../src/obsphasescreen.hxx"
%include "../src/obscompare.hxx"
