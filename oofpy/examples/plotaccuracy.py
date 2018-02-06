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


def wrmssim():
    "Load simulation data"
    i=0
    res=[]
    while os.path.exists("sim/sn%i.json" %i):
        p=json.load(open("sim/sn%i.json" %i))
        xx=numpy.load("sim/sn%i-ret.npz" %i)['arr_0']
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
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)
    ax.xaxis.set_ticks_position('bottom')
    ax.yaxis.set_ticks_position('left')    
    for tax in [ax.get_xaxis(), ax.get_yaxis()]:
        tax.set_major_formatter(matplotlib.ticker.ScalarFormatter())    
    plt.ylabel("$\epsilon\,$(rad)")
    plt.xlabel("(Noise per beam) / (Peak signal)")    
    plt.savefig("plots/errvsnoise.png")
    plt.close()
