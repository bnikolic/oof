/*
  Bojan Nikolic
  $Id: dataseries.cxx,v 1.4 2005/09/06 00:18:28 bnikolic Exp $

  Data series support
*/

#include "dataseries.hxx"

namespace AstroMap {


  DataSeries::DataSeries( size_t len):
    DSBase( len)
  {

  }

  DataSeries::DataSeries( void):
    DSBase( 0)
  {

  }

  DataSeries* DataSeries::clone(void)
  {
    return new DataSeries(*this);
  }

  void InvertDS ( DataSeries &ds)
  {
    for (size_t i =0 ; i < ds.size() ; ++i )
      {
	ds[i].dX *= -1.0;
	ds[i].dY *= -1.0;
      }
  }

}

