.SUFFIXES:

# Include common variables
ifeq ($(MAKELEVEL), 0)
include config.mk
endif

OMP_TARGETS := all build test
OBJS := integrate.o
OBJS := $(OBJS:%=$(BUILD_PREFIX)/%)

.PHONY: build plots test clean $(OMP_TARGETS:%=%_omp)
# Build object files
build: $(OBJS)

# Call test/Makefile
test:
	make -C test

## Make for each T in OMP_TARGETS the target T_omp which build with OpenMP enabled
define OMP_TARGET_template =
$1_omp: CXXFLAGS := $$(CXXFLAGS) -fopenmp -DOMP
$1_omp: $1

endef
$(foreach target,$(OMP_TARGETS),$(eval $(call OMP_TARGET_template,$(target))))

plots: integrate_test_plt.pdf
integrate_test_plt.pdf: integrate_test.dat test/integrate_test.plt
	gnuplot test/integrate_test.plt

clean:
	rm -rf $(BUILD_PREFIX)

$(BUILD_PREFIX)/%.o: %.cpp
	@mkdir -p $(BUILD_PREFIX)
	$(CXX) -o $@ $(CXXFLAGS) -c $<
