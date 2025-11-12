# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++23 -O2 -Wall -static -static-libgcc -static-libstdc++ -I src

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Output binary (.exe for Windows)
TARGET := $(BUILD_DIR)/social_graph_app.exe

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(CXXFLAGS)
	@echo "✅ Build successful! → $(TARGET)"

# Compile each .cpp into .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
	@echo "🧹 Cleaned build files."

# Run program
run: all
	@echo "🚀 Running program..."
	./$(TARGET)
