# compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# SFML library
SFML_LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# target
TARGET = chessmaster

# file
SRCDIR = src

# source
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

all: clean $(TARGET)

# compile & link
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(SFML_LIBS)

# clean
clean:
	rm -f $(TARGET)

.PHONY: all clean
