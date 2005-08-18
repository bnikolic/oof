/*
  Bojan Nikolic
  $Id: obsfilefns.hxx,v 1.3 2005/08/18 23:52:32 bnikolic Exp $

  Input/output support functions for observations 
*/

#ifndef __OOF_OBSFILEFNS_HXX__
#define __OOF_OBSFILEFNS_HXX__

namespace OOF {

  class ObsCompare;

  /*! Write out the model beams to the specified file */
  void WriteBeams( ObsCompare &oc, 
		   const char * fname);

  /*! Write out aperture the specified file. First extension is the
   *  amplitude, second extension in the phase 
   */
  void WriteAperture(ObsCompare &oc, 
		     const char * fname);

  
  



}

#endif
