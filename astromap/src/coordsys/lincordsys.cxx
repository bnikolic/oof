/*
  Bojan Nikolic
  $Id: lincordsys.cxx,v 1.3 2005/07/03 16:15:06 bnikolic Exp $

*/

#include "lincordsys.hxx"

#include <bndebug.hxx>

#include <gsl/gsl_linalg.h>

namespace AstroMap {

  
  LinCS::LinCS(void) :
    TM(6)
  {
    // Unit transform
    TM[0] =1;
    TM[1] =0;
    TM[2] =0;
    TM[3] =0;
    TM[4] =1;
    TM[5] =0;
  }

  LinCS::~LinCS()
  {

  }

  void LinCS::pxtoworld(double px , double py , double &wx , double &wy) const 
  {
    const unsigned naxis = 2;

    // Pixel coordinate vector
    std::valarray<double> pc(naxis);
    pc[0] = px;
    pc[1] = py;
    
    // World coordinate vector
    std::valarray<double> wc(naxis);    
    
    for(unsigned  i=0 ; i< naxis ; ++i) 
      {
	wc[i]= TM[ i*(naxis+1) +naxis ];
	for (unsigned j=0 ; j < naxis ; ++j) 
	  {
	    wc[i] += pc[j] * TM[ i*(naxis+1) + j ] ;
	  }
      }

    wx = wc[0];
    wy = wc[1];

  }

  void LinCS::worldtopx(double wx, double wy , double &px , double &py ) const 
  {
    /* The following algorithm is infact general for any number of
       dimensions... */

    unsigned const naxis =2 ;
    
    std::valarray <double> v(naxis);

    std::valarray <double> wc(naxis);
    wc[0]=wx;
    wc[1]=wy;

    // the actual matrrix
    std::valarray<double> tmatrix (naxis *naxis);
    // the offsets
    std::valarray<double> offsets (naxis);

    // the world coordiantes - offset
    std::valarray<double> vwc(naxis);

    for (unsigned i(0) ; i < (unsigned) naxis ; i++ ) 
      {
	for (unsigned j(0) ; j < (unsigned) naxis; j++ ) 
	  {
	    tmatrix[i*naxis + j] = TM[ i*(naxis+1) +j];
	  }
	offsets[i] = TM[ i*(naxis+1) +naxis];
	vwc[i]=wc[i] - offsets[i];
      }
  
    /// the forwrad equation is W = M * px + Offset
    /// so invert as  M^-1 * (W-offset) = px
  
    gsl_matrix_view m 
      = gsl_matrix_view_array (&tmatrix[0], naxis, naxis);
    
    gsl_vector_view b
      = gsl_vector_view_array(&vwc[0] , naxis);
    
    gsl_vector_view x
      = gsl_vector_view_array(&v[0] , naxis);
    
    int s;
    
    gsl_permutation * p = gsl_permutation_alloc (naxis);
    
    gsl_linalg_LU_decomp (&m.matrix, p, &s);
    
    gsl_linalg_LU_solve (&m.matrix, p, &b.vector, &x.vector);
    
    px = v[0];
    py = v[1];

  }

}


