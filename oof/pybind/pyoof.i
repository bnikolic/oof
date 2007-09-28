%module pyoof  
%{

#include <minimmodel.hxx>
#include <astromap.hxx>
#include <fft.hxx>
#include "coordsys.hxx"

#include "../src/telgeo/telgeo.hxx"
#include "../src/telgeo/gbtgeo.hxx"
#include "../src/telgeo/primefoc.hxx"
#include "../src/telgeo/telswitch.hxx"

#include "../src/aperture/phasemod.hxx"
#include "../src/aperture/zernmodel.hxx"
#include "../src/aperture/aperturemod.hxx"

#include "../src/aperture/amplimod.hxx"
#include "../src/aperture/gaussampmod.hxx"

#include "../src/aperture/mkapertures.hxx"

#include "../src/farfield/farffunctions.hxx"
#include "../src/farfield/farf.hxx"
#include "../src/farfield/choppedff.hxx"

#include "../src/maptoresidual.hxx"
#include "../src/maptoresidual_ds.hxx"
#include "../src/obsphasescreen.hxx"
#include "../src/obsdefocus.hxx"
#include "../src/obscompare.hxx"
#include "../src/obsfilefns.hxx"


%}
  
%include "minimmodel.hxx"
%include <fft.hxx>
%include "astromap.hxx"
%include "coordsys.hxx"


%include "../src/telgeo/telgeo.hxx"
%include "../src/telgeo/gbtgeo.hxx"
%include "../src/telgeo/primefoc.hxx"
%include "../src/telgeo/telswitch.hxx"

%include "../src/aperture/phasemod.hxx"
%include "../src/aperture/zernmodel.hxx"
%include "../src/aperture/aperturemod.hxx"

%include "../src/aperture/amplimod.hxx"
%include "../src/aperture/gaussampmod.hxx"

%include "../src/aperture/mkapertures.hxx"

%include "../src/farfield/farffunctions.hxx"
%include "../src/farfield/farf.hxx"
%include "../src/farfield/choppedff.hxx"

%include "../src/maptoresidual.hxx"
%include "../src/maptoresidual_ds.hxx"
%include "../src/obsphasescreen.hxx"
%include "../src/obsdefocus.hxx"
%include "../src/obscompare.hxx"
%include "../src/obsfilefns.hxx"


%extend OOF::ObsCompare {
	
	Minim::Minimisable *downcast(void) 
	{
	return self;
	}
}

%extend OOF::RZernModel {
	
	Minim::Model *downcast(void) 
	{
	return self;
	}
}
%extend AstroMap::CoordSys {

  double  x_pxtoworld(double px , double py ) {
	double wx; double wy;
	(*self).pxtoworld(px, py , wx , wy);
	return wx;
	}

  double  y_pxtoworld(double px , double py ) {
	double wx; double wy;
	(*self).pxtoworld(px, py , wx , wy);
	return wy;
	}

  double  x_worldtopx(double wx, double wy ) {
	double px ; double py;
	(*self).worldtopx( wx , wy, px, py );
	return px;
	}

  double  y_worldtopx(double wx, double wy ) {
	double px ; double py;
	(*self).worldtopx( wx , wy, px, py );
	return py;
	}


}
