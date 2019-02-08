CXX := g++

TARGETS := area sum_order bessel
PLOT_TARGETS := sum_order bessel
SRC_DIR := ./
BUILD_DIR := build
PLOT_DIR := plots

all: $(TARGETS)

.PHONY: $(TARGETS)
define TARGET_RULE =
$(1) : $(BUILD_DIR)/bin/$(1).x
endef
$(foreach target,$(TARGETS),$(eval $(call TARGET_RULE,$(target))))

plots : $(PLOT_TARGETS:%=plot-%)
.PHONY: $(PLOT_TARGETS:%=plot-%)
define PLOT_TARGET_RULE =
plot-$(1) : $(PLOT_DIR)/$(1:%=%.pdf)
endef
$(foreach target,$(PLOT_TARGETS),$(eval $(call PLOT_TARGET_RULE,$(target))))

$(BUILD_DIR)/bin/%.x: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(PLOT_DIR)/%.pdf: $(SRC_DIR)/%.plt | mk_plot_dir
	gnuplot $(PLOTFLAGS) $($(*F)-plotflags) $<
	@mv $*.pdf $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)/bin

# Since plots is the name of target, it conflicts with PLOT_DIR=plots. So we do this instead.
mk_plot_dir:
	@mkdir -p $(PLOT_DIR)

.PHONY: clean
clean:
	@rm -rf $(shell find $(BUILD_DIR) -not path 'build' -not -path '$(BUILD_DIR)/bin*')

.PHONY: clean-plots
clean-plots:
	@rm -rf plots

.PHONY: clean-all
clean-all:
	@rm -rf build
	@rm -rf plots
