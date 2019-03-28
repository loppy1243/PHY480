CXX := g++

.PHONY: all

all: derivative_test.x

derivative_test.x: derivative_test.o
	$(CXX) -o $@ -lgsl $^

%.o: %.cpp
	$(CXX) -c $<
