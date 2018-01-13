{fetchgit} :
let
    gitrev = "e77fe79feda1f293a850451af97ba6eb8be7acf0" ;

    inherit (builtins) substring;
in rec
{
    src = fetchgit {
        url= "file:///home/user/n/oof" ;
        rev = "${gitrev}" ;
        sha256 = "1zwfq0jrgf5vqs6b8km8z1xpys821hk5n2sgprviix7if25kian6";
    };

    sourcePref = "oof-${substring 0 7 gitrev}";
}
