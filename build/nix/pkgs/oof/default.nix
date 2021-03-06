{ stdenv, gcc, swig, fetchurl, gsl, boost, python27, autoconf,  automake, libtool,    pkgconfig, cfitsio,
  bnlib, bnmin1, bnfits, astromap, fetchgit, python27Packages}:
let
   srcs = import ../oofsrcs.nix { inherit fetchgit; };
in   
stdenv.mkDerivation rec {

    name = "oof";

    buildInputs = [ swig gsl boost python27 autoconf automake libtool  pkgconfig cfitsio
    		   bnlib bnmin1 bnfits astromap];

    propagatedBuildInputs = [ python27Packages.numpy ] ;

#    src = fetchurl {
#    	url = "http://www.mrao.cam.ac.uk/~bn204/soft/${name}-1.4.tar.bz2";
#	url = "file:///home/bnikolic/n/astroweb-mrao/static/soft/oof-1.4.tar.bz2";
#	sha256 = "0x4zz8b8b4cjmnhilndff6hlh3fypghbk4q6rssi5p90n97z3v4j";
#    };

    configureFlags= [ "--with-boost-libdir=${boost}/lib"
       		      "--disable-buildtests"];

    enableParallelBuilding = true;
   src = srcs.src;
   sourceRoot= "${srcs.sourcePref}/${name}" ;
   preConfigure = "autoreconf -i" ;     

}
