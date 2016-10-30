{ stdenv, gcc, swig, fetchurl, gsl, boost, python27, autoconf,  automake, libtool,    pkgconfig, gfortran }:
stdenv.mkDerivation rec {

    name = "bnmin1";

    buildInputs = [ swig gsl boost python27 autoconf automake libtool  pkgconfig gfortran ];

    src = fetchurl {

    #url = "http://www.mrao.cam.ac.uk/~bn204/soft/${name}-1.11.tar.bz2";
url = "file:///home/bnikolic/n/astroweb-mrao/static/soft/bnmin1-1.12.tar.gz";
	sha256 = "0kkbbp4hs11xvgkk0yzs9hqmyk0994k173g9y3v48dslh5mgkrl1";
    };

    configureFlags= [ "--with-boost-libdir=${boost}/lib"
    		      "--disable-buildtests"
    		      "FFLAGS=-fno-range-check"];

    enableParallelBuilding = true;

}
