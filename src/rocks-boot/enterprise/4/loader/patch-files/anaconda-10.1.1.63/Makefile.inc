#
# define destination locations
#
PYTHONLIBDIR = /usr/lib/anaconda
RUNTIMEDIR = /usr/lib/anaconda-runtime
ANACONDADATADIR = /usr/share/anaconda
PYTHON = python2.3
PYTHONINCLUDE = /usr/include/$(PYTHON)

ARCH := $(patsubst i%86,i386,$(shell uname -m))
ARCH := $(patsubst sparc%,sparc,$(ARCH))
ARCH := $(patsubst ppc%,ppc,$(ARCH))
FULLARCH := $(shell uname -m)

ifneq (,$(filter ppc64 x86_64 s390x,$(FULLARCH)))
LIBDIR = lib64
else
LIBDIR = lib
endif

# diet defines
USEDIET=0
ifeq (i386, $(ARCH))
USEDIET=1
# SDSC - hardcode DIET off
USEDIET=0
# end
endif