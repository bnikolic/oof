/*!
  Bojan Nikolic
  $Id: cassegrain.hxx,v 1.2 2005/06/21 14:27:43 bnikolic Exp $

*/
#ifndef _OOF_TELGEO_CASSEGRAIN_HXX__
#define _OOF_TELGEO_CASSEGRAIN_HXX__

namespace OOF {

  /*! Describes the geometry when using a cassegrain focus */
  struct CassegrainGeo {
    
    /*! Radius of the primary reflector */
    double PrimRadius;
    
    /*! Focal length of the primary */
    double PrimF;
    
    /*! Radius of the secondary */
    double SecRadius;

    /*! Effective focal length at cassegrain focus*/
    double CasF;
  };

  /*! Calculate path change due to movement of the secondary mirror
   *  from optimal position.
   *
   *  x,y is the positions in the aperture plane to calculate the path
   *  change.  
   *  dX, dY , dZ are the movements of the secondary mirror. 
   */
  double SecDeltaPath (double x, double y,
		       double dX, double dY , double dZ,
		       const CassegrainGeo & geo);

  
}
#endif
