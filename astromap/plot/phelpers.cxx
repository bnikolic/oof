/*
  Bojan Nikolic
  $Id: phelpers.cxx,v 1.1 2005/06/21 14:21:58 bnikolic Exp $
*/

#include "phelpers.hxx"

#include <cpgplot.h>

namespace AstroMap {

  template<class C> void  TSetCT ( C &l , C & r , C &g , C &b, 
				  double contrast, double brightnes)
  {

    /* Convert to simple float arrays */
    float fl[l.size()];
    float fr[l.size()];
    float fg[l.size()];
    float fb[l.size()];

    for (unsigned i = 0 ; i < l.size() ; ++i) fl[i]=l[i];
    for (unsigned i = 0 ; i < r.size() ; ++i) fr[i]=r[i];
    for (unsigned i = 0 ; i < g.size() ; ++i) fg[i]=g[i];
    for (unsigned i = 0 ; i < b.size() ; ++i) fb[i]=b[i];

    /* And send off to pgplot */
    cpgctab(fl,fr,fg,fb,l.size(), contrast, brightnes);
    

  }

  void SetColourTable (std::vector<double> &l ,
		       std::vector<double> &r, 
		       std::vector<double> &g ,
		       std::vector<double> &b, 
		       double contrast, double brightnes )
  {

    TSetCT ( l , r, g, b, contrast, brightnes) ;

  }
  
  void SetPrintCT (double locut , double hicut)
  {

    // Avoid full black and full white as these do not reproduce
    const double cmin = 0.35;
    const double cmax = 0.9;

    std::vector<double> lum (4);
    lum[0] = 0;     lum[1] = locut;     lum[2] = hicut;     lum[4] = 1;

    std::vector<double> cval (4);
    cval[0] = cmax;     cval[1] = cmax;     cval[2] = cmin;     cval[4] = cmin;

    SetColourTable( lum, cval, cval , cval, 1, 0.5);
    

  }

}


