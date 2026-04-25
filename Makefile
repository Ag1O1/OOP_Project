CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude
TARGET = program

# Look for .cpp files in src/
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Rule to build object files from src/ to obj/
obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
obj:
	mkdir -p obj

clean:
	rm -rf obj $(TARGET)

run: $(TARGET)
	./$(TARGET)
