# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
#
# June 2007
#
# Utilities to support the use of Kolmogorov utilities in Python


import pybnlib

def GenerateKolmogorov3D( Nx,Ny,Nz):

    grid=pybnlib.doubleArray( Nx*Ny*Nz)
    rfn=pybnlib.NormDistZM(1.0)
    pybnlib.Kolmogorov3D( grid, Nx,Ny,Nz, rfn)
    return ( grid,
             ( Nx,Ny,Nz) )


