/*
  Bojan Nikolic
  $Id: astromapio.cxx,v 1.1 2005/08/18 04:56:18 bnikolic Exp $
*/

#include "astromapio.hxx"

#include <iostream>

#include <fitswrap.hxx>
#include <tfitsops.hxx>
#include <fitserr.hxx>


#include "astromap.hxx"

namespace AstroMap {

  void FitsWrite ( Map & m,
		   const char * fnameout )
  {
    using namespace BNFits;

    try {
      FitsF fout ( fnameout, FitsF::create);

      std::vector<long> axes(2);
      axes[0] = m.nx;
      axes[1] = m.ny;
      fout.MkImage(axes, DOUBLE_IMG);

      WriteImg( fout,
		m);
    }     
    catch (FIOExc exc ) 
      {
	std::cerr<<"\n ERROR: Loading image failed with following error:\n";
	std::cerr<<exc.what();
	std::cerr<<"\n Unkown results writen";
      }
    
  }

}



