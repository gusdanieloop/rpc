/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "hw.h"

bool_t
xdr_params (XDR *xdrs, params *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)&objp->conteudo, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->usuario, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->contador))
		 return FALSE;
	return TRUE;
}