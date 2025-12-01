# Binary and image names
TARGET_EXEC := raytracing
TARGET_IMG := raytracing.ppm

# Directories
SRC_DIR := src
INC_DIR := $(SRC_DIR)
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
IMG_DIR := $(BUILD_DIR)/img

# Find all source filenames, create object filenames
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
HDRS := $(wildcard $(INC_DIR)/*.hpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

-include $(DEPS)

# Flags
CXX = g++
CPPFLAGS = -I$(INC_DIR) -MMD -MP
CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -pedantic-errors -Wconversion -Wsign-conversion -Wshadow -fdiagnostics-color=auto -Wformat=2 -Wformat-signedness -Wdouble-promotion
LDFLAGS =

# Tooling
FORMAT := clang-format
FORMAT_STYLE := {BasedOnStyle: Chromium, ColumnLimit: 100, IndentWidth: 4, QualifierAlignment: Right, Standard: c++20}
TIDY := clang-tidy
TIDY_CHECKS ?= -*,bugprone-*,cert-*,clang-analyzer-*,concurrency-*,cppcoreguidelines-*,hicpp-*,misc-*,modernize-*,-modernize-use-trailing-return-type,performance-*,portability-*,readability-*

# Output image
.PHONY: all
all: $(BIN_DIR)/$(TARGET_EXEC) | $(IMG_DIR)
	$(BIN_DIR)/$(TARGET_EXEC) > $(IMG_DIR)/$(TARGET_IMG)

# Link
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR) $(IMG_DIR): | $(BUILD_DIR)
	@mkdir -p $@
$(BUILD_DIR):
	@mkdir -p $@

# Format
format:
	$(FORMAT) -i --style='$(FORMAT_STYLE)' $(SRCS) $(HDRS)

# Lint
tidy:
	$(TIDY) -checks=$(TIDY_CHECKS) $(SRCS) $(HDRS) -- $(CPPFLAGS) $(CXXFLAGS)

# Clean
.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
