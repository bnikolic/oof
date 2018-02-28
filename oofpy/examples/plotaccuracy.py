# Plotting of retrieval error results

import math
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

plotstyle={ "capsize": 4, "capthick": 0.5, "elinewidth": 0.5}


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
        p["hwfe"] = p["wrms"] * p["wl"] / (2*math.pi) / 2
        p["hwferr"] = p["wrmserr"] * p["wl"] / (2*math.pi) / 2         
        res.append(p)
        i+=1
    return pandas.DataFrame(res)


def plotvsnoise(df, postf=""):
    fig=plt.figure(figsize=(7,5), dpi=150)
    ax=fig.add_subplot(1, 1, 1)
    for nzern in range(4,9):
        m=(df["nzern"]==nzern)
        dfm=df[m]
        dfm.plot(x='noisesn',
                 y='hwfe',
                 yerr='hwferr',
                 loglog=True,
                 label=("Maximum Zernike order=%i"%nzern),
                 ax=ax,
                 **plotstyle)
    ax.xaxis.set_ticks_position('both')
    ax.yaxis.set_ticks_position('both')    
    plt.ylabel(r"$\epsilon_{\mathrm{HWFE}}\,$(m)")
    plt.xlabel("(Noise per beam) / (Peak signal)")    
    plt.savefig("plots/errvsnoise-%s.png" % postf)
    plt.close() 

def plotvsdecim(df, postf=""):
    fig=plt.figure(figsize=(7,5), dpi=150)
    ax=fig.add_subplot(1, 1, 1)
    for d in [False, 2, 3, 4, 5]:
        m=(df["decimate"]==d)
        dfm=df[m]
        dfm.plot(x='noisesn',
                 y='hwfe',
                 yerr='hwferr',
                 loglog=True,
                 label=("decimate %s" % d),
                 ax=ax,
                 **plotstyle)
    ax.xaxis.set_ticks_position('both')
    ax.yaxis.set_ticks_position('both')    
    ax.set_title("Accuracy for decimated observation")
    plt.ylabel(r"$\epsilon_{\mathrm{HWFE}}\,$(m)")
    plt.xlabel("(Noise per beam) / (Peak signal)")    
    plt.savefig("plots/errvsdecim%s.png" % postf)
    plt.close()    


def plotvsdz(df, dzmax=None, postf=""):
    fig=plt.figure(figsize=(7,5), dpi=150)
    ax=fig.add_subplot(1, 1, 1)
    for sn in (1e-3, 5e-3, 1e-2):
        m=(df["noisesn"]==sn)
        dfm=df[m]
        dfm.plot(x='dz',
                 y='hwfe',
                 yerr='hwferr',
                 loglog=True,
                 label=("sn=%g"%sn),
                 ax=ax,
                 **plotstyle)
    if dzmax:
        ax.set_xlim(3e-3, dzmax)
    ax.xaxis.set_ticks_position('both')
    ax.yaxis.set_ticks_position('both')
    plt.ylabel(r"$\epsilon_{\mathrm{HWFE}}\,$(m)")
    plt.xlabel("Defocus (m)")    
    plt.savefig("plots/errvsdz-%s.png" % postf)
    plt.close()


def plotvsnoisedz(df):
    fig=plt.figure(figsize=(7,5), dpi=150)
    ax=fig.add_subplot(1, 1, 1)
    for sn in (1e-4, 3e-4, 6e-4, 1e-3, 3e-3, 6e-3):
        m=(df["noisesn"]==sn)
        dfm=df[m]
        dfm.plot(x='noisedz',
                 y='hwfe',
                 yerr='hwferr',
                 loglog=True,
                 label=("sn=%g"%sn),
                 ax=ax,
                 **plotstyle)
    ax.xaxis.set_ticks_position('both')
    ax.yaxis.set_ticks_position('both')
    #for tax in [ax.get_xaxis(), ax.get_yaxis()]:
    #tax.set_major_formatter(matplotlib.ticker.ScalarFormatter())    
    plt.ylabel(r"$\epsilon_{\mathrm{HWFE}}\,$(m)")
    plt.xlabel("Normal error in defocus (m)")    
    plt.savefig("plots/errvsnoisedz.png")
    plt.close()
    

if 0:
    df=wrmssim("v1-snsim-100")
    plotvsnoise(df, "100dz")
    df2=wrmssim("v1-snsim-10")
    plotvsnoise(df2, "10dz")    
    df3=wrmssim("v1-snsim-50")
    plotvsnoise(df3, "50dz")

    df4=wrmssim("v1-dz")
    df5=wrmssim("v1-dz035")
    plotvsdz(df4, postf="11")
    plotvsdz(df5, 0.3, postf="035")

    df6=wrmssim("v1-simdecim")
    df7=wrmssim("v1-simdecimdz10")

    plotvsdecim(df6)
    plotvsdecim(df7, "dz10")
