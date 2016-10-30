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

  };
in
    self
