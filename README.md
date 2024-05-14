# SPAxb_COO2CSR
This code reads a matrix in CO-Ordinate (COO) format and writes the output in Compressed Sparse Row (CSR) format.
A sample sparse matrix of dimension 10x10 in the COO format ("row index" "column index" "matrix value") is provided in the folder "/include/". The sparse matrix is generated using MATLAB and function to generate the same is also provide in the parent folder. After execution of the code, a corresponding sparse matrix in the CSR format ("column index" "matrix values" "row pointer") is generated in the "/output/" folder. The dimensions of the arrays are given below:
```
Arrays     size
ROW         nnz
COL         nnz
VAL         nnz
ROW_ptr     n+1
```

Here 'nnz' is the number of non-zero entries in the sparse matrix and 'n' is the matrix dimension (n=10 for the given matrix).

Code execution:
---------------
- CMake is used for compilation of the code although it is unnecessary.
- Once compiled the following commandline execution must be provided:
  ```
  ./COO2CSR "<Path to Mat_COO.dat input file>" "<Path to Mat_CSR.dat output file>" MATSTART_1
  ```
  
- In the above execution commandline "MATSTART_1" is provided if the sparse matrix is generated using MATLAB as MATLAB matrix entries start from 1 not 0. If matrix entries start from 0 then MATSTART_0 should be provided as the 4th     
  commandline argument.
