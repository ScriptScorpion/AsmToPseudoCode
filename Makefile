CXX := g++
CXXFLAGS := -std=c++17
TARGET := pseudo     
FILE := src/convert.cpp

compile:
	@$(CXX) $(CXXFLAGS) $(FILE) -o $(TARGET)
