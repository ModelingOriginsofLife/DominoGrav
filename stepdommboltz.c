#include "rstuff.h"
// assume we have "ndominos" dominos in the simulation
// pick one at random, attempt to move according to one of the rules
// repeat "ndominos" times
// runs about 25% faster than calling "stepdomino" individually

// stepdommgrav.c - this one inserts a boltzmann factor drift onto the dominos
// using the "new" boltzmann rule.  first, a kinetic path is chosen at random.
// then, the energy difference between the initial and final path is computed.
// this difference is used in a boltzmann factor to decide whether to try this path.
// finally, if the path is actually open, it is taken.
extern unsigned long igBoltz[5];	// for glauber factors

// "very soft" dominos...
void stepdomm()
{
long at1,at2,n,newpos1,newpos2,ndms;
long i,nn;

ndms = ndominos;

for(i=0;i<ndms;i++)
	{
	nn = n_rand(ndms);			// n_rand() only works up to 65,535
	at1 = dominos[nn].atnode1;
	at2 = dominos[nn].atnode2;
	n = n_rand8();				// pick a path at random
	#if CLOCK
	dominos[nn].clock++;
	#endif

// horizontal domino, with possible circular boundary conditions...
if((at2 == at1+1) || (at2 == (at1-ROWL+1)))	// atnode2 is to right of atnode1
	{
	// n < 4, attempt translations...
	if(n == 0) 
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		//printf("newpos1,newpos2  %d %d\n",newpos1,newpos2);
		//Delay(120,nil);
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[0][at1/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[1][at1/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[2][at1/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue; // bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[3][at1/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to vertical!
	else if(n == 4)		// left end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[4][at1/ROWL]++;
		#endif
		}
	else if(n == 5)		// right end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[5][at1/ROWL]++;
		#endif
		}
	else if(n == 6)		// left end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[6][at1/ROWL]++;
		#endif
		}
	else
	//if(n == 7)		// right end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[7][at1/ROWL]++;
		#endif
		}
		
	}
else if((at1 == at2+1) || (at1 == (at2-ROWL+1)))	// atnode1 is to right of atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		//printf("newpos1,newpos2  %d %d\n",newpos1,newpos2);
		//Delay(120,nil);
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[0][at2/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[1][at2/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[2][at2/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[3][at2/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to vertical!
	else if(n == 4)		// left end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[4][at2/ROWL]++;
		#endif
		}
	else if(n == 5)		// right end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[5][at2/ROWL]++;
		#endif
		}
	else if(n == 6)		// left end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[6][at2/ROWL]++;
		#endif
		}
	else
	//if(n == 7)		// right end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Phor[7][at2/ROWL]++;
		#endif
		}
	}

// vertical domino, with possible circular boundary conditions......
else if((at2 == at1+ROWL) || (at2 == (at1-(NROWS-1)*ROWL)))	// atnode2 is above atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
				// transition stats:
		#if TRANS
		Pver[0][at1/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[1][at1/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[2][at1/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[3][at1/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to horizontal!
	else if(n == 4)		// bottom end fixed, rotate right...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[4][at1/ROWL]++;
		#endif
		}
	else if(n == 5)		// bottom end fixed, rotate left...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[5][at1/ROWL]++;
		#endif
		}
	else if(n == 6)		// top end fixed, rotate right...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[6][at1/ROWL]++;
		#endif
		}
	else
	//if(n == 7)		// top end fixed, rotate left...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[7][at1/ROWL]++;
		#endif
		}
	}
	else
	//if((at1 == at2+ROWL) || (at1 == (at2-(NROWS-1)*ROWL)))	// atnode1 is above atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode2 = newpos2;			// move vertically down!
		dominos[nn].atnode1 = at2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[0][at2/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[1][at2/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode2 = at1;				// move vertically up!
		dominos[nn].atnode1 = newpos1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[2][at2/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[3][at2/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to horizontal!
	else if(n == 4)		// bottom end fixed, rotate right...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[4][at2/ROWL]++;
		#endif
		}
	else if(n == 5)		// bottom end fixed, rotate left...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[5][at2/ROWL]++;
		#endif
		}
	else if(n == 6)		// top end fixed, rotate right...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[6][at2/ROWL]++;
		#endif
		}
	else
	//if(n == 7)		// top end fixed, rotate left...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		#if TRANS
		Pver[7][at2/ROWL]++;
		#endif
		}
	}
}
return;
}

