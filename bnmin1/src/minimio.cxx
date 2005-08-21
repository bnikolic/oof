/*
  Bojan Nikolic
  $Id: minimio.cxx,v 1.1 2005/08/21 02:42:03 bnikolic Exp $
*/

#include "minimio.hxx"

#include "paramctr.hxx"
#include "minim.hxx"

#include <iostream>

#include <boost/lambda/lambda.hpp>

namespace Minim {

  
  /*! This is the crazy way to do this from previous version of
   *  software */
  template <class T>    inline 
  std::ostream & operator<< ( std::ostream & o , ParamCtr<T> const &p ) 
  {
    o<<p.name<<"=\t"<<*p.p<<"\t";
    
    if (p.dofit)
      {
	o<<"(fitting)     ";
      }
    else
      { 
	o<<"(not fitting) ";
      }
    
    o<<"\\\\ "<<p.comment<<std::endl; 
    return o;
  }

  void PrettyPrint( ModelDesc &mod)
  {
    using namespace boost::lambda;

    for_each(mod.pars.begin() , mod.pars.end() , std::cout <<_1 );
    
  }

}


