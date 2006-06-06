/**
   \file pixiterators.cxx

   $Id: pixiterators.cxx,v 1.1 2006/06/06 20:10:47 bnikolic Exp $
*/

#include "pixiterators.hxx"

#include "bndebug.hxx"

namespace AstroMap {

  PixISpiral::PixISpiral ( int cx, int cy  ):
    cx(cx), cy(cy),
    x(cx) , y(cy),
    n(0)
  {

  }

  void PixISpiral::operator++ (void)
  {
    
    if ( n == 0 )
      {// we're at origin
	x++; y--;
      }
    else
      {
	if ( ( x -cx)   == n ) // on the right edge
	  {
	    
	    if ( (y-cy) == n ) // top right corner:
	      x--;
	    else if ( (cy-y) == n ) // bottom right corner
	      {
		ENFORCE(false);
	      }
	    else
	      y++;
	  }
	else if ( (y-cy) == n ) // top edge
	  {
	    if ( (cx -x ) ==n ) // top right corner
	      y--;
	    else
	      x--;
	  }
	else if ( ( cx-x) == n ) // left edge
	  {
	    if ( (cy- y) == n)  // bottom left corner
	      x++;
	    else
	      y--;
	  }
	else // must be on bottom edge
	  {
	    if ( (x- cx)  == (n -1 ) )
	      {
		x++; x++ ; y--;
		n++;
	      }
	    else
	      x++;
	  }
      }
  }

}