// insert blocking states on rotations!
// "soft" dominos...

void stepdomm1()
{
long at1,at2,n,newpos1,newpos2,block,ndms;
long i,nn;

ndms = ndominos;

for(i=0;i<ndms;i++)
	{
	nn = n_rand(ndms);			// n_rand() only works up to 65,535
	at1 = dominos[nn].atnode1;
	at2 = dominos[nn].atnode2;
	n = n_rand8();
//	n = boltz();
	#if CLOCK
	dominos[nn].clock++;
	#endif

// horizontal domino, with possible circular boundary conditions...
if((at2 == at1+1) || (at2 == (at1-ROWL+1)))	// atnode2 is to right of atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[0][at1/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[1][at1/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[2][at1/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[3][at1/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to vertical!
	else if(n == 4)		// left end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		block = nodes[at2].Nbrs[0];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[4][at1/ROWL]++;
		#endif
		}
	else if(n == 5)		// right end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		block = nodes[at1].Nbrs[0];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[5][at1/ROWL]++;
		#endif
		}
	else if(n == 6)		// left end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		block = nodes[at2].Nbrs[2];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[6][at1/ROWL]++;
		#endif
		}
	else
	//if(n == 7)		// right end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		block = nodes[at1].Nbrs[2];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[7][at1/ROWL]++;
		#endif
		}
		
	}
else if((at1 == at2+1) || (at1 == (at2-ROWL+1)))	// atnode1 is to right of atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		//printf("newpos1,newpos2  %d %d\n",newpos1,newpos2);
		//Delay(120,nil);
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[0][at2/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[1][at2/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[2][at2/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[3][at2/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to vertical!
	else if(n == 4)		// left end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		block = nodes[at1].Nbrs[0];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[4][at2/ROWL]++;
		#endif
		}
	else if(n == 5)		// right end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		block = nodes[at2].Nbrs[0];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[5][at2/ROWL]++;
		#endif
		}
	else if(n == 6)		// left end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		block = nodes[at1].Nbrs[2];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[6][at2/ROWL]++;
		#endif
		}
	else
	//if(n == 7)		// right end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		block = nodes[at2].Nbrs[2];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[7][at2/ROWL]++;
		#endif
		}
	}

// vertical domino, with possible circular boundary conditions......
else if((at2 == at1+ROWL) || (at2 == (at1-(NROWS-1)*ROWL)))	// atnode2 is above atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;				// move vertically down!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[0][at1/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[1][at1/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[2][at1/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[3][at1/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to horizontal!
	else if(n == 4)		// bottom end fixed, rotate right...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		block = nodes[at2].Nbrs[1];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[4][at1/ROWL]++;
		#endif
		}
	else if(n == 5)		// bottom end fixed, rotate left...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		block = nodes[at2].Nbrs[3];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[5][at1/ROWL]++;
		#endif
		}
	else if(n == 6)		// top end fixed, rotate right...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		block = nodes[at1].Nbrs[1];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[6][at1/ROWL]++;
		#endif
		}
	else
	//if(n == 7)		// top end fixed, rotate left...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		block = nodes[at1].Nbrs[3];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[7][at1/ROWL]++;
		#endif
		}
	}
