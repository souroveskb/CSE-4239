/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "matrixOperator.h"

bool_t xdr_Matrix (XDR *xdrs, Matrix *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->nRows))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->nColumns))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->data, 1000,
		sizeof (float), (xdrproc_t) xdr_float))
		 return FALSE;
	return TRUE;
}

bool_t xdr_Input (XDR *xdrs, Input *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->numOfMatrices))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->matrices, 2,
		sizeof (Matrix), (xdrproc_t) xdr_Matrix))
		 return FALSE;
	return TRUE;
}

bool_t xdr_Output (XDR *xdrs, Output *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_Matrix (xdrs, &objp->result))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->errorCode))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->errorMessage, 50,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}