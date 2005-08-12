/*
  Bojan Nikolic
  $Id: obscompare.hxx,v 1.1 2005/08/12 19:32:16 bnikolic Exp $

  Compare models to observations!
*/

#ifndef __OOF_OBSCOMPARE_HXX__
#define __OOF_OBSCOMPARE_HXX__

#include <minimmodel.hxx>

namespace OOF {

  class ObsCompare : public Minim::Minimisable {


  public:
    
    // ------- Construcotrs / Destructors    -----------


    // ------- Member functions -----------------------


    // ------- Methods inherited from minimisable

    virtual void  residuals ( std::vector< double > & res ) 0;
    virtual unsigned   nres (void)   ; 
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars ) ;



  };

  


}

#endif
