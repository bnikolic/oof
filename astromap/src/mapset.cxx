/*
  Bojan Nikolic
  $Id: mapset.cxx,v 1.2 2005/08/06 14:12:11 bnikolic Exp $

*/

#include "mapset.hxx"

#include <valarray>

#include "tmapset.hxx"

namespace AstroMap {

  void WorldSet(Map &m , BNLib::BinaryDD &fn )
  {
    TWorldSet( m  , fn);
  }

  void WorldSet(Map &m , BNLib::BinaryDD &fn, std::valarray<bool> &mask )
  {
    TWorldSet( m  , fn, mask);
  }

}


