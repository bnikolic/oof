/*
  Bojan Nikolic

*/

#include "mapset.hxx"

#include <valarray>

#include "tmapset.hxx"

namespace AstroMap {

  void WorldSet(Map &m , BNLib::BinaryDD &fn )
  {
    TWorldSet( m  , fn);
  }

  void WorldSet(Map &m , BNLib::BinaryDD &fn, std::valarray<bool> const &mask )
  {
    TWorldSet( m  , fn, mask);
  }

}


