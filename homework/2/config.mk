# Maybe touch these
export CXX := g++
export CXXFLAGS := -O3 $(CXXFLAGS)
export BUILD_PREFIX := $(CURDIR)/build
export EXE_PREFIX := $(CURDIR)/bin

# Probably don't touch these
export integrate_LIBS := gsl