else
//if((at1 == at2+ROWL) || (at1 == (at2-(NROWS-1)*ROWL)))	// atnode1 is above atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode2 = newpos2;			// move vertically down!
		dominos[nn].atnode1 = at2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[0][at2/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[1][at2/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode2 = at1;				// move vertically up!
		dominos[nn].atnode1 = newpos1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[2][at2/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[3][at2/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to horizontal!
	else if(n == 4)		// bottom end fixed, rotate right...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		block = nodes[at1].Nbrs[1];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[4][at2/ROWL]++;
		#endif
		}
	else if(n == 5)		// bottom end fixed, rotate left...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		block = nodes[at1].Nbrs[3];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[5][at2/ROWL]++;
		#endif
		}
	else if(n == 6)		// top end fixed, rotate right...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		block = nodes[at2].Nbrs[1];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[6][at2/ROWL]++;
		#endif
		}
	else
	//if(n == 7)		// top end fixed, rotate left...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		block = nodes[at2].Nbrs[3];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		Pver[7][at2/ROWL]++;
		#endif
		}
	}
}
return;
}

// "nhp" dominos...
// domino can't turn if both ends are held, either in the source,
// or destination configuration.

void stepdomm2()
{
long at1,at2,n,newpos1,newpos2,block,end1,end2,ndms;
long i,nn;
//long y1,y2,mny;
long mny;

ndms = ndominos;

for(i=0;i<ndms;i++)
	{
	nn = n_rand(ndms);			// n_rand() only works up to 65,535
	at1 = dominos[nn].atnode1;
	at2 = dominos[nn].atnode2;
//	n = n_rand4();		// translations only
	n = n_rand8();
//	n = boltz();
	//	n = n_rand(2); n = 2*n; // just vertical translations
	#if CLOCK
	dominos[nn].clock++;
	#endif


// horizontal domino, with possible circular boundary conditions...
if((at2 == at1+1) || (at2 == (at1-ROWL+1)))	// atnode2 is to right of atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[0][at1/ROWL]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[1][at1/ROWL]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[2][at1/ROWL]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		Phor[3][at1/ROWL]++;
		#endif
		}
	// n >= 4, attempt to rotate to vertical!
	else if(n == 4)		// left end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		block = nodes[at2].Nbrs[0];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[3];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end1 = nodes[at1].Nbrs[2];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at1/ROWL;
		Phor[4][mny]++;
		#endif
		}
	else if(n == 5)		// right end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		block = nodes[at1].Nbrs[0];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[3];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end2 = nodes[at2].Nbrs[2];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at1/ROWL;
		Phor[5][mny]++;
		#endif
		}
	else if(n == 6)		// left end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		block = nodes[at2].Nbrs[2];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[3];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end1 = nodes[at1].Nbrs[0];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at1/ROWL;
		Phor[6][mny]++;
		#endif
		}
	else		// right end fixed, rotate up...
//	if(n == 7)		// top end fixed, rotate left...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		block = nodes[at1].Nbrs[2];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[3];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end2 = nodes[at2].Nbrs[0];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at1/ROWL;
		Phor[7][mny]++;
		#endif
		}
		
	}
else if((at1 == at2+1) || (at1 == (at2-ROWL+1)))	// atnode1 is to right of atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically down!
		dominos[nn].atnode2 = newpos2;
		//printf("newpos1,newpos2  %d %d\n",newpos1,newpos2);
		//Delay(120,nil);
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at2/ROWL;
		Phor[0][mny]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at2/ROWL;
		Phor[1][mny]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at2/ROWL;
		Phor[2][mny]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at2/ROWL;
		Phor[3][mny]++;
		#endif
		}
	// n >= 4, attempt to rotate to vertical!
	else if(n == 4)		// left end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		block = nodes[at1].Nbrs[0];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[1];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end2 = nodes[at2].Nbrs[2];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate down!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate down!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at2/ROWL;
		Phor[4][mny]++;
		#endif
		}
	else if(n == 5)		// right end fixed, rotate down...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		block = nodes[at2].Nbrs[0];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[1];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end1 = nodes[at1].Nbrs[2];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate down!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate down!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at2/ROWL;
		Phor[5][mny]++;
		#endif
		}
	else if(n == 6)		// left end fixed, rotate up...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		block = nodes[at1].Nbrs[2];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[1];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end2 = nodes[at2].Nbrs[0];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate up!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate up!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at2/ROWL;
		Phor[6][mny]++;
		#endif
		}
	else		// right end fixed, rotate up...
