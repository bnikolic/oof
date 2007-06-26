/**
   \file phycosmo.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   Some simple cosmology routines
*/

#ifndef _BNLIB_PHYCOSMO_HXX__
#define _BNLIB_PHYCOSMO_HXX__

namespace BNLib{

  namespace Phy {

    /*!
     * Relativistic cosmology
     */
    class RelCosmo {
    
    private:

      /*! Hubble parameter */
      double H0;     
      /*! Omega matter?    */
      double O0;
      /*! Omega lambda     */
      double OL;

      /*! Speed of light in km per seconds*/
      double c_km_s ;
      
    public:

      RelCosmo( double H0_km_s_Mpc= 70  , 
		double  Omega_0=0.3 , 
		double Omega_L =0.7 );

      
      double comovingr( double z) ; 
      
      /*! The comoving radial distance in megaparsecs, _different_
       *  from luminosity distance  
       */
      double D_Mpc(double z);
      double D_m(double z) ;

      /*! The luminosity distance */
      double DLum_m(double z);
      /*! Luminosity distance in Mega-parsecs */
      double DLum_Mpc(double z);
      
      double Dangular_m(double z);
      double Dangular_Mpc(double z);
      
    };

  }
}

#endif
