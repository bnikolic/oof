/**
   \file mapregions.cxx

   Bojan Nikolic

*/

#include "mapregions.hxx"

#include "astromap.hxx"


namespace AstroMap {

  MRRect::MRRect(size_t lx,
		 size_t ly,
		 size_t hx,
		 size_t hy):
    lx(lx),
    ly(ly),
    hx(hx),
    hy(hy)
  {
  }

  double Sum(const Map &m,
	     const MRRect &reg)
  {
    double res=0;
    for (size_t i=reg.lx; i<reg.hx; ++i)
      for (size_t j=reg.ly; j<reg.hy; ++j)
      {
	res+= m.get(i,j);
      }
    return res;
  }

  Map * Extract(const Map &m,
		const MRRect &reg)
  {
    Map *mres=new Map(reg.hx-reg.lx,
		      reg.hy-reg.ly);
    for (size_t i=reg.lx; i<reg.hx; ++i)
      for (size_t j=reg.ly; j<reg.hy; ++j)
      {
	mres->get(i-reg.lx, j-reg.ly) = m.get(i,j);
      }
    
    return mres;
  }

}



