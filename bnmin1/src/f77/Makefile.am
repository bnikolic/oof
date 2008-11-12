
lib_LTLIBRARIES = libminpda.la 



if GFORTRAN
libminpda_la_FFLAGS= -ff2c -fno-range-check
else
libminpda_la_FFLAGS= -ff2c 
endif

libminpda_la_SOURCES= pda_d1mach.f  \
			pda_dpmpar.f \
			pda_enorm.f \
			pda_fdjac2.f \
			pda_lmdif.f \
			pda_lmpar.f \
			pda_qrfac.f \
			pda_qrsolv.f

