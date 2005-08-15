/*
  Bojan Nikolic
  $Id: obscompare.hxx,v 1.2 2005/08/15 14:11:39 bnikolic Exp $

  Compare models to observations!
*/

#ifndef __OOF_OBSCOMPARE_HXX__
#define __OOF_OBSCOMPARE_HXX__

#include <minimmodel.hxx>

namespace OOF {

  class ObsCompare : public Minim::Minimisable {


  public:
    
    // ------- Constructors / Destructors    -----------


    // ------- Member functions -----------------------


    // ------- Methods inherited from minimisable

    virtual void  residuals ( std::vector< double > & res ) ;
    virtual unsigned   nres (void)   ; 
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars ) ;



  };

  


}

#endif
