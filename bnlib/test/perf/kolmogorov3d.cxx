
#include "../../src/kolmogorov_3d.hxx"
#include "../../src/bnrandom.hxx"

int main(void)
{
  
  size_t Nx=513;
  size_t Ny=65;
  size_t Nz=65;
  
  double * cube = new double[Nx*Ny*Nz];
  
  BNLib::NormDistZM dist(1.0 );
  
  Kolmogorov3D( cube,
		Nx,
		Ny,
		Nz,
		dist);
  
  
  delete[] cube;


}
