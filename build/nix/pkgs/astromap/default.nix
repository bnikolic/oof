{ stdenv, gcc, swig, fetchurl, gsl, boost, python27, autoconf,  automake, libtool, cfitsio,
  pkgconfig,
  fftw,   pgplot,
  bnlib, bnmin1, bnfits, xorg, libpng}:
stdenv.mkDerivation rec {

    name = "astromap";

    buildInputs = [swig gsl boost python27 autoconf automake libtool cfitsio pkgconfig fftw pgplot bnlib bnmin1 bnfits
    		   xorg.libXpm libpng];

    src = fetchurl {
#    	url = "http://www.mrao.cam.ac.uk/~bn204/soft/${name}-1.2.tar.bz2";
    	url = "file:///home/bnikolic/n/astroweb-mrao/static/soft/astromap-1.5.tar.bz2";
	sha256 = "0rpmmlqga7b7rmnmwr36b70nyl3fl5hww9nzzb62zgixk1gbz41n";
    };

    configureFlags= [ "--with-boost-libdir=${boost}/lib" ];

    enableParallelBuilding = true;

}
