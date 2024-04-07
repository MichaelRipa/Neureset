# Set this for your local system
REPOPATH=/home/student/Programs/Neureset

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -I $(REPOPATH)/headers

# Source and object files
SRCDIR = $(REPOPATH)/src/
SOURCES = $(wildcard $(SRCDIR)*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)%.cpp=%.o)

# Executable name
EXEC = neureset

# Rule to make the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to make object files
%.o: $(SRCDIR)%.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule
clean:
	rm -f $(OBJECTS) $(EXEC)
