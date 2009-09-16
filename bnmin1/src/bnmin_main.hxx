/**
   \file bnmin_main.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>

   The main include file for BNMin1 Library
   
   \mainpage A simple minimisation / inference library

*/

#include <string>
#include <stdexcept>

#ifndef __BNMIN_BNMIN_MAIN_HPP__
#define __BNMIN_BNMIN_MAIN_HPP__
namespace Minim {


  const char * version(void);

  /** \brief Base class for run-time errors within the library 
   */
  class BaseErr:
    public std::runtime_error
  {
  public:
    BaseErr(const std::string &s);

  };

  class NParsErr:
    public BaseErr
  {
  public:
    NParsErr(const std::string &fname,
	     size_t expected,
	     size_t received);
    

  };


}
#endif

