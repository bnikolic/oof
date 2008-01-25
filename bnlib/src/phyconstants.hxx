/**
   \file phyconstants.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   Some physical constants
*/
#ifndef _BNLIB_PHYCONSTANTS_HXX__
#define _BNLIB_PHYCONSTANTS_HXX__

namespace BNLib{

  /** Sub-namespace for physical constants. Values taken from the NIST
      constant lists, some time in 2002. */
  namespace Phy {

    extern double const c_m_s   ; 
    extern double const  h_J_s  ; 
    extern double const  k_J_K;

    extern double const eV_J ;
    
    extern double const Mpc_m;

    extern double const LSolar_W;

  }

}


#endif
