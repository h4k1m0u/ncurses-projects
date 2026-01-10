# For more details about this Makefile, refer to: https://github.com/h4k1m0u/sdl-platformer/
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build

SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS_FILES := $(OBJECTS_FILES:.o=.d)

CPPFLAGS := -I$(INCLUDE_DIR)
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -MMD
# LDFLAGS := -lncurses
LDFLAGS := -lncursesw

$(BUILD_DIR)/main: $(OBJECTS_FILES)
	$(CXX) $^ -o$@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o$@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS_FILES)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
