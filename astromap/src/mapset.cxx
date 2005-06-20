/*
  Bojan Nikolic
  $Id: mapset.cxx,v 1.1 2005/06/21 00:44:46 bnikolic Exp $

*/

#include "mapset.hxx"

#include "tmapset.hxx"

namespace AstroMap {

  void WorldSet(Map &m , BNLib::BinaryDD &fn )
  {
    TWorldSet( m  , fn);
  }

}


