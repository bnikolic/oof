# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# June 2007
#
# Utilities to support the use of Kolmogorov utilities in Python


import pybnlib

def GenerateKolmogorov3D( Nx,Ny,Nz,
                          seed=None):

    grid=pybnlib.doubleArray( Nx*Ny*Nz)
    rfn=pybnlib.NormDistZM(1.0)
    if seed != None:
        rfn.reseed(seed)
    pybnlib.Kolmogorov3D( grid, Nx,Ny,Nz, rfn)
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


