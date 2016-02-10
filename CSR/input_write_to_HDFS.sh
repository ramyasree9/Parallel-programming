hadoop fs -rm -r Input-matrix-csr.txt
hadoop fs -rm -r Input-vector-csr.txt
hadoop fs -put Input-mat-vect-csr.txt Input-matrix-csr.txt
hadoop fs -put Input-vector.txt Input-vector-csr.txt
 
