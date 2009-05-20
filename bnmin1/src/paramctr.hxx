/**
   \file paramctr.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk>

   Control of parameters
*/

#ifndef _BNMIN_PARAMCTR_HXX__
#define _BNMIN_PARAMCTR_HXX__

#include <string>

#include "bnmin_main.hxx"

namespace Minim {

  /** A class to describe a model parameter
   */
  template<class T>
  class ParamCtr
  {
  public:
    /// Pointer to the actual value being controlled
    T * p;

    /// A name for this parameter
    std::string name;

    /// If false the parametar is excluded from fitting
    bool dofit;

    /// A comment explaining what the parametar does
    std::string comment;

    ParamCtr(T* pp,
	     const std::string &pname,
	     bool pdofit, 
	     const std::string &pcomment): 
      p(pp),
      name(pname),
      dofit(pdofit),
      comment(pcomment)
    {
    }
    
    /** Default constructor for interoperation with stl containers
     */
    ParamCtr(void):
      p(NULL),
      name(""),
      dofit(false),
      comment("")
    {
    }

    T  getp(void) 
    {
      return *p;
    }

    void setp(T pp)
    { 
      *p = pp;
    }

    /// Returns the name as a c-type string
    const char * getname(void)
    { 
      return name.c_str(); 
    }

    /*! Returns the comment as a c-type string */
    const char * getcomment(void) 
    { 
      return comment.c_str(); 
    }
  };

  /// A floating point double parameter
  typedef ParamCtr<double>  DParamCtr;

  class ParamError:
    public BaseErr
  {
  public:
    /// Use only if could not establish the parameter
    ParamError(const std::string &msg):
      BaseErr("Parameter not identified: " +msg)
    {}

    ParamError(const DParamCtr&p,
	       const std::string &msg):
      BaseErr(p.name+msg)
    {}
    
    virtual ~ParamError() throw()
    {}

  };
  


}

#endif // _BNMIN_PARAMCTR_HXX__
