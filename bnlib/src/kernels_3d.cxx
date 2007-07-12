/**
   \file kernels_3d.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
   
   June 2007   

*/   

#include "kernels_3d.hxx"

#include <cmath>

namespace BNLib {

  void KConvolve3D( const Displacement3D * dps ,
		    const double * coeffs,
		    const size_t KN,
		    const double * cube,
		    const Extnent3D & ext,
		    const Position3D * pos,
		    const size_t PN,
		    double * out )
  {

    for ( size_t pcounter = 0 ; pcounter < PN ; ++pcounter )
    {
      const Position3D & cp = pos[pcounter] ;
      double res= 0;
      double csum = 0;
      
      for (size_t ccounter = 0 ; ccounter < KN ; ++ ccounter )
      {
	const  Displacement3D &  cd = dps[ccounter];
	
	int i,j,k;
	i = cp.i + cd.i;
	j = cp.j + cd.j;
	k = cp.k + cd.k;

	if ( i >= 0 && i < (int) ext.i  &&
	     j >= 0 && j < (int) ext.j  &&
	     k >= 0 && k < (int) ext.k   )
	{
	  csum += coeffs[ccounter];
	  res += coeffs[ccounter] * cube[ i + j * ext.i + k * ext.i *ext.j ] ;
	}
      }

      out[pcounter] = res / csum;

    }

  }

  void KConvolve3D( const std::vector<Displacement3D> & dps,
		    const std::vector<double> & coeffs,
		    const double * cube,
		    const Extnent3D & ext,
		    const std::vector<Position3D> & pos,
		    std::vector<double> & out )
  {
    out.resize( pos.size() );

    KConvolve3D( & dps[0],
		 & coeffs[0],
		 dps.size() ,
		 cube,
		 ext,
		 & pos[0],
		 pos.size(),
		 & out[0] );

  }

  void GenZCylinder( std::vector<Displacement3D> & dps,
		     std::vector<double> & coeffs,
		     double r_px,
		     size_t zextent )
  {
    int r2 = (int) pow(r_px, 2);

    dps.resize(0);
    coeffs.resize(0);

    if (zextent == 0 )
      return;

    Displacement3D dp;
    size_t cz = 0 ;
    do 
    {
      for ( int j = - ( (int) r_px ) ; j < ( (int) r_px) ; ++ j )
      {
	for ( int i = - ( (int)  r_px ) ; i < ( (int) r_px) ; ++ i )
	{
	  if ( i*i +j*j <= r2 )
	  {
	    dp.i = i ; 
	    dp.j = j ;
	    dp.k = cz;
	    dps.push_back( dp);
	    coeffs.push_back(1.0);
	  }
	}
      }
      ++cz;
    } while ( cz  < zextent );
	
    

  }

  void GenGaussCylinder( std::vector<Displacement3D> & dps,
			 std::vector<double> & coeffs,
			 double r_px,
			 size_t zextent_px,
			 size_t rextent_px,
			 double zh_start,
			 double zh_increment)
  {
    dps.resize(0);
    coeffs.resize(0);

    Displacement3D dp;
    for ( size_t z =0 ; z < zextent_px ; ++z )
    {
      double zhat = zh_start + z * zh_increment;
      // Radius squared of the gaussian at this z
      double g_r_px_2  = r_px*r_px * ( 1 + pow(zhat,2) );
      
      dp.k=z;
      for ( int j = - ( (int) rextent_px ) ; j < ( (int) rextent_px ) ; ++j )
      {
	dp.j = j;
	for ( int i = - ( (int) rextent_px ) ; i < ( (int) rextent_px ) ; ++i )
	{
	  int r2 = i*i + j*j;
	  dp.i = i;
	  dps.push_back(dp);
	  coeffs.push_back( exp( -0.5 *  r2 / g_r_px_2 ));
	}

      }


    }
    


  }


}


