# Compiler and flags
CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++17 
AR := ar
ARFLAGS := -rcs

# Directories
SRC_DIR := srcs
OBJ_DIR := obj
TEMPLATE_DIR := templates
INCLUDE_DIR := Includes
LIB_NAME := libftpp.a

# Source files and object files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Header dependencies
HEADERS := $(wildcard $(TEMPLATE_DIR)/*.hpp $(INCLUDE_DIR)/*.hpp)

# Default target
all: $(LIB_NAME)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(TEMPLATE_DIR) -I$(INCLUDE_DIR) -c $< -o $@

# Create static library
$(LIB_NAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

# Test rule: make testname compiles library, compiles test, and runs it
%: tests/%.cpp $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -I. -I$(TEMPLATE_DIR) -I$(INCLUDE_DIR) $< -o $@ -L. -lftpp
	valgrind ./$@
	rm $@

# Clean generated files
clean:
	rm -f $(OBJECTS)
	rm -rf $(OBJ_DIR)

# Clean object files and library
fclean: clean
	rm -f $(LIB_NAME)

# Rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re
