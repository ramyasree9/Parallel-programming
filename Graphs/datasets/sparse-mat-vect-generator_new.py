
#!/usr/bin/env python
''' this is simple python program to generate sparse matrix and store them into-file
	input 1. sparsitiy ( which mean how many column in a single row of the generated matrix has non zero value
	input 2. Dimension of the matrix - which mean , the script will always generate square matrix.
	input 3. Output file name in which matrix will be stored.

'''
from math import *
import random

def writeMatrix(sparsity,mat_M_Row_Dim,mat_M_Column_Dim,vect_V_Dim,matFileName):
	# open file code 
	matFile = open(matFileName, 'w+')
	#matFile.write(str(sparsity)+'\n')
	#matFile.write(str(matDim)+'\n')
        i=-1
	j=-1
	for eachRow in range(mat_M_Row_Dim): 
		sparseCount = 0
                i=i+1
		for eachCol in range(mat_M_Column_Dim):
			j=j+1
			flag = random.randint(1,100)%2
			boundaryCond = (sparsity - sparseCount - 1) - (mat_M_Column_Dim - 1 - eachCol ) 
			if( ((sparseCount < sparsity) and flag == 0) or ( boundaryCond == 0)):
				sparseCount = sparseCount + 1
				matFile.write( 'M,'+str(i)+','+str(j)+','+str(random.randint(1,10))+'.0' )
			else:
				matFile.write('M,'+str(i)+','+str(j)+',0.0')
			matFile.write('\n')
		j=-1

	i=-1
	j=-1
	
	for eachCol in range(vect_V_Dim):
			i=i+1
			matFile.write( 'V,'+str(i)+','+str(random.randint(1,10))+'.0  ' )
			matFile.write('\n')
	matFile.close()

def readInput():
	sparsity = int(raw_input("Enter matrix sparsity : "))
	mat_M_Row_Dim = int(raw_input("Enter matrix M Row dimension :"))
	mat_M_Column_Dim = int(raw_input("Enter matrix M Column dimension :"))
	vect_V_Dim = int(raw_input("Enter vector V Row dimension :"))
	#mat_B_Column_Dim = int(raw_input("Enter matrix B Column dimension :")) 
	matFileName = "./sparseinput.txt"
	return sparsity, mat_M_Row_Dim, mat_M_Column_Dim, vect_V_Dim, matFileName

if __name__ == '__main__':
	sparsity, mat_M_Row_Dim, mat_M_Column_Dim, vect_V_Dim, matFileName = readInput()
	writeMatrix(sparsity, mat_M_Row_Dim, mat_M_Column_Dim, vect_V_Dim, matFileName)
