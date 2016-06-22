// boltz.c - december 6, 2005
// returns boltzmann-weighted states for dominos with gravity.

#include <stdio.h>
#include <math.h>
#include "rstuff.h"

unsigned long iBoltz[9];	// 9 for rest state
double Boltz[9];
unsigned long igBoltz[5];	// for glauber factors,
double gBoltz[5];			// exp(-Beta*n*Grav) where n = -2, -1, 0, 1, or 2
#if 0
long boltz()
{

myrand();

if(_seed < iBoltz[0])		// translation down (two units)
	return 0;
else if(_seed < iBoltz[1])	// translation right
	return 1;
else if(_seed < iBoltz[2])	// translation up (two units)
	return 2;
else if(_seed < iBoltz[3])	// translation left
	return 3;
else if(_seed < iBoltz[4])	// rotation down
	return 4;
else if(_seed < iBoltz[5])	// rotation down
	return 5;
else if(_seed < iBoltz[6])	// rotation up
	return 6;
else //	(_seed < iBoltz[7])	// rotation up
	return 7;
}
#endif
#if 1
long boltz()	// same speed as above if optimizer on
{
register unsigned long *iboltz;

iboltz = iBoltz;

myrand();

if(_seed < *iboltz++)		// translation down (two units)
	return 0;
else if(_seed < *iboltz++)	// translation right
	return 1;
else if(_seed < *iboltz++)	// translation up (two units)
	return 2;
else if(_seed < *iboltz++)	// translation left
	return 3;
else if(_seed < *iboltz++)	// rotation down
	return 4;
else if(_seed < *iboltz++)	// rotation down
	return 5;
else if(_seed < *iboltz++)	// rotation up
	return 6;
else if(_seed < *iboltz++)	// rotation up
	return 7;
 else return 8;			// rest
}
#endif

//  fills in iBoltz[]...
//  iBoltz[] values are unsigned longs for speed.
//  the unit probability interval is divied up into
//  ranges for the 8 transitions, and spread over the
//  unsigned long range 0 to 4294967295.
void initgravboltz(double temp,double grav)
{
double Z,Q,beta;
unsigned long prob,sofar;
long i;

beta = 1.0/temp;
Q = exp(-beta*grav);	// boltzmann factor (less than one)

Z = 1.0 + 1.0;			// neutral translations
Z += Q*Q;			// upward translation (two units)
Z += 1.0/(Q*Q);			// downward translation (two units)
Z += (Q + Q);			// upward rotations
Z += (1.0/Q + 1.0/Q);	// downward rotations


Boltz[0] = 1.0/(Q*Q)/Z;		// move 0 (downward translation)
Boltz[1] = 1.0/Z;			// move 1 (neutral right translation)
Boltz[2] = Q*Q/Z;			// move 2 (upward translation)
Boltz[3] = 1.0/Z;			// move 3 (neutral left translation)
Boltz[4] = 1.0/Q/Z;			// move 4 (downward rotation)
Boltz[5] = 1.0/Q/Z;			// move 5 (downward rotation)
Boltz[6] = Q/Z;				// move 6 (upward rotation)
Boltz[7] = Q/Z;				// move 7 (upward rotation)
 Boltz[8] = 0;			// rest (not used)

sofar = 0;
for(i=0;i<9;i++)
	{
	prob = (unsigned long)(Boltz[i]*4294967296.0);	
	iBoltz[i] = sofar + prob;
	sofar += prob;
	}
}


void initpotboltz(double temp,double grav)
{
double Z,Q,beta;
unsigned long prob,sofar;
long i;

beta = 1.0/temp;
Q = exp(-beta*grav);	// boltzmann factor (less than one)

Z = 8.0;			// all moves away from rest
Z += 1.0/Q;				// rest state

Boltz[0] = 1.0/Z;		// move 0 (downward translation)
Boltz[1] = 1.0/Z;		// move 1 (neutral right translation)
Boltz[2] = 1.0/Z;		// move 2 (upward translation)
Boltz[3] = 1.0/Z;		// move 3 (neutral left translation)
Boltz[4] = 1.0/Z;		// move 4 (downward rotation)
Boltz[5] = 1.0/Z;		// move 5 (downward rotation)
Boltz[6] = 1.0/Z;		// move 6 (upward rotation)
Boltz[7] = 1.0/Z;		// move 7 (upward rotation)
Boltz[8] = 1.0/Q/Z;		// rest state

sofar = 0;
for(i=0;i<9;i++)
	{
	prob = (unsigned long)(Boltz[i]*4294967296.0);	
	iBoltz[i] = sofar + prob;
	sofar += prob;
	}
}

//  fills in igBoltz[i]...
//  we have a difference between two energy levels, the transition probability is given by
//  a boltzmann factor, P = exp(-BdE) / (1 + exp(-BdE)), where dE is the energy difference,
//  dE = n*Gravity, n = -2, -1, 0, 1, 2, indexed by i = 0, 1, 2, 3, 4.
//  igBoltz[] values are unsigned longs for speed.
//  unit interval is mapped to unsigned long range 0 to 4294967295
void initgboltz(double temp,double grav)
{
double Q,beta;
unsigned long prob;
long i;

beta = 1.0/temp;

Q = exp(-beta*-2*grav);	// boltzmann factor (less than one)
gBoltz[0] = Q / (1 + Q);
Q = exp(-beta*-1*grav);
gBoltz[1] = Q / (1 + Q);
Q = 1;						// equal energies, P = 1/2
gBoltz[2] = Q / (1 + Q);
Q = exp(-beta*1*grav);
gBoltz[3] = Q / (1 + Q);
Q = exp(-beta*2*grav);
gBoltz[4] = Q / (1 + Q);

for(i=0;i<5;i++)
	{
	prob = (unsigned long)(gBoltz[i]*4294967296.0);	
	igBoltz[i] = prob;
	printf("%f\t%lu\n",gBoltz[i],igBoltz[i]);
	}
printf("\n");
}

// checkboltz() - takes five values 0 - 4 corresponding to possible energy differences
// -2g, -g, 0, g, 2g and indexes a precomputed boltzmann factor.  the normalized probabilities
// associated with glauber dynamics are P = exp(-BdE) / (1 + exp(-BdE)) where dE is the energy difference.
// the function returns a 0 with probability P and 1 otherwise.
long checkboltz(long index)
{

myrand();
if(_seed < igBoltz[index]) return 0;
return 1;

}
