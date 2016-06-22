// shuffle.c - december 19, 2004
// in-place shuffle of array of longs or floats
// about 2200 shuffles per second of 10000 array
// on the 1400 400 MHz.

#include <stdio.h>
#include <math.h>
#include "myrand4.h"

void shuffle(void *Ptr,long n);
void shuffle(void *Ptr,long n)
{
long i,nn,val,*A;
//register unsigned long _seed = 1;

A = Ptr;
for(i=0;i<n;i++)
	{
	nn = n_rand(n);
	//if(nn == i) continue;
	val = A[i];
	A[i] = A[nn];
	A[nn] = val;
	}
}

