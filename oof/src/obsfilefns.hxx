/**
   \file obsfilefns.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>

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
