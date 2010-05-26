/** 
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version 2010

   This file is part of the OOF package and licensed under GNU General
   Public License version 2
   
   \file directcompare.cxx

*/

#include "directcompare.hxx"
#include "maptoresidual.hxx"

#include <fitting_basic.hxx>

namespace OOF {

  FFCompare::FFCompare(AstroMap::ModelMap *m,
		       MapToResidual *o,
		       const AstroMap::Map &msample):
    m(m),
    o(o),
    mtemp(msample)
  {
  }

  FFCompare::~FFCompare()
  {
  }

  unsigned FFCompare::nres(void) const
  {
    return o->nres();
  }

  void FFCompare::residuals(std::vector<double> &res) const
  {
    res.resize(nres());
    m->eval(mtemp);
    o->residuals(mtemp,
		 res.begin());
  }
  
  void FFCompare::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    m->AddParams(pars);
  }


}


