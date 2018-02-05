# Plotting routines

import matplotlib.pyplot as p

def beams(a, fnameout="beams.png"):
    fig=p.figure()
    N=a.shape[0]
    for i in range(N):
        ax=fig.add_subplot(1, N, i+1)
        ax.matshow(a[i].real)
    p.savefig(fnameout)
    p.close()

def screens(a, fnameout="screens.png"):
    fig=p.figure()
    N=a.shape[0]
    for i in range(N):
        ax=fig.add_subplot(1, N, i+1)
        m=ax.imshow(a[i].real)
        p.colorbar(m)
    p.savefig(fnameout)
    p.close()
    
