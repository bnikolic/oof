{ stdenv, gcc, swig, fetchurl, gsl, boost, python27, autoconf,  automake, libtool }:
stdenv.mkDerivation rec {

    name = "bnlib";

    buildInputs = [ swig gsl boost python27 autoconf automake libtool ];

    src = fetchurl {
    #    	url = "http://www.mrao.cam.ac.uk/~bn204/soft/${name}-1.3.2.tar.bz2";
    url = "file:///home/bnikolic/n/astroweb-mrao/static/soft/bnlib-1.3.3.tar.gz";
	sha256 = "04j19x46dc38wqw7b3ixdx7fazv1bnhg33zbcg6qr3pxj9qrxc19";
    };

    configureFlags= [ "--with-boost-libdir=${boost}/lib" ];

    enableParallelBuilding = true;

}
