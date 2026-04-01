# to be overriden when building on android/termux (make prefix=... target)
# https://www.gnu.org/software/make/manual/html_node/Overriding.html
prefix ?= /usr/local

LIBRARY_NAME := stb-utils
INCLUDE_DEST_DIR := $(prefix)/include/$(LIBRARY_NAME)
LIBRARY_DEST_DIR := $(prefix)/lib

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
LIBRARY_BASENAME := lib$(LIBRARY_NAME).a
LIBRARY_FILE := $(BUILD_DIR)/$(LIBRARY_BASENAME)

SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS_FILES := $(OBJECTS_FILES:.o=.d)

CPPFLAGS := -I$(INCLUDE_DIR)
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -MMD

# https://gist.github.com/basharam/9511906
$(LIBRARY_FILE): $(OBJECTS_FILES)
	ar -r $@ $^

# note that object files within a static library don't need to be linked now
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o$@ $<

$(BUILD_DIR):
	mkdir -p $@

-include $(DEPS_FILES)

.PHONY: clean install uninstall
clean:
	rm -rf $(BUILD_DIR)

# install & uninstall targets make it easy to link against this lib
install:
	install -m 644 -D -t $(INCLUDE_DEST_DIR) $(INCLUDE_DIR)/*.hpp $(INCLUDE_DIR)/*.h
	install -m 644 -t $(LIBRARY_DEST_DIR) $(LIBRARY_FILE)

uninstall:
	rm -rf $(INCLUDE_DEST_DIR)
	rm -rf $(LIBRARY_DEST_DIR)/$(LIBRARY_BASENAME)
