/*
  Bojan Nikolic
  $Id: obsfilefns.hxx,v 1.2 2005/08/18 15:25:47 bnikolic Exp $

  Input/output support functions for observations 
*/

#ifndef __OOF_OBSFILEFNS_HXX__
#define __OOF_OBSFILEFNS_HXX__

namespace OOF {

  class ObsCompare;

  /*! Write out the model beams to the specified file */
  void WriteBeams( ObsCompare &oc, 
		   const char * fname);

  
  



}

#endif
