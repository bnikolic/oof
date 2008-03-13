/**
   \file paramctr.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk>

   Control of parameters
*/

#ifndef _BNMIN_PARAMCTR_HXX__
#define _BNMIN_PARAMCTR_HXX__

#include <string>

namespace Minim {

  template <class T>  class ParamCtr {
  public:
    /// Pointer to the actuall value being controlled
    T * p;
    /// A name for this parameter
    std::string name;
    /// If false the parametar is excluded from fitting
    bool dofit;
    /// A comment explaining what the parametar does
    std::string comment;

    ParamCtr( T* pp , std::string pname , bool pdofit , std::string pcomment): 
      p(pp) , name(pname) , dofit(pdofit) , comment(pcomment) {};
    
    /// if we want vectors of these, best to have an default
    /// contructors. 
    ParamCtr(void) : p(NULL), name(""), dofit(false) , comment("") {};

    T  getp (void) { return *p; };
    void setp (T pp ) { *p = pp ; };

    /// Returns the name as a c-type string
    const char * getname(void) { return name.c_str() ; }

    /*! Returns the comment as a c-type string */
    const char * getcomment(void) { 
      return comment.c_str() ; 
    }



  };

  typedef ParamCtr<double>  DParamCtr;


}

#endif // _BNMIN_PARAMCTR_HXX__
