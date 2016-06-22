#include "rstuff.h"
// try and take a step with domino nn, return -1 if a bump w/ bndy,
// return -8 if a bump w/ another domino...
// this version will fix a bug in stepdomino2, and hopefully have
// a consistent scheme for mapping domino endedness.
// we'll implement the "more physical" "sliding around" mapping,
// rather than the "fix one end and rotate" mapping, if SLIP is #defined to be nonzero.
// states are not equiprobable, but are boltzmann weighted, returned by the function
// n = boltz(), defined in boltz.c. 

// "very soft" dominos...
long stepdomino(long nn)
{
long at1,at2,n,newpos1,newpos2;


at1 = dominos[nn].atnode1;
at2 = dominos[nn].atnode2;
//printf("i,j  %d %d\n",i,j);
//Delay(120,nil);
n = boltz();
//n %= 4;
//if (n<4) n += 4;
//if( n == 0) n += 4;
//if( n == 1) n += 4;
//if( n == 2) n += 4;
//if( n == 3) n += 4;
//printf("n %d\n",n);
//Delay(2,nil);
//if((j == i+1) || (j == i-1) || (j == (i+ROWL-1) || (j == (i-ROWL+1))

// horizontal domino, with possible circular boundary conditions...
if((at2 == at1+1) || (at2 == (at1-ROWL+1)))	// atnode2 is to right of atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		//printf("newpos1,newpos2  %d %d\n",newpos1,newpos2);
		//Delay(120,nil);
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to vertical!
	if(n == 4)		// left end fixed, rotate down...
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 5)		// right end fixed, rotate down...
		{
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 6)		// left end fixed, rotate up...
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 7)		// right end fixed, rotate up...
		{
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
		
	}
if((at1 == at2+1) || (at1 == (at2-ROWL+1)))	// atnode1 is to right of atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		//printf("newpos1,newpos2  %d %d\n",newpos1,newpos2);
		//Delay(120,nil);
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	// n >= 4, attempt to rotate to vertical!
	if(n == 4)		// left end fixed, rotate down...
		{
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 5)		// right end fixed, rotate down...
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 6)		// left end fixed, rotate up...
		{
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 7)		// right end fixed, rotate up...
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	}

// vertical domino, with possible circular boundary conditions......
if((at2 == at1+ROWL) || (at2 == (at1-(NROWS-1)*ROWL)))	// atnode2 is above atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to horizontal!
	if(n == 4)		// bottom end fixed, rotate right...
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 5)		// bottom end fixed, rotate left...
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 6)		// top end fixed, rotate right...
		{
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 7)		// top end fixed, rotate left...
		{
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	}
if((at1 == at2+ROWL) || (at1 == (at2-(NROWS-1)*ROWL)))	// atnode1 is above atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode2 = newpos2;			// move vertically down!
		dominos[nn].atnode1 = at2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode2 = at1;				// move vertically up!
		dominos[nn].atnode1 = newpos1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to horizontal!
	if(n == 4)		// bottom end fixed, rotate right...
		{
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 5)		// bottom end fixed, rotate left...
		{
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 6)		// top end fixed, rotate right...
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 7)		// top end fixed, rotate left...
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	}

return nn;
}

