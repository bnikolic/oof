import math
import imp # for reload
import json
from itertools import cycle
from cycler import cycler

import matplotlib
import matplotlib.pyplot as plt

import numpy
import pandas

# NB linestyle cycler broken in matplotlib 2.0.2
plt.rc("axes", prop_cycle=(cycler("color", ['r', 'g', 'b', 'y' ] )+
                           cycler("linestyle", ["-","--","-.",":"])))
plt.rc("savefig", dpi=300)
plt.rc("path", simplify=True)
plt.rc("font", family="serif")
plt.rc("mathtext", fontset ="custom")
plt.rc("text", usetex=True)


for x in ["xtick", "ytick"]:
    plt.rc(x+".major", size=6, width=1)
    plt.rc(x+".minor", size=3, width=1)

plt.rc("lines", markeredgewidth= 1)

plt.rc("legend", numpoints=1, frameon= False, handletextpad=   0.3)

#plotstyle={ "capsize": 4, "capthick": 0.5, "elinewidth": 0.5}
matplotlib.style.use('seaborn-paper')


def loadtimings(d):
    i=0
    res=[]
    while os.path.exists("%s/sn%i.json" %(d,i)):
        p=json.load(open("%s/sn%i.json" %(d,i)))
        res.append(p)
        i+=1
    return pandas.DataFrame(res)

def plot(df):
    for nzern in (2,3,4):
        m=(df["nzern"]==nzern)        
        fig=plt.figure(figsize=(5,4.0), dpi=200)
        ax=fig.add_subplot(1, 1, 1)
        for dotorch in [True, False]:
            m2=(df["dotorch"]==dotorch)
            dfm=df[numpy.logical_and(m, m2)]
            dfm.plot(x='NN',
                     y='time',
                     loglog=True,
                     label=("pyTorch == %s"% str(dotorch)),
                     ax=ax)
        ax.xaxis.set_ticks_position('both')
        ax.yaxis.set_ticks_position('both')
        plt.ylabel(r"$t\,$(s)")
        plt.xlabel("NN (pixels)")    
        plt.savefig("plots/timingnogpu-nz%i.png"%nzern)
        plt.close()

def plotvsz(df, NN):
    fig=plt.figure(figsize=(5,4.0), dpi=200)
    ax=fig.add_subplot(1, 1, 1)
    m=(df["NN"]==NN)        
    for dotorch in [True, False]:
        m2=(df["dotorch"]==dotorch)
        dfm=df[numpy.logical_and(m, m2)]
        dfm.plot(x='nzern',
                 y='time',
                 loglog=True,
                 label=("pyTorch == %s"% str(dotorch)),
                 ax=ax)
    ax.xaxis.set_ticks_position('both')
    ax.yaxis.set_ticks_position('both')
    plt.ylabel(r"$t\,$(s)")
    plt.xlabel("nzern")    
    plt.savefig("plots/timingnogpu-NN%i.png"% NN)
    plt.close()
        
