CXX := g++

.PHONY: all plots

all: plots derivative_test.x
plots: derivative_test_plt.pdf

derivative_test.x: derivative_test.o
	$(CXX) -o $@ -lgsl $^

derivative_test_plt.pdf: derivative_test.plt derivative_test.dat
	gnuplot $<

derivative_test.dat: derivative_test.x
	./derivative_test.x

%.o: %.cpp
	$(CXX) -c $<