// try and take a step with domino nn, return -1 if a bump w/ bndy,
// return -8 if a bump w/ another domino...
// insert blocking states on rotations!
// "soft" dominos...
long stepdomino1(long nn)
{
long at1,at2,n,newpos1,newpos2,block;

at1 = dominos[nn].atnode1;
at2 = dominos[nn].atnode2;

n = boltz();

// horizontal domino, with possible circular boundary conditions...
if((at2 == at1+1) || (at2 == (at1-ROWL+1)))	// atnode2 is to right of atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to vertical!
	if(n == 4)		// left end fixed, rotate down...
		{
		newpos1 = nodes[at1].Nbrs[0];
		block = nodes[at2].Nbrs[0];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 5)		// right end fixed, rotate down...
		{
		newpos2 = nodes[at2].Nbrs[0];
		block = nodes[at1].Nbrs[0];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 6)		// left end fixed, rotate up...
		{
		newpos1 = nodes[at1].Nbrs[2];
		block = nodes[at2].Nbrs[2];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 7)		// right end fixed, rotate up...
		{
		newpos2 = nodes[at2].Nbrs[2];
		block = nodes[at1].Nbrs[2];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
		
	}
if((at1 == at2+1) || (at1 == (at2-ROWL+1)))	// atnode1 is to right of atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		//printf("newpos1,newpos2  %d %d\n",newpos1,newpos2);
		//Delay(120,nil);
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	// n >= 4, attempt to rotate to vertical!
	if(n == 4)		// left end fixed, rotate down...
		{
		newpos2 = nodes[at2].Nbrs[0];
		block = nodes[at1].Nbrs[0];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 5)		// right end fixed, rotate down...
		{
		newpos1 = nodes[at1].Nbrs[0];
		block = nodes[at2].Nbrs[0];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 6)		// left end fixed, rotate up...
		{
		newpos2 = nodes[at2].Nbrs[2];
		block = nodes[at1].Nbrs[2];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 7)		// right end fixed, rotate up...
		{
		newpos1 = nodes[at1].Nbrs[2];
		block = nodes[at2].Nbrs[2];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	}

// vertical domino, with possible circular boundary conditions......
if((at2 == at1+ROWL) || (at2 == (at1-(NROWS-1)*ROWL)))	// atnode2 is above atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;				// move vertically down!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to horizontal!
	if(n == 4)		// bottom end fixed, rotate right...
		{
		newpos1 = nodes[at1].Nbrs[1];
		block = nodes[at2].Nbrs[1];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 5)		// bottom end fixed, rotate left...
		{
		newpos1 = nodes[at1].Nbrs[3];
		block = nodes[at2].Nbrs[3];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 6)		// top end fixed, rotate right...
		{
		newpos2 = nodes[at2].Nbrs[1];
		block = nodes[at1].Nbrs[1];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 7)		// top end fixed, rotate left...
		{
		newpos2 = nodes[at2].Nbrs[3];
		block = nodes[at1].Nbrs[3];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	}
if((at1 == at2+ROWL) || (at1 == (at2-(NROWS-1)*ROWL)))	// atnode1 is above atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode2 = newpos2;			// move vertically down!
		dominos[nn].atnode1 = at2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode2 = at1;				// move vertically up!
		dominos[nn].atnode1 = newpos1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to horizontal!
	if(n == 4)		// bottom end fixed, rotate right...
		{
		newpos2 = nodes[at2].Nbrs[1];
		block = nodes[at1].Nbrs[1];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 5)		// bottom end fixed, rotate left...
		{
		newpos2 = nodes[at2].Nbrs[3];
		block = nodes[at1].Nbrs[3];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 6)		// top end fixed, rotate right...
		{
		newpos1 = nodes[at1].Nbrs[1];
		block = nodes[at2].Nbrs[1];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 7)		// top end fixed, rotate left...
		{
		newpos1 = nodes[at1].Nbrs[3];
		block = nodes[at2].Nbrs[3];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	}

return nn;
}

