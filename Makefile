# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -I src

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Output binary
TARGET := $(BUILD_DIR)/social_graph_app

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Build successful!"

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
	@echo "🧹 Cleaned build files."

# Run
run: all
	@echo "🚀 Running program..."
	./$(TARGET)
