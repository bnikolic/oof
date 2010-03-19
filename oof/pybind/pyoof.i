%module pyoof  
%{

#include <minimmodel.hxx>
#include <astromap.hxx>
#include <fft.hxx>
#include "coordsys.hxx"

#include "../src/oof_main.hxx"

#include "../src/telgeo/telgeo.hxx"
#include "../src/telgeo/gbtgeo.hxx"
#include "../src/telgeo/primefoc.hxx"
#include "../src/telgeo/telswitch.hxx"

#include "../src/aperture/phasemod.hxx"
#include "../src/aperture/zernmodel.hxx"
#include "../src/aperture/aperturemod.hxx"
#include "../src/aperture/multi_apmod.cxx"

#include "../src/aperture/amplimod.hxx"
#include "../src/aperture/gaussampmod.hxx"
#include "../src/aperture/tophatmodel.hxx"
#include "../src/aperture/sqgaussmod.hxx"

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
%import "astromap.hxx"
%import "coordsys.hxx"


%include "../src/oof_main.hxx"
%include "../src/telgeo/telgeo.hxx"
%include "../src/telgeo/gbtgeo.hxx"
%include "../src/telgeo/primefoc.hxx"
%include "../src/telgeo/telswitch.hxx"

%include "../src/aperture/phasemod.hxx"
%include "../src/aperture/zernmodel.hxx"
%include "../src/aperture/aperturemod.hxx"
%include "../src/aperture/multi_apmod.cxx"

%include "../src/aperture/amplimod.hxx"
%include "../src/aperture/gaussampmod.hxx"
%include "../src/aperture/tophatmodel.hxx"
%include "../src/aperture/sqgaussmod.hxx"

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

%extend AstroMap::Map {

    double min() {
	return (*self).min();
	}

    double max() {
	return (*self).max();
	}

    double sum() {
	return (*self).sum();
	}

     void mult ( Map const & m ) {
	(*self) *= m;
     }

     void mult ( double m ) {
	(*self) *= m;
     }

     void add ( Map const & m ) {
	(*self) += m;
     }

     void add ( double x ) {
	(*self) += x;
     }

     void copy( Map const & m ) {
	(*self) = m ;
     }

    double getv  ( unsigned x, unsigned y) {
	return 	self->get(x,y);
     } 

     void set  ( unsigned x, unsigned y, double val) {
	self->get(x,y)=val;
     }
	

}
