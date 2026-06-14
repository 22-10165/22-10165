
TARGET := cluster.exe

CXXFLAGS := -Wall

CXX := g++

# List of source files and corresponding object files
SRC := $(wildcard *.cxx)
OBJ := $(SRC:.cxx=.o)

# Pattern rule: compile .cxx to .o
%.o: %.cxx *.h Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ) Makefile
	$(CXX) $(OBJ) -o $@

clean:
	rm -f $(TARGET) $(OBJ) a.out
