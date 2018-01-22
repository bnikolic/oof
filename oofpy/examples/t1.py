from oofpy import zernike, amp

g=numpy.moveaxis(numpy.mgrid[-2:2:128j, -2:2:128j], 0, -1)
z=zernike.eval(2,0,g)
a=amp.gauss(0,0,1,1,0,0,g) * amp.dish(1.0,0, g)
                 
