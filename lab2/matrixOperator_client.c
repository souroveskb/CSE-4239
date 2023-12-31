/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "matrixOperator.h"


void inputMatrix(Matrix* M)
{
    printf("Enter Matrix :\n");
    for(int i = 0, k = 0; i < M->nRows; i++) {
        for(int j = 0; j < M->nColumns; j++, k++) {
            scanf("%lf", &(M->data[k]));
        }
    }
}


void printMatrix(Matrix* M){

	printf("Result Matrix :\n");
    for(int i = 0, k = 0; i < M->nRows; i++) {
        for(int j = 0; j < M->nColumns; j++, k++) {
            printf("%.2lf ", (M->data[k]));
        }
		printf("\n");
    }
}



void matrix_operations_1(char *host, int op)
{
	CLIENT *clnt;
	Matrix  *result_1;
	Massage  addition_1_arg;
	Matrix  *result_2;
	Massage  multiplication_1_arg;
	Matrix  *result_3;
	Massage  transpose_1_arg;
	Matrix  *result_4;
	Massage  inverse_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, MATRIX_OPERATIONS, MATRIX_VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	if(op == 1) {

		
		printf("number of rows( <= 10) : ");
		scanf("%d", &(addition_1_arg.A.nRows));
    	printf("number of columns( <= 10) : ");
		scanf("%d", &(addition_1_arg.A.nColumns));

        printf("~~~~~~~~~~First matrix~~~~~~~~~~~\n");
        inputMatrix(&(addition_1_arg.A));

		addition_1_arg.B.nRows = addition_1_arg.A.nRows;
		addition_1_arg.B.nColumns = addition_1_arg.A.nColumns;

        printf("~~~~~~~~~~Second Matrix~~~~~~~~~~\n");
        inputMatrix(&(addition_1_arg.B));

        result_1 = addition_1(&addition_1_arg, clnt);
        if (result_1 == (Matrix *) NULL) {
            clnt_perror (clnt, "call failed");
        }

		printMatrix(result_1);
        

    } else if (op ==2 ){
		
    	printf("number of rows( <= 10) : ");
		scanf("%d", &(multiplication_1_arg.A.nRows));
    	printf("number of columns( <= 10) : ");
		scanf("%d", &(multiplication_1_arg.A.nColumns));


        printf("~~~~~~~~~~First matrix~~~~~~~~~~~\n");
        inputMatrix(&(multiplication_1_arg.A));

		multiplication_1_arg.B.nRows = multiplication_1_arg.A.nRows;
		multiplication_1_arg.B.nColumns = multiplication_1_arg.A.nColumns;

        printf("~~~~~~~~~~Second Matrix~~~~~~~~~~\n");
        inputMatrix(&(multiplication_1_arg.B));
		
		result_2 = multiplication_1(&multiplication_1_arg, clnt);
		if (result_2 == (Matrix *) NULL) {
            clnt_perror (clnt, "call failed");
        }
        
		printMatrix(result_2);
        

    } else if (op == 3){


    	printf("number of rows( <= 10) : ");
		scanf("%d", &(transpose_1_arg.A.nRows));
    	printf("number of columns( <= 10) : ");
		scanf("%d", &(transpose_1_arg.A.nColumns));

		printf("~~~~~~~~Enter The Matrix~~~~~~~~~\n");
        inputMatrix(&(transpose_1_arg.A));

		result_3 = transpose_1(&transpose_1_arg, clnt);
		if (result_3 == (Matrix *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		
		printMatrix(result_3);
	
	} else {

		printf("order of the matrix( <= 10) : ");
		scanf("%d", &(inverse_1_arg.A.nRows));
		inverse_1_arg.A.nColumns = inverse_1_arg.A.nRows;
    	
		printf("~~~~~~~~Enter The Matrix~~~~~~~~~\n");
        inputMatrix(&(inverse_1_arg.A));

		result_4 = inverse_1(&inverse_1_arg, clnt);
		if (result_4 == (Matrix *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		if(result_4->nColumns == 0){
			printf("The determinant is Zero.So inverse of this matrix is not possible!!\n");
		} else{
			printMatrix(result_4);
		}

	}
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		host = "localhost";
		// printf ("usage: %s server_host\n", argv[0]);
		// exit (1);
	} else{
		host = argv[1];
	}

	while(1) {
		int op_id;
		printf("Choose an Operation:\n");
		printf("1.Addition\n2.Multiplication\n3.Transpose\n4.Inverse\n0.Exit\nEnter choice : ");
		scanf("%d", &op_id);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        
        if(op_id >= 1 && op_id <= 4) {
			matrix_operations_1 (host, op_id);
        } else if(op_id == 0) {
            break;
        } else {
            printf("Please enter a valid choice.\n");
        }
    }
exit (0);
}
