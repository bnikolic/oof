/**
   \file mapset.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>
*/

#include "mapset.hxx"

#include <valarray>

#include "tmapset.hxx"

namespace AstroMap {

  void WorldSet(Map &m , BNLib::BinaryDD &fn )
  {
    TWorldSet( m  , fn);
  }

  void WorldAdd(Map &m , BNLib::BinaryDD &fn )
  {
    TWorldAdd(m, fn);
  }

  void WorldSet(Map &m , BNLib::BinaryDD &fn, std::valarray<bool> const &mask )
  {
    TWorldSet( m  , fn, mask);
  }

}


