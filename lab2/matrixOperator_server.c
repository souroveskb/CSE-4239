/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "matrixOperator.h"

Matrix *addition_1_svc(Massage *argp, struct svc_req *rqstp)
{
	static Matrix  result;
	puts("Addition function called.");
	
	Matrix A = argp->A;
    Matrix B = argp->B;

    result.nRows = A.nRows;
    result.nColumns = A.nColumns;

    for(int i = 0, k = 0; i < A.nRows; i++) {
        for(int j = 0; j < A.nColumns; j++, k++) {
            result.data[k] = A.data[k] + B.data[k];
        }
    }

	return &result;
}

Matrix *multiplication_1_svc(Massage *argp, struct svc_req *rqstp)
{
	static Matrix  result;
	puts("Multiplication function called.");

    Matrix A = argp->A;
    Matrix B = argp->B;

    result.nRows = A.nRows;
    result.nColumns = B.nColumns;

    for(int i = 0; i < A.nRows; i++) {
        for(int j = 0; j < B.nColumns; j++) {
            result.data[i * B.nColumns + j] = 0;
            for(int k = 0; k < A.nColumns; k++) {
                result.data[i * B.nColumns + j] += (A.data[i * A.nColumns + k] * B.data[k * B.nColumns + j]);
            }
        }
    }
	return &result;
}

Matrix *transpose_1_svc(Massage *argp, struct svc_req *rqstp)
{
	static Matrix  result;

	puts("Transpose Matrix called");

	// Matrix M = argp->A;

	result.nRows = argp->A.nColumns;
	result.nColumns = argp->A.nRows;

	for (int i = 0, k = 0; i < result.nRows; i++){
		for (int j = 0; j < result.nColumns; j++, k++){
			result.data[k] = argp->A.data[k];
		}
	}

	return &result;
}


double determinants(double arr[], int n)
{
    if(n == 1) {
        return arr[0];
    }

    double ret = 0;
    double new_arr[(n-1)*(n-1)];
    for(int i = 0; i < n; i++) {
        for(int j = n, k = 0; j < n*n; j++) {
            if(j % n == i) continue;
            new_arr[k++] = arr[j];
        }
        if(i & 1) {
            ret -= arr[i] * determinants(new_arr, n-1);
        } else {
            ret += arr[i] * determinants(new_arr, n-1);
        }
    }
    return ret;
}


Matrix *inverse_1_svc(Massage *argp, struct svc_req *rqstp)
{
	static Matrix  result;
	Matrix M = argp->A;	

	puts("Inverse function is called");

    double det = determinants(M.data, M.nRows);

    if(det == 0) {
        printf("Determinants can't be zero.\n");
    	result.nColumns = result.nRows = 0;
        return &result;
    }
    result.nColumns = result.nRows = M.nRows;

	double cofactor[M.nRows * M.nColumns];
	double new_arr[M.nRows * M.nColumns];

    for(int i = 0; i < M.nRows * M.nRows; i++) {
        for(int j = 0, k = 0; j < M.nRows * M.nRows; j++) {
            if((i % M.nRows == j % M.nRows) || (i / M.nRows == j / M.nRows)) continue;
            new_arr[k++] = M.data[j];
        }
        cofactor[i] = (i & 1 ? -1 : 1) * determinants(new_arr, M.nRows - 1);
    }

    for(int i = 0, j = 0; i < M.nRows * M.nRows; i++) {
        result.data[j++] = cofactor[i];
    }

    // printf("Inv : %lf\n", inv);

    for(int i = 0; i < M.nRows * M.nRows; i++) {
        result.data[i] /= det;
    }

	return &result;
}