//	if(n == 7)		// top end fixed, rotate left...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		block = nodes[at2].Nbrs[2];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[1];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end1 = nodes[at1].Nbrs[0];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate up!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate up!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition stats:
		#if TRANS
		mny = at1/ROWL;
		Phor[7][mny]++;
		#endif
		}
	}

// vertical domino, with possible circular boundary conditions......
else if((at2 == at1+ROWL) || (at2 == (at1-(NROWS-1)*ROWL)))	// atnode2 is above atnode1
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos1 = nodes[at1].Nbrs[0];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;				// move vertically down!
		dominos[nn].atnode2 = at1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at1/ROWL;			// at1 always below at2
		Pver[0][mny]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at1/ROWL;
		Pver[1][mny]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos2 = nodes[at2].Nbrs[2];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = at2;				// move vertically up!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at1/ROWL;
		Pver[2][mny]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at1/ROWL;
		Pver[3][mny]++;
		#endif
		}
	// n >= 4, attempt to rotate to horizontal!
	else if(n == 4)		// bottom end fixed, rotate right...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		block = nodes[at2].Nbrs[1];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[0];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end1 = nodes[at1].Nbrs[3];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at1/ROWL;
		Pver[4][mny]++;
		#endif
		}
	else if(n == 5)		// bottom end fixed, rotate left...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		block = nodes[at2].Nbrs[3];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[0];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end1 = nodes[at1].Nbrs[1];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at1/ROWL;
		Pver[5][mny]++;
		#endif
		}
	else if(n == 6)		// top end fixed, rotate right...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		block = nodes[at1].Nbrs[1];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[0];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end2 = nodes[at2].Nbrs[3];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at1/ROWL;
		Pver[6][mny]++;
		#endif
		}
	else		// top end fixed, rotate left...
//	if(n == 7)		// top end fixed, rotate left...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		block = nodes[at1].Nbrs[3];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[0];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[2];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end2 = nodes[at2].Nbrs[1];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at1/ROWL;
		Pver[7][mny]++;
		#endif
		}
	}
else if((at1 == at2+ROWL) || (at1 == (at2-(NROWS-1)*ROWL)))	// atnode1 is above atnode2
	{
	// n < 4, attempt translations...
	if(n == 0)
		{
//		if(checkboltz(0)) continue;			// boltzmann weighting (2 down)
		myrand();
		if(_seed > igBoltz[0]) continue;
		newpos2 = nodes[at2].Nbrs[0];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode2 = newpos2;			// move vertically down!
		dominos[nn].atnode1 = at2;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at2/ROWL;			// at2 always below at1
		Pver[0][mny]++;
		#endif
		}
	else if(n == 1)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[1];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the right!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at2/ROWL;
		Pver[1][mny]++;
		#endif
		}
	else if(n == 2)
		{
//		if(checkboltz(4)) continue;			// boltzmann weighting (2 up)
		myrand();
		if(_seed > igBoltz[4]) continue;
		newpos1 = nodes[at1].Nbrs[2];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode2 = at1;				// move vertically up!
		dominos[nn].atnode1 = newpos1;
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at2/ROWL;
		Pver[2][mny]++;
		#endif
		}
	else if(n == 3)
		{
//		if(checkboltz(2)) continue;			// boltzmann weighting (0 change)
		myrand();
		if(_seed > igBoltz[2]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		newpos2 = nodes[at2].Nbrs[3];
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		dominos[nn].atnode1 = newpos1;			// move to the left!
		dominos[nn].atnode2 = newpos2;
		nodes[newpos1].occ = nn;
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at2/ROWL;
		Pver[3][mny]++;
		#endif
		}
	// n >= 4, attempt to rotate to horizontal!
	else if(n == 4)		// bottom end fixed, rotate right...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[1];
		block = nodes[at1].Nbrs[1];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[2];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end2 = nodes[at2].Nbrs[3];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate right!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate right!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at2/ROWL;
		Pver[4][mny]++;
		#endif
		}
	else if(n == 5)		// bottom end fixed, rotate left...
		{
//		if(checkboltz(1)) continue;			// boltzmann weighting (1 down)
		myrand();
		if(_seed > igBoltz[1]) continue;
		newpos2 = nodes[at2].Nbrs[3];
		block = nodes[at1].Nbrs[3];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos2 < 0) continue;			// bump with bndy
		if(nodes[newpos2].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[2];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end2 = nodes[at2].Nbrs[1];				// check for destination held by ends...
		end1 = nodes[newpos2].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = at2;				// rotate left!
		dominos[nn].atnode2 = newpos2;			// (slip ordering)
		#else
		dominos[nn].atnode2 = at2;				// rotate left!
		dominos[nn].atnode1 = newpos2;			// (rotate ordering)
		#endif
		nodes[newpos2].occ = nn;
		nodes[at1].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at2/ROWL;
		Pver[5][mny]++;
		#endif
		}
	else if(n == 6)		// top end fixed, rotate right...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[1];
		block = nodes[at2].Nbrs[1];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[2];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end1 = nodes[at1].Nbrs[3];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[1];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate right!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate right!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at2/ROWL;
		Pver[6][mny]++;
		#endif
		}
	else
