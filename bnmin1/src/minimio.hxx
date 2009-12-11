/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2003

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file minimio.hxx

   Routines four I/O of minimiser data
*/

#ifndef __BNMIN1_MINIMIO_HXX__
#define __BNMIN1_MINIMIO_HXX__

namespace Minim {

  class ModelDesc;


  /*! Print out parameter data to standard output */
  void PrettyPrint( ModelDesc &mod);


}

#endif
