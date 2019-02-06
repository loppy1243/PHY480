CXX := g++

TARGETS := area sum_order
SRC_DIR := ./
BUILD_DIR := build

all : $(TARGETS)

.PHONY: $(TARGETS)
$(foreach target,$(TARGETS),$(target) : $(BUILD_DIR)/bin/$(target).x)

$(BUILD_DIR)/bin/%.x : $(SRC_DIR)/%.cpp $(BUILD_DIR)
	$(CXX) -o $@ $<

$(BUILD_DIR) :
	@mkdir -p $(BUILD_DIR)/bin

.PHONY: clean
clean :
	rm -rf $(shell find $(BUILD_DIR) -not path 'build' -not -path '$(BUILD_DIR)/bin*')

.PHONY: clean-all
clean-all :
	rm -rf build
