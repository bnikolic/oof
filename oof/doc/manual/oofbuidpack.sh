COMPS="bnlib bnfits astromap bnmin1 oof" 
for x in ${COMPS}
do
  (cd ${x} && 
      echo ">>> Building ${x}" &&
      autoreconf -i && 
      ( (  cd pybind && 
	      autoreconf -i  )  ||
	  (  cd plot && 
	      autoreconf -i  ) 
	  ) && 
      ./configure --prefix=${BNPREFIX} && 
      make install &&
      make dist-bzip2 )      
done

