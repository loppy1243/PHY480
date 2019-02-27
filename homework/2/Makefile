.SUFFIXES:

ifeq ($(MAKELEVEL), 0)
include config.mk
endif

OMP_TARGETS := all build test
OBJS := integrate.o
OBJS := $(OBJS:%=$(BUILD_PREFIX)/%)

.PHONY: build test clean $(OMP_TARGETS:%=%_omp)
build: $(OBJS)

test:
	make -C test

define OMP_TARGET_template =
$1_omp: CXXFLAGS := $$(CXXFLAGS) -fopenmp -DOMP
$1_omp: $1

endef
$(foreach target,$(OMP_TARGETS),$(eval $(call OMP_TARGET_template,$(target))))

clean:
	rm -rf $(BUILD_PREFIX)

$(BUILD_PREFIX)/%.o: %.cpp
	@mkdir -p $(BUILD_PREFIX)
	$(CXX) -o $@ $(CXXFLAGS) -c $<
