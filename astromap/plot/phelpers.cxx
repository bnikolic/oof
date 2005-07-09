/*
  Bojan Nikolic
  $Id: phelpers.cxx,v 1.3 2005/07/09 12:59:09 bnikolic Exp $
*/

#include "phelpers.hxx"

#include <cpgplot.h>
#include <iostream>
#include <fstream>
#include <linraster.hxx>


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

  #define bnstringer1(x) #x
  #define bnstringer2(x) bnstringer1(x)

  std::string ColourTFName( const char * name)
  {
    std::string shareprefix( bnstringer2(CMAPDATADIR) );
    std::string sname(name);
    std::string fname;

    if ( sname == "heat")
      fname = "heat.lasc";
    else
      fname = name;

    return shareprefix+"/ASTROMAPPLOT/" + fname;

  }

  void ParseCTFile(const char *fname , 
		   std::vector<double> &r,
		   std::vector<double> &g,
		   std::vector<double> &b)
  {

    std::ifstream  ifile (fname);

    ifile.setf(std::ios::skipws);
    
    double x;
    unsigned i =0;

    while ( ! ifile.eof() ) 
      {
	ifile>>x;
	r.push_back(x);
	ifile>>x;
	g.push_back(x);
	ifile>>x;
	b.push_back(x);
	
	++i;
	if ( i > 1000 ) break;
      }
  }

  void  SetFileColourTab (const char * name, double locut , double hicut)
  {

    std::string fname ( ColourTFName(name));
    
    std::vector<double> r;
    std::vector<double> g;
    std::vector<double> b;

    ParseCTFile( fname.c_str() , r, g, b);

    std::vector<double> l (r.size() );
    BNLib::LinRaster( l.begin(),
		      l.end(),
		      locut,
		      hicut);
    
    SetColourTable( l , r, g, b, 
		    1, 0.5);
    

  }

}


