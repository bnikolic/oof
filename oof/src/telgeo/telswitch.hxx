/**
   \file telswitch.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Return telescope geometries for supported telescopes 
*/
#ifndef _OOF_TELSWITCH_HXX__
#define _OOF_TELSWITCH_HXX__


namespace OOF {

  // Forwards
  class TelGeometry;

  /*! 
   * Return the geometry of an ALMA antenna 
   */
  TelGeometry * MkALMA(void);

  /*! 
   * Return the appropriate geometry by switching on a upplied
   * string. Will return NULL if string wan not recognised.
   */
  TelGeometry * TelSwitch(const char * telname );
  

}

#endif
