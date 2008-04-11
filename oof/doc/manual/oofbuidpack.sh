COMPS="bnlib bnfits astromap bnmin1 oof" 
for x in ${COMPS}
do
  (cd ${x} && 
      autoreconf -i && 
      (  cd pybind && 
	  autoreconf -i  ) && 
      ./configure --prefix=${BNPREFIX} && 
      make install &&
      make dist-bzip2 )      
done
