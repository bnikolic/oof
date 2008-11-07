/**
   \file astromapio.cxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>
*/

#include "astromapio.hxx"

#include <iostream>
#include <typeinfo>

#include <fitswrap.hxx>
#include <tfitsops.hxx>
#include <fitserr.hxx>


#include "astromap.hxx"
#include "coordsys/csfileio.hxx"

namespace AstroMap {

  Map * FitsMapLoad ( BNFits::FitsF &fin ) 
  {
    using namespace BNFits;

    try {
      // Get the dimensions of the map;

      std::vector<long> imgdims;
      ImgDims(fin, imgdims);

      if ( imgdims.size() < 2)
      {
	throw FIOExc("none" , "Too few dimensions in image", 0);
      }
      
      if ( imgdims[0] == 0 || imgdims[1]  ==0 )
      {
	throw FIOExc(FName(fin) , 
		     "Zero length dimension in image", 0);
      }

      // Load the coordinate system
      CoordSys * cs = FitsCSLoad( fin );

      // Create a map with correct cs
      Map * res = new Map(imgdims[0],imgdims[1],cs);
      
      // And finally load image data
      LoadImg(fin, *res);

      return res;
    } 
    catch ( FIOExc exc ) 
      {
	std::cerr<<"\n ERROR: Loading image failed with following error:\n";
	std::cerr<<exc.what();
	std::cerr<<"Re-throwing exception";
	throw;
      }
  }

  Map * FitsMapLoad ( const char * fnamein, int extno) throw (BNFits::FIOExc)
  {
    using namespace BNFits;
    
    FitsF fin ( fnamein, FitsF::read);

    fin.HDUseek(extno);

    return FitsMapLoad(fin);

  }


  void FitsWrite ( Map & m,
		   BNFits::FitsF &fout) throw (BNFits::FIOExc)

  {
    using namespace BNFits;

    std::vector<long> axes(2);
    axes[0] = m.nx;
    axes[1] = m.ny;
    fout.MkImage(axes, DOUBLE_IMG);

    WriteImg( fout,
	      m);
    
    FitsWrite( *(m.cs), fout,
	       m.nx, m.ny);    

  }

  void FitsWrite ( Map & m,
		   const char * fnameout ) throw (BNFits::FIOExc)
  {
    using namespace BNFits;
    FitsF fout (fnameout, FitsF::create);
    FitsWrite(m, fout);
  }

  void FitsWrite ( std::vector<Map *> mvect,
		    const char * fnameout )
  {
    using namespace BNFits;

    try {
      FitsF fout ( fnameout, FitsF::create);
      
      for (unsigned i =0 ; i < mvect.size() ; ++i)
	FitsWrite( (*mvect[i]), fout);
    }     
    catch (FIOExc exc ) 
      {
	std::cerr<<"\n ERROR: Writing image failed with following error:\n";
	std::cerr<<exc.what();
	std::cerr<<"\n Unkown results writen";
      }

  }

}



