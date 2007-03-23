/*
  Bojan Nikolic
  
  Some simple usefuly unary functions 
*/
#ifndef _BNLIB_UNARYFNUTILS_HXX__
#define _BNLIB_UNARYFNUTILS_HXX__

#include "unaryfn.hxx"


namespace BNLib {

  /*! Just returns a constant */
  class ConstUDD : public UnaryDD {

    double c;

  public : 
    
    ConstUDD( double c);
    
    virtual double operator() (double x) ;

  };

  template<class opfn> class PairUDD : public UnaryDD {
    
    UnaryDD * fn1;
    UnaryDD * fn2;

    bool thisown;

  public:

    // --------- Constructor / Desctructor -----------------------
    PairUDD( UnaryDD * fn1, 
	     UnaryDD * fn2,
	     bool thisown):
      fn1(fn1),
      fn2(fn2),
      thisown(thisown)
    {
    }
      ;

    virtual ~PairUDD()
    {
      if ( thisown )
	{
	  if (fn1)
	    delete fn1;
	  if (fn2)
	    delete fn2;
	}

    }

    // ------------ Functions inherited from UnaryDD --------------
    virtual double operator() (double x)
      {
	return opfn::opfn ( (*fn1)(x) , (*fn2)(x)  );
      };


  };
    

  


}

#endif
