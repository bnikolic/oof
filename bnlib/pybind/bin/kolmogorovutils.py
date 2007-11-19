# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# June 2007
#
# Utilities to support the use of Kolmogorov utilities in Python


import pybnlib

def GenerateKolmogorov3D( Nx,Ny,Nz,
                          seed=None,
                          opt=pybnlib.KInitialEFB):

    grid=pybnlib.doubleArray( Nx*Ny*Nz)
    rfn=pybnlib.NormDistZM(1.0)
    if seed != None:
        rfn.reseed(seed)
    pybnlib.Kolmogorov3D( grid, Nx,Ny,Nz, rfn, opt)
    return ( grid,
             ( Nx,Ny,Nz) )

def GridToNumarray( gs):

    import numarray

    res=numarray.zeros( gs[1],
                        numarray.Float32)

    Nx,Ny,Nz=gs[1]

    for k in range( Nz):
        for j in range(Ny):
            for i in range(Nx):
                res[i,j,k]= gs[0][k*Nx*Ny+j*Nx+i]

    return res

def MkExtent(g):

    "Return the Extnent3D structure from a grid list with dims in second element"

    Nx, Ny, Nz = g[1]

    ext=pybnlib.Extnent3D()
    ext.i=Nx
    ext.j=Ny
    ext.k=Nz

    return ext


def RandomCubeSFN(cube,
                  s_p,
                  acumlen):

    "Compute the structure function"

    acum= pybnlib.doubleArray( acumlen)
    ns=   pybnlib.size_tArray( acumlen)
    
    pybnlib.RandomSFN( cube[0], cube[1][0], cube[1][1], cube[1][2], s_p, acum, ns, acumlen)

    r=[]
    for i in range(acumlen):
        r.append( (acum[i], ns[i] ))

    return numarray.array( r)
