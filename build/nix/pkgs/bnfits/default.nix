{ stdenv, gcc, swig, fetchurl, gsl, boost, python27, autoconf,  automake, libtool, cfitsio, fetchgit }:
let
   srcs = import ../oofsrcs.nix { inherit fetchgit; };
in 
stdenv.mkDerivation rec {

    name = "bnfits";

    buildInputs = [ swig gsl boost python27 autoconf automake libtool cfitsio ];

#    src = fetchurl {
    	#url = "http://www.mrao.cam.ac.uk/~bn204/soft/${name}-1.2.tar.bz2";
#	url = "file:///home/bnikolic/n/astroweb-mrao/static/soft/bnfits-1.2.1.tar.gz";
#	sha256 = "1cscs8pnz0y675p1mr7v9f8al1v4qarybla6lg6v9abhc5akn111";
#    };

    configureFlags= [ "--with-boost-libdir=${boost}/lib" ];

    enableParallelBuilding = true;

   src = srcs.src;
   sourceRoot= "${srcs.sourcePref}/${name}" ;
   preConfigure = "autoreconf -i" ; 
   
}
