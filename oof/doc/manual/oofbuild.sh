# Bojan Nikolic <bojan@bnikolic.co.uk>
# Helper script to build oof

export CPPFLAGS="${CPPFLAGS} -I${OOFPREFIX}/include"
export CFLAGS="${CFLAGS} -I${OOFPREFIX}/include" 
export SWIGFLAGS="-I${OOFPREFIX}/include" 
export LDFLAGS="${LDFLAGS} -L${OOFPREFIX}/lib"

COMPS="bnlib-1.1 bnfits-1.1 astromap-1.1 bnmin1-1.1 oof-1.1"

for x in ${COMPS}
do
  tar xvjf ${x}.tar.bz2  &&
  (cd ${x} &&
   ./configure --prefix=${OOFPREFIX} && 
   make install
   )
done

