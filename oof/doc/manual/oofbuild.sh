# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Bash script that illustrates building the OOF application

# Note: we are now using the pkg-config utility, simplifying
# installation considerably

export PKG_CONFIG_PATH=${OOFPREFIX}/lib/pkgconfig/

COMPS="bnlib-1.2.1 bnfits-1.2 astromap-1.2 bnmin1-1.3 oof-1.2"

for x in ${COMPS}
do
  if  [ -e ${x}.tar.bz2 ] ;  then 
  tar xvjf ${x}.tar.bz2  &&
  (cd ${x} &&
      ./configure --prefix=${OOFPREFIX} ${BOOSTFLAG} && 
      make install
      )
  else
      echo "Cant find ${x} !!!"
      break
  fi
done

