CXX := g++

TARGETS := area sum_order
SRC_DIR := ./
BUILD_DIR := build

all: $(TARGETS)

.PHONY: $(TARGETS)
define TARGET_RULE =
$(1) : $(BUILD_DIR)/bin/$(1).x
endef
$(foreach target,$(TARGETS),$(eval $(call TARGET_RULE,$(target))))

$(BUILD_DIR)/bin/%.x: $(SRC_DIR)/%.cpp $(BUILD_DIR)
	$(CXX) -o $@ $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)/bin

.PHONY: clean
clean:
	rm -rf $(shell find $(BUILD_DIR) -not path 'build' -not -path '$(BUILD_DIR)/bin*')

.PHONY: clean-all
clean-all:
	rm -rf build
