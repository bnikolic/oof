{ system ? builtins.currentSystem }:
let

  pkgs = (import <nixpkgs1703> ) { inherit system; };
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
     buildInputs = [ pkgs.python35
          pkgs.python35Packages.numpy
          pkgs.python35Packages.scipy
          pkgs.python35Packages.pandas
          matplotlib
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

  pymp = pkgs.python35Packages.buildPythonPackage rec {
      pname = "pymp-pypi";
      name = "pymp-pypi-${version}";
      version = "0.4.0";

    src = pkgs.python35Packages.fetchPypi {
      inherit pname version;
      sha256 = "1pcrq84rmd1sg6wi7wfrzwyzpzxz2qf37kwxsy9rlqvrgwqf5pam";
    };

         propagatedBuildInputs = [ pkgs.python35Packages.numpy ];

  };

  kiwisolver = pkgs.python35Packages.buildPythonPackage rec {
      pname = "kiwisolver";
      name = "kiwisolver-${version}";
      version = "1.0.1";

    src = pkgs.python35Packages.fetchPypi {
      inherit pname version;
      sha256 = "0y22ci86znwwwfhbmvbgdfnbi6lv5gv2xkdlxvjw7lml43ayafyf";
    };

  };
  

  matplotlib = callPackage pkgs/matplotlib {
  buildPythonPackage=pkgs.python35Packages.buildPythonPackage ;
  inherit (pkgs.python35Packages) pycairo
  backports_functools_lru_cache  cycler dateutil nose numpy
  pyparsing sphinx tornado mock pytz
  pygobject3 functools32  pyqt4 pythonOlder ;     inherit (pkgs.darwin.apple_sdk.frameworks) Cocoa;  } ;


  };
in
    self // pkgs
