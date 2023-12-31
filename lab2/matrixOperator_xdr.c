/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "matrixOperator.h"

bool_t
xdr_Matrix (XDR *xdrs, Matrix *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->nRows))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->nColumns))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->data, 100,
		sizeof (double), (xdrproc_t) xdr_double))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Massage (XDR *xdrs, Massage *objp)
{
	register int32_t *buf;

	 if (!xdr_Matrix (xdrs, &objp->A))
		 return FALSE;
	 if (!xdr_Matrix (xdrs, &objp->B))
		 return FALSE;
	return TRUE;
}