// try and take a step with domino nn, return -1 if a bump w/ bndy,
// return -8 if a bump w/ another domino...
// insert even more blocking states on rotations!
// "nhp" dominos...
// domino can't turn if both ends are held, either in the source,
// or destination configuration.
// unclear who to transmit bump to, if held from twisting by ends...
// for the moment, send a separate signal, -2.
long stepdomino2(long nn)
{
long at1,at2,n,newpos1,newpos2,block,end1,end2;

at1 = dominos[nn].atnode1;
at2 = dominos[nn].atnode2;

n = boltz();

// horizontal domino, with possible circular boundary conditions...
if((at2 == at1+1) || (at2 == (at1-ROWL+1)))	// atnode2 is to right of atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to vertical!
	if(n == 4)		// left end fixed, rotate down...
		{
		newpos1 = nodes[at1].Nbrs[0];
		block = nodes[at2].Nbrs[0];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[3];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end1 = nodes[at1].Nbrs[2];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 5)		// right end fixed, rotate down...
		{
		newpos2 = nodes[at2].Nbrs[0];
		block = nodes[at1].Nbrs[0];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[3];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end2 = nodes[at2].Nbrs[2];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 6)		// left end fixed, rotate up...
		{
		newpos1 = nodes[at1].Nbrs[2];
		block = nodes[at2].Nbrs[2];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[3];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end1 = nodes[at1].Nbrs[0];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 7)		// right end fixed, rotate up...
		{
		newpos2 = nodes[at2].Nbrs[2];
		block = nodes[at1].Nbrs[2];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[3];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end2 = nodes[at2].Nbrs[0];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
		
	}
if((at1 == at2+1) || (at1 == (at2-ROWL+1)))	// atnode1 is to right of atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		//printf("newpos1,newpos2  %d %d\n",newpos1,newpos2);
		//Delay(120,nil);
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	// n >= 4, attempt to rotate to vertical!
	if(n == 4)		// left end fixed, rotate down...
		{
		newpos2 = nodes[at2].Nbrs[0];
		block = nodes[at1].Nbrs[0];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[1];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end2 = nodes[at2].Nbrs[2];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 5)		// right end fixed, rotate down...
		{
		newpos1 = nodes[at1].Nbrs[0];
		block = nodes[at2].Nbrs[0];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[1];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end1 = nodes[at1].Nbrs[2];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 6)		// left end fixed, rotate up...
		{
		newpos2 = nodes[at2].Nbrs[2];
		block = nodes[at1].Nbrs[2];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[1];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end2 = nodes[at2].Nbrs[0];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 7)		// right end fixed, rotate up...
		{
		newpos1 = nodes[at1].Nbrs[2];
		block = nodes[at2].Nbrs[2];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[1];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end1 = nodes[at1].Nbrs[0];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	}

// vertical domino, with possible circular boundary conditions......
if((at2 == at1+ROWL) || (at2 == (at1-(NROWS-1)*ROWL)))	// atnode2 is above atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;				// move vertically down!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to horizontal!
	if(n == 4)		// bottom end fixed, rotate right...
		{
		newpos1 = nodes[at1].Nbrs[1];
		block = nodes[at2].Nbrs[1];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[0];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end1 = nodes[at1].Nbrs[3];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 5)		// bottom end fixed, rotate left...
		{
		newpos1 = nodes[at1].Nbrs[3];
		block = nodes[at2].Nbrs[3];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[0];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end1 = nodes[at1].Nbrs[1];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 6)		// top end fixed, rotate right...
		{
		newpos2 = nodes[at2].Nbrs[1];
		block = nodes[at1].Nbrs[1];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[0];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end2 = nodes[at2].Nbrs[3];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 7)		// top end fixed, rotate left...
		{
		newpos2 = nodes[at2].Nbrs[3];
		block = nodes[at1].Nbrs[3];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[0];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end2 = nodes[at2].Nbrs[1];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	}
if((at1 == at2+ROWL) || (at1 == (at2-(NROWS-1)*ROWL)))	// atnode1 is above atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode2 = newpos2;			// move vertically down!
		dominos[nn].atnode1 = at2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 1)
		{
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	if(n == 2)
		{
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode2 = at1;				// move vertically up!
		dominos[nn].atnode1 = newpos1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 3)
		{
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		}
	// n >= 4, attempt to rotate to horizontal!
	if(n == 4)		// bottom end fixed, rotate right...
		{
		newpos2 = nodes[at2].Nbrs[1];
		block = nodes[at1].Nbrs[1];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[2];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end2 = nodes[at2].Nbrs[3];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 5)		// bottom end fixed, rotate left...
		{
		newpos2 = nodes[at2].Nbrs[3];
		block = nodes[at1].Nbrs[3];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos2 < 0) return newpos2;			// bump with bndy
		if(nodes[newpos2].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[2];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end2 = nodes[at2].Nbrs[1];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		}
	if(n == 6)		// top end fixed, rotate right...
		{
		newpos1 = nodes[at1].Nbrs[1];
		block = nodes[at2].Nbrs[1];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[2];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end1 = nodes[at1].Nbrs[3];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	if(n == 7)		// top end fixed, rotate left...
		{
		newpos1 = nodes[at1].Nbrs[3];
		block = nodes[at2].Nbrs[3];
		if(block < 0) return block;				// bump with bndy
		if(nodes[block].occ >= 0) return -8;	// bump with another domino
		if(newpos1 < 0) return newpos1;			// bump with bndy
		if(nodes[newpos1].occ >= 0) return -8;	// bump with another domino
		end1 = nodes[at1].Nbrs[2];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		end1 = nodes[at1].Nbrs[1];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) return -2;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) return -2;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) return -2;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		}
	}

return nn;
}
