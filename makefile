# binary and image names
TARGET_EXEC := raytracing
TARGET_IMG := raytracing.ppm

# directories
SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin
IMG_DIR := ./img

# find all source and header files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
HDRS := $(wildcard $(SRC_DIR)/*.hpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# flags
CXX = g++
CPPFLAGS =
CXXFLAGS = -g
LDFLAGS =

# output image
all: $(BIN_DIR)/$(TARGET_EXEC)
	@mkdir -p $(IMG_DIR)
	$(BIN_DIR)/$(TARGET_EXEC) > $(IMG_DIR)/$(TARGET_IMG)

# link
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# compile objects
$(OBJS): $(SRCS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# clean
.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR) $(IMG_DIR)
