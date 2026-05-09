# BST Word Frequency Tool
# Gabriel Speer — 2023

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET  = driver
SRCS    = driver.cpp BST.cpp Node.cpp
OBJS    = $(SRCS:.cpp=.o)

.PHONY: default clean

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp BST.h Node.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) $(TARGET) $(OBJS) *~ \#*\#
