# Plotting of retrieval error results

import imp # for reload
import json
from itertools import cycle
from cycler import cycler

import matplotlib
import matplotlib.pyplot as plt

import numpy
import pandas

from accuracy import wrms

# NB linestyle cycler broken in matplotlib 2.0.2
plt.rc("axes", prop_cycle=(cycler("color", ['r', 'g', 'b', 'y' ] )+
                           cycler("linestyle", ["-","--","-.",":"])))

matplotlib.style.use('seaborn-paper')

def wrmssim(d):
    "Load simulation data"
    i=0
    res=[]
    while os.path.exists("%s/sn%i.json" %(d,i)):
        p=json.load(open("%s/sn%i.json" %(d,i)))
        xx=numpy.load("%s/sn%i-ret.npz" %(d,i))['arr_0']
        zz=wrms (xx, p["nzern"])
        p["wrms"]=zz.mean()
        p["wrmserr"]=zz.std()/zz.shape[0]**0.5
        res.append(p)
        i+=1
    return pandas.DataFrame(res)


def plotvsnoise(df):
    fig=plt.figure(figsize=(7,5), dpi=150)
    ax=fig.add_subplot(1, 1, 1)
    for nzern in range(4,9):
        m=(df["nzern"]==nzern)
        dfm=df[m]
        dfm.plot(x='noisesn',
                y='wrms',
                 yerr='wrmserr',
                 loglog=True,
                 label=("nzmax=%i"%nzern),
                 ax=ax)
    ax.xaxis.set_ticks_position('both')
    ax.yaxis.set_ticks_position('both')    
    for tax in [ax.get_xaxis(), ax.get_yaxis()]:
        tax.set_major_formatter(matplotlib.ticker.ScalarFormatter())    
    plt.ylabel("$\epsilon\,$(rad)")
    plt.xlabel("(Noise per beam) / (Peak signal)")    
    plt.savefig("plots/errvsnoise.png")
    plt.close()


def plotvsdz(df):
    fig=plt.figure(figsize=(7,5), dpi=150)
    ax=fig.add_subplot(1, 1, 1)
    for sn in (1e-3, 5e-3, 1e-2):
        m=(df["noisesn"]==sn)
        dfm=df[m]
        dfm.plot(x='dz',
                 y='wrms',
                 yerr='wrmserr',
                 loglog=True,
                 label=("sn=%g"%sn),
                 ax=ax)
    ax.xaxis.set_ticks_position('both')
    ax.yaxis.set_ticks_position('both')
    #for tax in [ax.get_xaxis(), ax.get_yaxis()]:
    #tax.set_major_formatter(matplotlib.ticker.ScalarFormatter())    
    plt.ylabel("$\epsilon\,$(rad)")
    plt.xlabel("Defocus (m)")    
    plt.savefig("plots/errvsdz.png")
    plt.close()
    