//	if(n == 7)		// top end fixed, rotate left...
		{
//		if(checkboltz(3)) continue;			// boltzmann weighting (1 up)
		myrand();
		if(_seed > igBoltz[3]) continue;
		newpos1 = nodes[at1].Nbrs[3];
		block = nodes[at2].Nbrs[3];
		if(block < 0) continue;				// bump with bndy
		if(nodes[block].occ >= 0) continue;	// bump with another domino
		if(newpos1 < 0) continue;			// bump with bndy
		if(nodes[newpos1].occ >= 0) continue;	// bump with another domino
		end1 = nodes[at1].Nbrs[2];				// check for source held by ends...
		end2 = nodes[at2].Nbrs[0];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		end1 = nodes[at1].Nbrs[1];				// check for destination held by ends...
		end2 = nodes[newpos1].Nbrs[3];
		if(end1 == -1)							// end is on a boundary
			if(nodes[end2].occ >= 0) continue;
		if(end2 == -1)							// end is on a boundary
			if(nodes[end1].occ >= 0) continue;
		if((nodes[end1].occ >= 0) && (nodes[end2].occ >= 0)) continue;
		#if SLIP
		dominos[nn].atnode1 = newpos1;			// rotate left!
		dominos[nn].atnode2 = at1;				// (slip ordering)
		#else
		dominos[nn].atnode2 = newpos1;			// rotate left!
		dominos[nn].atnode1 = at1;				// (rotate ordering)
		#endif
		nodes[newpos1].occ = nn;
		nodes[at2].occ = -1;
		#if CLOCK
		dominos[nn].clock = 0;
		#endif
		//  transition statistics
		#if TRANS
		mny = at2/ROWL;
		Pver[7][mny]++;
		#endif
		}
	}
 else{
	 fprintf(stderr,"Whoa baby!!!\n"); 
	 fprintf(stderr,"nn = %d\n",(int)nn);
	 fprintf(stderr,"at1 = %d\n",(int)dominos[nn].atnode1);
	 fprintf(stderr,"at2 = %d\n",(int)dominos[nn].atnode2);
	 exit(4);
 }
//   int chk;
//   chk = checkdom(nn);
//   if(chk>0){
//  	 fprintf(stderr,"Bad dom!!!\n"); 
//  	 exit(5);
//   }
 mny = 1;			// for debugging...
}
return;
}


int checkdom(int nn);
int checkdom(int nn)
{
	int at1,at2;
	at1 = dominos[nn].atnode1;
	at2 = dominos[nn].atnode2;
	if((at2 == at1+1) && ((at1+1)%ROWL ==0)) // at1 at end of row
		return(1);
	else
		return(0);
}
			
	


void checkall();
	
void checkall()
{
	int chk,i;
	for(i=0;i<ndominos;i++)
	{
		chk = checkdom(i);
		if(chk>0){
			printf("%d\t%ld\t%ld\n",i,
			       dominos[i].atnode1, dominos[i].atnode2);
		}
	}
}
