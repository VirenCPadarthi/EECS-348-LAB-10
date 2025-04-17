CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = lab10
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(SRC)

clean:
	rm -f $(TARGET)
