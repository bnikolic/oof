# Telescope Geometry routines
import numpy

def primeF(F, g):
    """Compute phase change due to unit axial shift aprime focus"""
    R=numpy.hypot(g[...,0], g[...,1])
    a=R/(2*F)
    return (1-a**2)/(1+a**2)

