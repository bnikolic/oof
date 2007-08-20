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
    
    // We need these to check if each point is within the grid
    // dimensions.
    const int Nx = (int) ext.i;
    const int Ny = (int) ext.j;
    const int Nz = (int) ext.k;

    // Need these for the indexing
    const size_t sNx = ext.i;
    const size_t sNxNy = ext.i *ext.j;

    for ( size_t pcounter = 0 ; pcounter < PN ; ++pcounter )
    {
      const Position3D & cp = pos[pcounter] ;

      const int cpi = cp.i;
      const int cpj = cp.j;
      const int cpk = cp.k;

      double res= 0;
      double csum = 0;
      
      for (size_t ccounter = 0 ; ccounter < KN ; ++ ccounter )
      {
	const  Displacement3D &  cd = dps[ccounter];
	
	int i,j,k;
	i = cpi + cd.i;
	j = cpj + cd.j;
	k = cpk + cd.k;

	if ( i >= 0 && i < Nx  &&
	     j >= 0 && j < Ny  &&
	     k >= 0 && k < Nz )
	{
	  csum += coeffs[ccounter];
	  res +=  coeffs[ccounter] * cube[ i + j * sNx + k * sNxNy] ;
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

  void FillDisplacement3D ( std::vector<Displacement3D> & dps,
			    size_t start,
			    const std::vector<double>  & i_v,
			    const std::vector<double>  & j_v,
			    const std::vector<double>  & k_v)
  {

    for (size_t l =0 ; l < i_v.size() ; ++l )
    {
      dps[start+l].i = (int) i_v[l];
      dps[start+l].j = (int) j_v[l];
      dps[start+l].k = (int) k_v[l];
    }
    
  }

  void ZFlatten( const double * cube,
		 const Extnent3D & ext,
		 size_t zstart,
		 size_t zend,
		 double * res)
  {

    const size_t Nx = ext.i;
    const size_t Ny = ext.j;
    const size_t NxNy = Nx*Ny;

    for (size_t z = zstart  ; z< zend ; ++z)
    {
      for ( size_t i = 0 ; i < NxNy ; ++i)
      {
	res[i] +=  cube[NxNy*z + i] ;
      }
    }
  }

  void SkewFlatten( const double * cube,
		    const Extnent3D & ext,
		    size_t zstart,
		    size_t zend,
		    double cx, 
		    double cy,
		    double dx,
		    double dy,
		    double * res)
  {
    const size_t Nx = ext.i;
    const size_t Ny = ext.j;
    const size_t NxNy = Nx*Ny;

    for (size_t z = zstart  ; z< zend ; ++z)
    {
      for ( size_t j = 0 ; j < Ny ; ++j )
      {
	double y = j + cy + dy * (z-zstart);
	int y_low = (int) floor(y);

	for ( size_t i = 0 ; i < Nx ; ++i)
	{
	  double x = i + cx + dx * (z - zstart);
	  int x_low = (int) floor(x);

	  if ( x_low < 0 ||
	       x_low +1 >= (int) Nx ||
	       y_low < 0 ||
	       y_low +1 >= (int) Ny )
	  {
	    res[j*Nx+i] = nan("NaN");
	  }
	  else
	  {
	    res[j*Nx+i] = 
	      (x-x_low + y - y_low)/2 * cube[NxNy*z + Nx*(y_low+1)+ x_low+1] +
	      (x_low +1 - x + y - y_low)/2 * cube[NxNy*z + Nx*(y_low+1)+ x_low] +
	      (x-x_low + y_low+1 - y )/2 * cube[NxNy*z + Nx*(y_low)+ x_low+1] +
	      (x_low+1-x + y_low+1 - y )/2 * cube[NxNy*z + Nx*(y_low)+ x_low];
	  }
	}
	
      }
    }

  }
  
}


