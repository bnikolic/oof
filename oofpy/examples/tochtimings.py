# Time torch accelleration
import json
import timeit
import os

def dotimings(dirout="timings"):
    i=0
    pars={ 'tol' : 1e-8,
           'number': 5}
    if not os.path.exists(dirout):
        os.makedirs(dirout)
    for dotorch in [True, False]:
        pars["dotorch"]=dotorch
        for NN in [32, 64, 128, 256, 512]:
            for nzern in [2,3,4,5,6,7]:
                pars["NN"]=NN
                pars["nzern"]=nzern
                r=timeit.timeit("rr2=ooftorch.dofit({dotorch}, tol={tol})".format(**pars),
                                "import ooftorch; ooftorch.setupfortime({NN}, {nzern})".format(**pars),
                                number=pars["number"])
                pars["time"]=r
                open(os.path.join("%s/sn%i.json"  % (dirout, i)), "w").write(json.dumps(pars))
                i+=1
