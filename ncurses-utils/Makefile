LIBRARY_NAME := ncurses-utils
PREFIX := /usr/local
INCLUDE_DEST_DIR := $(PREFIX)/include/$(LIBRARY_NAME)
LIBRARY_DEST_DIR := $(PREFIX)/lib

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
LIBRARY_BASENAME := lib$(LIBRARY_NAME).a
LIBRARY_FILE := $(BUILD_DIR)/$(LIBRARY_BASENAME)

SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS_FILES := $(OBJECTS_FILES:.o=.d)

# link against ncursesw to support wide-characters (unicode)
# _XOPEN_SOURCE_EXTENDED macro defined to make ncursesw functions work on termux/Android
CPPFLAGS := -I$(INCLUDE_DIR) -D_XOPEN_SOURCE_EXTENDED
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -MMD
# LDFLAGS := -lncurses
LDFLAGS := -lncursesw

# https://gist.github.com/basharam/9511906
$(LIBRARY_FILE): $(OBJECTS_FILES)
	ar -r $@ $^

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
	mkdir -p $(INCLUDE_DEST_DIR)
	cp -t $(INCLUDE_DEST_DIR) $(INCLUDE_DIR)/*.hpp
	cp -t $(LIBRARY_DEST_DIR) $(LIBRARY_FILE)

uninstall:
	rm -rf $(INCLUDE_DEST_DIR)
	rm -rf $(LIBRARY_DEST_DIR)/$(LIBRARY_BASENAME)
