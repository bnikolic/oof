# Plotting of retrieval error results

import os
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
plt.rc("axes", prop_cycle=(cycler("color", ['r', 'g', 'b', 'k', 'y', 'c'  ] )+
                           cycler("linestyle", ["-","--","-.",":", "-", "--"])))
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

def mkfig():
    return plt.figure(figsize=(5, 4.0), dpi=200)


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
    fig=mkfig()
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
    fig=mkfig()
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
    ax.set_xlim(1e-4, 1e-2)
    ax.set_ylim(1e-6, 1e-4)        
    plt.ylabel(r"$\epsilon_{\mathrm{HWFE}}\,$(m)")
    plt.xlabel("(Noise per beam) / (Peak signal)")    
    plt.savefig("plots/errvsdecim%s.png" % postf)
    plt.close()    


def plotvsdz(df, dzmax=None, postf=""):
    fig=mkfig()
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
    ax.set_ylim(1e-6, 50e-6)
    ax.xaxis.set_ticks_position('both')
    ax.yaxis.set_ticks_position('both')
    plt.ylabel(r"$\epsilon_{\mathrm{HWFE}}\,$(m)")
    plt.xlabel("Defocus (m)")    
    plt.savefig("plots/errvsdz-%s.png" % postf)
    plt.close()


def plotvsnoisedz(df, postf=""):
    fig=mkfig()
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
    plt.savefig("plots/errvsnoisedz%s.png" % postf)
    plt.close()
    

if 1:
    df=wrmssim("v2-snsim-100")
    plotvsnoise(df, "100dz-v2")
    df2=wrmssim("v2-snsim-10")
    plotvsnoise(df2, "10dz-v2")    
    df3=wrmssim("v2-snsim-50")
    plotvsnoise(df3, "50dz-v2")

if 1:    
    df4=wrmssim("v2-dz")
    df5=wrmssim("v2-dz035")
    plotvsdz(df4, postf="11-v2")
    plotvsdz(df5, 0.1, postf="035-v2")

if 1:
    df51=wrmssim("v2-dz073")
    plotvsdz(df51, postf="073-v2")

if 1:    
    df6=wrmssim("v2-simdecim")
    df7=wrmssim("v2-simdecimdz10")

    plotvsdecim(df6, "v2")
    plotvsdecim(df7, "dz10-v2")

if 1:
    df77=wrmssim("v2-simdecim-50")
    plotvsdecim(df77, "dz50-v2")    

if 1:
    df8=wrmssim("v2-simdznoise")
    plotvsnoisedz(df8, "-v2")
