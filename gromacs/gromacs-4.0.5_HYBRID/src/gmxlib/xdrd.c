/*
 * $Id: xdrd.c,v 1.17 2006/04/19 09:37:22 lindahl Exp $
 * 
 *                This source code is part of
 * 
 *                 G   R   O   M   A   C   S
 * 
 *          GROningen MAchine for Chemical Simulations
 * 
 *                        VERSION 3.2.0
 * Written by David van der Spoel, Erik Lindahl, Berk Hess, and others.
 * Copyright (c) 1991-2000, University of Groningen, The Netherlands.
 * Copyright (c) 2001-2004, The GROMACS development team,
 * check out http://www.gromacs.org for more information.

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * If you want to redistribute modifications, please consider that
 * scientific software is very special. Version control is crucial -
 * bugs must be traceable. We will be happy to consider code for
 * inclusion in the official distribution, but derived work must not
 * be called official GROMACS. Details are found in the README & COPYING
 * files - if they are missing, get the official version at www.gromacs.org.
 * 
 * To help us fund GROMACS development, we humbly ask that you cite
 * the papers on the package - you can find them in the top README file.
 * 
 * For more info, check our website at http://www.gromacs.org
 * 
 * And Hey:
 * GROningen Mixture of Alchemy and Childrens' Stories
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "typedefs.h"
#include "xdrf.h"
#include "gmx_fatal.h"
#include "smalloc.h"

int xdr_real(XDR *xdrs,real *r)
{
#ifdef GMX_DOUBLE
  float f;
  int   ret;
  
  f=*r;
  ret=xdr_float(xdrs,&f);
  *r=f;

  return ret;
#else
  return xdr_float(xdrs,(float *)r);
#endif
}

int xdr3drcoord(XDR *xdrs, real *fp, int *size, real *precision)
{
#ifdef GMX_DOUBLE
  float *ffp;
  float  fprec;
  int    i,ret,isize;
  
  isize=*size*DIM;
  if (isize <= 0)
    gmx_fatal(FARGS,"Don't know what to malloc for ffp, isize = %d",isize);

  snew(ffp,isize);

  for(i=0; (i<isize); i++)
    ffp[i]=fp[i];
  fprec=*precision;
  ret=xdr3dfcoord(xdrs,ffp,size,&fprec);
  
  *precision=fprec;
  for(i=0; (i<isize); i++)
    fp[i]=ffp[i];

  sfree(ffp);
  return ret;
#else
  return xdr3dfcoord(xdrs,(float *)fp,size,(float *)precision);
#endif
}







