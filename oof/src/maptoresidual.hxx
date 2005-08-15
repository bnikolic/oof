/*!
  Bojan Nikolic
  $Id: maptoresidual.hxx,v 1.2 2005/08/15 15:02:07 bnikolic Exp $

*/

#ifndef __OOF_MAPTORESIDUAL_HXX__
#define __OOF_MAPTORESIDUAL_HXX__

#include <vector>

#include <astromap_fwd.hxx>

namespace OOF {

  /*!
  *  Abstract class which returns residuals given a beam map. It
  *  basically defines the residuals half of the Minim::Model
  *  interface.
  *
  */
  class MapToResidual {

  public:

    /* ----- Constructors / Destructors  ----------------*/
    
    /* We have to know what sorts of maps we are dealing with so
       probably all actuall implementations will have constructors
       with take a msample as an arguemnt. */

    /* ----- Member Functions ---------------------------*/

    /*! Return the number of residuals that this class will return */
    virtual unsigned   nres (void)    = 0  ; 

    /*! Return the actuall residuals by writing them to the supplied
     *  valarray. Model is the model map that should be compared to
     *  the data. Return value is the number of residuals written ==
     *  nres() */
    virtual size_t residuals ( AstroMap::Map & model, 
			       std::vector<double>::iterator  resv ) =0 ;




    

  };


}


#endif
