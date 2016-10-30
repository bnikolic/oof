{ fetchurl,  stdenv, x11, gfortran  }:

stdenv.mkDerivation rec {
  version = "5.2";
  name = "pgplot${version}";

  buildInputs = [ x11 gfortran];

  patches = [ ./driverenable.patch  ];

  preBuild = "./makemake $PWD linux g77_gcc";

  postInstall = ''
    mkdir -p $out/lib &&
    cp libcpgplot.a libpgplot.a libpgplot.so grfont.dat rgb.txt $out/lib
    mkdir -p $out/include &&
    cp cpgplot.h $out/include &&
    mkdir -p $out/bin &&
    cp pgxwin_server $out/bin
  '';

  # Builds both the "C" biding and standard Fortran
  buildFlags = [ "all cpg" ];

  src = fetchurl {
    url = "ftp://ftp.astro.caltech.edu/pub/pgplot/${name}.tar.gz";
    sha256 ="1r2vg9ra9a920j1fiwg3fxjfc7z6k90ffjnz4r6xh45537vryyd5";
  };

  meta = {
    description = "Device-independent graphics package for making graphs and diagrams";
    homepage = http://www.astro.caltech.edu/~tjp/pgplot/;

    longDescription = ''The PGPLOT Graphics Subroutine Library is a
    Fortran- or C-callable, device-independent graphics package for
    making simple scientific graphs. It is intended for making
    graphical images of publication quality with minimum effort on the
    part of the user. For most applications, the program can be
    device-independent, and the output can be directed to the
    appropriate device at run time.'';

  };
}
