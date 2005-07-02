/*!
  Bojan Nikolic
  $Id: dsfileops.cxx,v 1.2 2005/07/02 20:43:51 bnikolic Exp $

*/

#include "dsfileops.hxx"

#include <memory>
#include <bndebug.hxx>

#include "dataseries.hxx"


namespace AstroMap {


  DataSeries * LoadFITSDS( const char * fname , unsigned extno)
  {

    
    std::auto_ptr<DataSeries> res (ENFORCE(new DataSeries(0 )));

    return res.release();

  }



}


