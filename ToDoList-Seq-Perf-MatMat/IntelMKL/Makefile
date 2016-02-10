include ./../../Project-Intel-MKL-cpu-Mflops-DGEMM-v0.2/Make.inc

run : Mat-vec-mul.o
	$(CC) -o run Mat-vec-mul.o -L$(CBLAS_LIB) $(CBLAS_FLAGS)
Mat-vec-mul.o: Mat-vec-mul.c
	$(CC) -c $(CCFLAGS) -DMKL_ILP64 -I$(CBLAS_INCLUDE) Mat-vec-mul.c 
clean:
	rm run Mat-vec-mul.o
