{ stdenv, gcc, swig, fetchurl, gsl, boost, python27, autoconf,  automake, libtool, fetchgit }:
let
   srcs = import ../oofsrcs.nix { inherit fetchgit; };
in 
stdenv.mkDerivation rec {

    name = "bnlib";

    buildInputs = [ swig gsl boost python27 autoconf automake libtool ];

#    releasesrc = fetchurl {
#    	url = "http://www.mrao.cam.ac.uk/~bn204/soft/${name}-1.3.2.tar.bz2";
#	sha256 = "04j19x46dc38wqw7b3ixdx7fazv1bnhg33zbcg6qr3pxj9qrxc19";
#   };
   
   src = srcs.src;

   configureFlags= [ "--with-boost-libdir=${boost}/lib" ];

   enableParallelBuilding = true;
   sourceRoot= "${srcs.sourcePref}/bnlib" ;

   preConfigure = "autoreconf -i" ; 
}
