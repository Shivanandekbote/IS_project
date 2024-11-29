# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -g

# Libraries to link against
LIBS = -lssl -lcrypto

# Source files and object files
# Source files and object files
SRC = src/main.cpp src/encryption.cpp src/file_io.cpp
OBJ = $(SRC:.cpp=.o)



# Output executable name
EXEC = StorageSecurityProject

# Default target to build the project
all: $(EXEC)

# Rule to create the executable from object files
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LIBS)

# Rule to compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(EXEC)
