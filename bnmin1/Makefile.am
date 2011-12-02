if PYBIND_OPT
   MAYBE_DIRS = pybind
else
   MAYBE_DIRS = 
endif 

if BUILDTESTS_OPT
   MAYBE_DIRS += test
endif 

SUBDIRS = src $(MAYBE_DIRS) 

EXTRA_DIST = CMakeLists.txt src/CMakeLists.txt

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA= bnmin1.pc
