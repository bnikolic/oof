/*
  Bojan Nikolic
  $Id: telswitch.hxx,v 1.1 2005/06/25 13:39:40 bnikolic Exp $

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
