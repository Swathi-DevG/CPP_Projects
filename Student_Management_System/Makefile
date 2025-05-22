CXX = g++
CXXFLAGS = -Wall -IInc

# Target executable
TARGET = student_app.exe

# Object files
OBJS = main.o Src/student.o

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile main.cpp
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Compile student.cpp
Src/student.o: Src/student.cpp
	$(CXX) $(CXXFLAGS) -c Src/student.cpp -o Src/student.o

# Clean up build files
.PHONY: clean
clean:
	rm -f *.o Src/*.o $(TARGET)