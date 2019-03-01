.SUFFIXES:
ROOT := ../

ifeq ($(MAKELEVEL), 0)
include $(ROOT)/config.mk
endif

EXES := integrate_test.x
EXES := $(EXES:%=$(EXE_PREFIX)/%)

.PHONY: all clean clean-all
all: $(EXES)

clean:
	rm -rf $(BUILD_PREFIX)

clean-all:
	make -C test clean MAKELEVEL=0
	rm -rf $(BUILD_PREFIX)

$(EXE_PREFIX)/integrate_test.x: integrate_test.cpp $(BUILD_PREFIX)/integrate.o
	@mkdir -p $(EXE_PREFIX)
	$(CXX) -o $@ $(LIBS:%=-l%) $(CXXFLAGS) $^

$(BUILD_PREFIX)/integrate.o: $(ROOT)/integrate.cpp
	$(eval LIBS := $(LIBS) $(integrate_LIBS))
	make -C $(ROOT) build
