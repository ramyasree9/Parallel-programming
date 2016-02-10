include ./../../BLAS/CBLAS/Makefile.in
Path=/home/ramyab/BLAS/CBLAS/include/
all:run
run: Mat-vec-mul.c
	$(CC) -c $(CFLAGS) -I$(Path) Mat-vec-mul.c
	$(LOADER) -o run Mat-vec-mul.o $(CBLIB) $(BLLIB)
clean: 
	rm run Mat-vec-mul.o
