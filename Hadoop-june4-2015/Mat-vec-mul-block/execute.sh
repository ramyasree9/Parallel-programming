hadoop fs -rm -r output-block
hadoop fs -rm -r output-mat-vect-mul-block
hadoop jar Mat_vect_mul_block.jar Mat_vect_mul_block Input-to-mat-vect-mul-block.txt output-block output-mat-vect-mul-block 1024 16
