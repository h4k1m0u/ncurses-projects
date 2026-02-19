# For more details about this Makefile, refer to: https://github.com/h4k1m0u/sdl-platformer/
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build

SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS_FILES := $(OBJECTS_FILES:.o=.d)

IMAGES_SRC_DIR := images
IMAGES_SRC_FILES := $(shell find $(IMAGES_SRC_DIR)/*.png)
IMAGES_DEST_DIR := $(BUILD_DIR)/images
IMAGES_DEST_FILES := $(IMAGES_SRC_FILES:$(IMAGES_SRC_DIR)/%.png=$(IMAGES_DEST_DIR)/%.png)

# link against ncursesw to support wide-characters (unicode)
# _XOPEN_SOURCE_EXTENDED macro defined to make ncursesw functions work on termux/Android
CPPFLAGS := -I$(INCLUDE_DIR) -D_XOPEN_SOURCE_EXTENDED
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -MMD
# LDFLAGS := -lncurses
LDFLAGS := -lncursesw

$(BUILD_DIR)/main: $(OBJECTS_FILES)
	$(CXX) $^ -o$@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o$@ $<

$(BUILD_DIR):
	mkdir -p $@

-include $(DEPS_FILES)

.PHONY: clean images
clean:
	rm -rf $(BUILD_DIR)

# Copy modified images only to build folder
images: $(IMAGES_DEST_FILES)

$(IMAGES_DEST_DIR)/%.png: $(IMAGES_SRC_DIR)/%.png | $(IMAGES_DEST_DIR)
	cp $< $@

$(IMAGES_DEST_DIR):
	mkdir -p $@
