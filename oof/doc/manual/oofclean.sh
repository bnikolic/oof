COMPS="bnlib bnfits astromap bnmin1 oof" 
for x in ${COMPS}
do
  (cd ${x} && make distclean && cd ..)
done
