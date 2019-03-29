CXX := g++

BINS := derivative_test.x eigen_basis.x
DATA := derivative_test.dat eigen_basis.dat
PLOTS := derivative_test_plt.pdf eigen_basis_plt.pdf

.PHONY: all binaries plots plots_only data

binaries: derivative_test.x eigen_basis.x
all: binaries plots
plots: derivative_test_plt.pdf eigen_basis_plt.pdf
data: derivative_test.dat eigen_basis.dat

derivative_test.x: derivative_test.o
	$(CXX) -o $@ -lgsl $^

eigen_basis.x: eigen_basis.o harmonic_oscillator.o
	$(CXX) -o $@ -lgsl $^

derivative_test_plt.pdf: derivative_test.plt derivative_test.dat
	gnuplot $<

eigen_basis_plt.pdf: eigen_basis.plt eigen_basis.dat
	gnuplot $<

derivative_test.dat: derivative_test.x
	./derivative_test.x

eigen_basis.dat: eigen_basis.x
	is_first=1; \
	for b in 0.9 1.0; do \
		for d in 1 5 10 20; do \
			if (( $$is_first )); then flag=-o; is_first=0; else flag=-a; fi; \
			./eigen_basis.x $$flag eigen_basis.dat 1 $$b $$d; \
		done; \
	done

%.o: %.cpp
	$(CXX) -c $<
