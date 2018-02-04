{ system ? builtins.currentSystem }:
let

  pkgs = (import <nixpkgs> ) { inherit system; };
  callPackage = pkgs.lib.callPackageWith (pkgs  // self);

  self = rec {

  bnlib = callPackage pkgs/bnlib { };
  bnfits = callPackage pkgs/bnfits { };
  astromap = callPackage pkgs/astromap { };
  bnmin1 = callPackage pkgs/bnmin1 { };
  pgplot = callPackage pkgs/pgplot { };
  oof = callPackage pkgs/oof { };

  oofenv = pkgs.stdenv.mkDerivation rec {
     name = "oofenv";
     buildInputs = [ oof pkgs.python27
     pkgs.python27Packages.numpy
     pkgs.python27Packages.scipy
           pkgs.python27Packages.pandas
	   pkgs.python27Packages.matplotlib
	  ] ;
  };

  oofpyenv = pkgs.stdenv.mkDerivation rec {
     name = "oofpyenv";
     buildInputs = [ pkgs.python36
          pkgs.python36Packages.numpy
          pkgs.python36Packages.scipy
          pkgs.python36Packages.pandas
          pkgs.python36Packages.matplotlib
	  pymp
	  ] ;
  };  

  pyfits = pkgs.python27Packages.buildPythonPackage rec {
    name = "pyfits-${version}";
    version = "3.5";
    src = pkgs.fetchurl {
      url = "https://pypi.python.org/packages/c0/5d/ffae283cea526bce7c1154e7309a040a3e8c02e973b2360bcfc8f30134ef/pyfits-3.5.tar.gz";
      sha256 = "066gbaf57jf3p6iyssrxvqyi6kfdmwi85ky61dcl1hd3sli8crjf";
    };
    checkPhase = ''
    '';
    doCheck = false;
      installCheckPhase = " " ;
    propagatedBuildInputs = [ pkgs.python27Packages.numpy ];

  };

  pymp = pkgs.python36Packages.buildPythonPackage rec {
      pname = "pymp-pypi";
      name = "pymp-pypi-${version}";
      version = "0.4.0";

    src = pkgs.python36Packages.fetchPypi {
      inherit pname version;
      sha256 = "1pcrq84rmd1sg6wi7wfrzwyzpzxz2qf37kwxsy9rlqvrgwqf5pam";
    };

         propagatedBuildInputs = [ pkgs.python36Packages.numpy ];

  };


  };
in
    self // pkgs
