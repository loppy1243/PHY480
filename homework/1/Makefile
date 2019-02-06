CC := gcc

TARGETS := area
SRC_DIR := ./
BUILD_DIR := build

all : $(TARGETS)
$(TARGETS) : $(TARGETS:$(BUILD_DIR)/bin/%.x)

$(BUILD_DIR)/bin/%.x : $(BUILD_DIR)/%.o
	$(CC) -o $% $<

$(BUILD_DIR)/%.o : $(BUILD_DIR) %.cpp
	$(CC) -o $% -c $<

$(BUILD_DIR) :
	@mkdir -p $(BUILD_DIR)/bin

clean :
	rm -rf $(shell find $(BUILD_DIR) -not path 'build' -not -path '$(BUILD_DIR)/bin*')

clean-all :
	rm -rf build
