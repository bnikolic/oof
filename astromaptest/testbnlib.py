

import pybnlib

dd = range(1,10)

da= pybnlib.doubleArray( len(dd))

for i, val in enumerate(dd): da[i]=val

il=pybnlib.InterpolatorLog(da, da, len(dd) , pybnlib.InterpolatorLog.akima, pybnlib.InterpolatorLog.linear )

il2=pybnlib.InterpolatorGSL(da, da, len(dd) , pybnlib.InterpolatorLog.akima)


