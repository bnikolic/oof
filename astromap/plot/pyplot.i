%module pyplot
%{

#include "../src/astromap.hxx"
#include "../src/mapops.hxx"
#include "../src/pixextract.hxx"
#include "../src/fft.hxx"

#include "../src/coordsys/coordsys.hxx"
#include "../src/coordsys/lincordsys.hxx"
#include "../src/coordsys/csops.hxx"

#include "../src/dataser/datapoint.hxx"
#include "../src/dataser/dataseries.hxx"
#include "../src/dataser/dsfileops.hxx"



#include "plot.hxx"
#include "phelpers.hxx"

#include <cpgplot.h>

%}

%include "typemaps.i"

%include "../src/astromap.hxx"
%include "../src/mapops.hxx"
%include "../src/pixextract.hxx"
%include "../src/fft.hxx"

%include "../src/coordsys/coordsys.hxx"
%include "../src/coordsys/lincordsys.hxx"
%include "../src/coordsys/csops.hxx"

%include "../src/dataser/datapoint.hxx"
%include "../src/dataser/dataseries.hxx"
%include "../src/dataser/dsfileops.hxx"


%include "plot.hxx"
%include "phelpers.hxx"

%extend AstroMap::Map {

    double min() {
	return (*self).min();
	}

}


void cpgldev(void);
int cpgbeg(int unit, const char *file, int nxsub, int nysub);
void cpgsci(int ci);
void cpgscir(int icilo, int icihi);
void cpgctab(const float *l, const float *r, const float *g, const float *b, int nc, float contra, float bright);
void cpgend(void);
void cpgmove(float x, float y);
void cpgdraw(float x, float y);
void cpgpt(int n, const float *xpts, const float *ypts, int symbol);
void cpgpt1(float xpt, float ypt, int symbol);
void cpglab(const char *xlbl, const char *ylbl, const char *toplbl);
void cpgenv(float xmin, float xmax, float ymin, float ymax, int just, int axis);
void cpgclos(void);
void cpgsls(int ls);
void cpgsitf(int itf);

// Frame drawing etc
void cpgsvp(float xleft, float xright, float ybot, float ytop);
void cpgswin(float x1, float x2, float y1, float y2);
void cpgbox(const char *xopt, float xtick, int nxsub, const char *yopt, float ytick, int nysub);
void cpgtbox(const char *xopt, float xtick, int nxsub, const char *yopt, float ytick, int nysub);

void cpgeras(void);
void cpgpage(void);
void cpgpanl(int nxc, int nyc);

void cpgpap(float width, float aspect);
void cpgsch(float size);

// annonation
void cpgarro(float x1, float y1, float x2, float y2);
void cpgptxt(float x, float y, float angle, float fjust, const char *text);
void cpgwedg(const char *side, float disp, float width, float fg, float bg, const char *label);

// Histograms
void cpghist(int n, const float *data, float datmin, float datmax, int nbin, int pgflag);

// more drawing
void cpgpoly(int n, const float *xpts, const float *ypts);
void cpgshs(float angle, float sepn, float phase); 
void cpgsfs(int fs);
void cpgslw(int lw); // set line width
void cpgqlw(int *OUTPUT);//query line width
void cpgqwin(float *OUTPUT, float *OUTPUT, float *OUTPUT, float *OUTPUT);


void cpgcirc(float xcent, float ycent, float radius);


