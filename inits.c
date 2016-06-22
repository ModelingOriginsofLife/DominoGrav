#include "rstuff.h"
#include "glgraph.h"
#include <unistd.h>

// fill in node structure neighborhoods...
void initnodes()
{
long i;

// -1 means node unoccupied...
for(i=0;i<NMAX;i++)
	nodes[i].occ = -1;

// bottom neighbor...
for(i=0;i<ROWL;i++)
	nodes[i].Nbrs[0] = -1;
for(i=ROWL;i<ROWL*NROWS;i++)
	nodes[i].Nbrs[0] = i - ROWL;
	
// right neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if((i+1)%ROWL == 0)
		nodes[i].Nbrs[1] = -1;
	else
		nodes[i].Nbrs[1] = i+1;
	}

// top neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i+ROWL >= NMAX)
		nodes[i].Nbrs[2] = -1;
	else
		nodes[i].Nbrs[2] = i+ROWL;
	}

// left neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i%ROWL == 0)
		nodes[i].Nbrs[3] = -1;
	else
		nodes[i].Nbrs[3] = i-1;
	}
}

// fills in next-to-nearest neighbor entries as well.
void initnodes8()
{
long i;

// -1 means node unoccupied...
for(i=0;i<NMAX;i++)
	nodes[i].occ = -1;

// bottom neighbor...
for(i=0;i<ROWL;i++)
	nodes[i].Nbrs[0] = -1;
for(i=ROWL;i<ROWL*NROWS;i++)
	nodes[i].Nbrs[0] = i - ROWL;
	
// right neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if((i+1)%ROWL == 0)
		nodes[i].Nbrs[1] = -1;
	else
		nodes[i].Nbrs[1] = i+1;
	}

// top neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i+ROWL >= NMAX)
		nodes[i].Nbrs[2] = -1;
	else
		nodes[i].Nbrs[2] = i+ROWL;
	}

// left neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i%ROWL == 0)
		nodes[i].Nbrs[3] = -1;
	else
		nodes[i].Nbrs[3] = i-1;
	}

// bottom next-to-neighbor...
for(i=0;i<ROWL;i++)
	nodes[i].Nbrs[4] = -1;
for(i=ROWL;i<2*ROWL;i++)
	nodes[i].Nbrs[4] = -1;
for(i=2*ROWL;i<ROWL*NROWS;i++)
	nodes[i].Nbrs[4] = i - 2*ROWL;

// right next-to-neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if((i+1)%ROWL == 0)
		nodes[i].Nbrs[5] = -1;
	else if((i+2)%ROWL == 0)
		nodes[i].Nbrs[5] = -1;
	else
		nodes[i].Nbrs[5] = i+2;
	}

// top next-to-neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i+ROWL >= NMAX)
		nodes[i].Nbrs[6] = -1;
	else if(i+2*ROWL >= NMAX)
		nodes[i].Nbrs[6] = -1;
	else
		nodes[i].Nbrs[6] = i+2*ROWL;
	}

// left next-to-neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i%ROWL == 0)
		nodes[i].Nbrs[7] = -1;
	else if((i-1)%ROWL == 0)
		nodes[i].Nbrs[7] = -1;
	else
		nodes[i].Nbrs[7] = i-2;
	}
}

// circular boundary conditions...
void initnodescb()
{
long i;

// -1 means node unoccupied...
for(i=0;i<NMAX;i++)
	nodes[i].occ = -1;

// bottom neighbor...
for(i=0;i<ROWL;i++)
	nodes[i].Nbrs[0] = (NROWS-1)*ROWL + i;
for(i=ROWL;i<ROWL*NROWS;i++)
	nodes[i].Nbrs[0] = i - ROWL;
	
// right neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if((i+1)%ROWL == 0)
		nodes[i].Nbrs[1] = i+1-ROWL;
	else
		nodes[i].Nbrs[1] = i+1;
	}

// top neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i+ROWL >= NMAX)
		nodes[i].Nbrs[2] = (i%ROWL);
	else
		nodes[i].Nbrs[2] = i+ROWL;
	}

// left neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i%ROWL == 0)
		nodes[i].Nbrs[3] = i+ROWL-1;
	else
		nodes[i].Nbrs[3] = i-1;
	}
}

// circular boundary conditions left and right,
// solid boundary top and bottom.
void initnodescb1()
{
long i;

// -1 means node unoccupied...
for(i=0;i<NMAX;i++)
	nodes[i].occ = -1;

// bottom neighbor...
for(i=0;i<ROWL;i++)
	nodes[i].Nbrs[0] = -1;
for(i=ROWL;i<ROWL*NROWS;i++)
	nodes[i].Nbrs[0] = i - ROWL;
	
// right neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if((i+1)%ROWL == 0)
		nodes[i].Nbrs[1] = i+1-ROWL;
	else
		nodes[i].Nbrs[1] = i+1;
	}

// top neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i+ROWL >= NMAX)
		nodes[i].Nbrs[2] = -1;
	else
		nodes[i].Nbrs[2] = i+ROWL;
	}

// left neighbor...
for(i=0;i<ROWL*NROWS;i++)
	{
	if(i%ROWL == 0)
		nodes[i].Nbrs[3] = i+ROWL-1;
	else
		nodes[i].Nbrs[3] = i-1;
	}
}

void initobstacle()
{
long i;
float x0,y0,x,y,dist,rad = 10;

x0 = ROWL/2;
y0 = NROWS/2;

for(i=0;i<ROWL*NROWS;i++)
	{
	x = i%ROWL;
	y = i/NROWS;
	dist = (x-x0)*(x-x0) + (y-y0)*(y-y0);
	if(dist < rad*rad)
		{
		nodes[i].occ = 1000000;
		Obs[nobs++] = i;
		}
	}
}

void initmem()                  // membrane
{
long i,idx;
/*
for(i=0;i<ROWL-2;i+=5)			// three filled, one open
    {
    idx = NROWS*ROWL/2+i;
    //idx = (NROWS/3)*ROWL+i;		// lower membrane on screen
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
    idx++;
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
     nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
    idx++;
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
     idx++;
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
	}
*/
/*
for(i=0;i<ROWL-2;i+=4)			// three filled, one open
    {
    idx = NROWS*ROWL/2+i;
    //idx = (NROWS/3)*ROWL+i;		// lower membrane on screen
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
    idx++;
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
     nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
    idx++;
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
	}
*/
//*
for(i=0;i<ROWL-2;i+=3)			// two filled, one open
    {
    idx = NROWS*ROWL/2+i;
    //idx = (NROWS/3)*ROWL+i;		// lower membrane on screen
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
    idx++;
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
	}
//*/
/*
for(i=0;i<ROWL;i+=2)			// every other
    {
    //idx = NROWS*ROWL/2+i;
    idx = (2*NROWS/3)*ROWL+i;		// lower membrane on screen
    nodes[idx].occ = 1000000;
    Obs[nobs++] = idx;
    idx++;
	}
*/
/*
 for(i=0;i<ROWL;i++)            // to isolate top from bottom...
     {
     idx = ROWL+i;
     nodes[idx].occ = 1000000;
     Obs[nobs++] = idx;
     }
*/
}

// make a membrane of thickness "thick", with pores
// separated by "space", at "height" above the bottom of the display.
void initmem1(long thick,long space, long height)
{
long i,j,idx=0,hgt;

i=0;
while(i<ROWL)
	{
	if(i%space)
		{
		idx = height*ROWL + i;
		nodes[idx].occ = 1000000;
		Obs[nobs++] = idx;
		}
	i++;
	}
if(dispctl)
	{
	printf("in initmem1 %ld\n",dispctl);
	sleep(1);
	}
for(j=1;j<thick;j++)
	{
	hgt = (height+j)*ROWL;
	i=0;
	while(i<ROWL)
		{
		if((i%space != 0) && (i%space != 1))
			{
			idx = hgt + i;
			nodes[idx].occ = 1000000;
			Obs[nobs++] = idx;
			if(dispctl)
			{
			printf("in loop/n");
			printf("dispctl,i,j,idx %ld %ld %ld %ld\n",dispctl,i,j,idx);
			printf("nobs, NMAX %ld %ld\n",nobs,NMAX);
			sleep(4);
			}
			}
		if(dispctl)
			{
			printf("after loop/n");
			printf("dispctl,i,j,idx %ld %ld %ld %ld\n",dispctl,i,j,idx);
			sleep(1);
			}
		i++;
		}
	}
if(dispctl)
	{
	printf("in initmem1 #2 %ld\n",dispctl);
	sleep(1);
	}
}

// makes a simple pore, no blocking.
// make a membrane of thickness "thick", with pores
// separated by "space", at "height" above the bottom of the display.
// if space = 0, no pores at all.
void initmem2(long thick,long space, long height)
{
long i,j,idx=0,hgt;

for(j=0;j<thick;j++)
	{
	hgt = (height+j)*ROWL;
	i=0;
	while(i<ROWL)
		{
		if(((i%space != 0) && (i%space != 1)) || space == 0)
			{
			idx = hgt + i;
			nodes[idx].occ = 1000000;
			Obs[nobs++] = idx;
			}
		i++;
		}
	}
}

// create a domino at location node1, node2, return its index...
// adjust to allow circular boundary condition dominos...
long createdomino(long node1,long node2)
{

	if(nodes[node1].occ >= 0)	// somebody already there...
		return -1;
	if(nodes[node2].occ >= 0)	// somebody already there...
		return -1;
	if((node1 >= NMAX) || (node2 >= NMAX))	// off the grid...
		return -1;
	if((node1 < 0) || (node2 < 0))	// off the grid...
		return -1;
#if 0
	if(abs(node2-node1) != 1)		// not adjacent...
		if(abs(node2-node1) != ROWL)
			if(abs(node2-node1) != (ROWL-1))	// circular (horizontal)
				if(abs(node2-node1) != (ROWL*(NROWS-1)))	// circular (vertical)
					return -1;
#endif
//	if(((node1%ROWL) == 0) && ((node2%ROWL) == ROWL-1))	// wraparound...
//		return -1;
//	if(((node2%ROWL) == 0) && ((node1%ROWL) == ROWL-1))	// wraparound...
//		return -1;
	dominos[ndominos].exists = 1;	// mark as existent...
	dominos[ndominos].atnode1 = node1;
	dominos[ndominos].atnode2 = node2;
	nodes[node1].occ = ndominos;
	nodes[node2].occ = ndominos;
	++ndominos;
	return ndominos;
}

// create a domino at location node1, node2, return its index...
// adjust to allow circular boundary condition dominos...
// create with a particular color...
long createdominoc(long node1,long node2,long col)
{

	if(nodes[node1].occ >= 0)	// somebody already there...
		return -1;
	if(nodes[node2].occ >= 0)	// somebody already there...
		return -1;
	if((node1 >= NMAX) || (node2 >= NMAX))	// off the grid...
		return -1;
	if((node1 < 0) || (node2 < 0))	// off the grid...
		return -1;
#if 0
	if(abs(node2-node1) != 1)		// not adjacent...
		if(abs(node2-node1) != ROWL)
			if(abs(node2-node1) != (ROWL-1))	// circular (horizontal)
				if(abs(node2-node1) != (ROWL*(NROWS-1)))	// circular (vertical)
					return -1;
#endif
//	if(((node1%ROWL) == 0) && ((node2%ROWL) == ROWL-1))	// wraparound...
//		return -1;
//	if(((node2%ROWL) == 0) && ((node1%ROWL) == ROWL-1))	// wraparound...
//		return -1;
	dominos[ndominos].exists = 1;	// mark as existent...
	dominos[ndominos].atnode1 = node1;
	dominos[ndominos].atnode2 = node2;
	nodes[node1].occ = ndominos;
	nodes[node2].occ = ndominos;

#if CLOCK
	dominos[ndominos].clock = 0;
#endif
	dominos[ndominos].color = col;
	++ndominos;
	return ndominos;
}

// create a domino at location node1, with given orientation , return its index...
// 0 - second node is down from node1  1 - second node is right from node1
// 2 - second node is up   from node1  3 - second node is left  from node1
// create with a particular color...
long createdomoc(long node1,long orient,long col)
{
long node2;
	if(nodes[node1].occ >= 0)	// somebody already there...
		return -1;
	node2 = nodes[node1].Nbrs[orient];
	if(nodes[node2].occ >= 0)	// somebody already there...
		return -1;
	if((node1 >= NMAX) || (node2 >= NMAX))	// off the grid...
		return -1;
	if((node1 < 0) || (node2 < 0))	// off the grid...
		return -1;

	dominos[ndominos].exists = 1;	// mark as existent...
	dominos[ndominos].atnode1 = node1;
	dominos[ndominos].atnode2 = node2;
	nodes[node1].occ = ndominos;
	nodes[node2].occ = ndominos;
	dominos[ndominos].color = col;
	#if CLOCK
	dominos[ndominos].clock = 0;
	#endif
	++ndominos;
	return ndominos;
}
#if 0
// remove the domino which has a square on "node", if there is one.
// returns ndominos if domino removed, -1 if nothing there.
long removedomino(long node)
{
long nn,at;

	nn = nodes[node].occ;		// look up domino at node
	
	if(nn == -1)				// nobody home!
		return -1;
	
	at = dominos[nn].atnode1;	// clear domino from nodes[]
	nodes[at].occ = -1;
	at = dominos[nn].atnode2;
	nodes[at].occ = -1;
		
	--ndominos;					// move domino at end of list onto removed domino
	dominos[nn].atnode1 = dominos[ndominos].atnode1;
	dominos[nn].atnode2 = dominos[ndominos].atnode2;
	
	return ndominos;			// all done!
}

// remove domino number nn, if there is one.
// returns ndominos if domino removed, -1 if nn too big.
long removedominonum(long nn)
{
long at;

	if(nn >= ndominos)				// not that many!
		return -1;
	
	at = dominos[nn].atnode1;	// clear domino from nodes[]
	nodes[at].occ = -1;
	at = dominos[nn].atnode2;
	nodes[at].occ = -1;
		
	--ndominos;					// move domino at end of list onto removed domino
	dominos[nn].atnode1 = dominos[ndominos].atnode1;
	dominos[nn].atnode2 = dominos[ndominos].atnode2;
	dominos[nn].color = dominos[ndominos].color;
	#if CLOCK
	dominos[nn].clock = dominos[ndominos].clock;
	#endif
	
	return ndominos;			// all done!
}
#endif
// remove the domino which has a square on "node", if there is one.
// returns ndominos if domino removed, -1 if nothing there.
long removedomino(long node)
{
long nn,at;

	nn = nodes[node].occ;		// look up domino at node
	
	if(nn == -1)				// nobody home!
		return -1;
	
	at = dominos[nn].atnode1;	// clear domino from nodes[]
	nodes[at].occ = -1;
	at = dominos[nn].atnode2;
	nodes[at].occ = -1;
		
	--ndominos;
	if(nn != ndominos)			// if we didn't happen to delete the last domino on the list
		{						// move domino at end of list onto removed domino
		//dominos[nn].atnode1 = dominos[ndominos].atnode1;
		//dominos[nn].atnode2 = dominos[ndominos].atnode2;
		at = dominos[ndominos].atnode1;
		dominos[nn].atnode1 = at;
		nodes[at].occ = nn;		// also change domino number in nodes[].occ!
		at = dominos[ndominos].atnode2;
		dominos[nn].atnode2 = at;
		nodes[at].occ = nn;
		dominos[nn].color = dominos[ndominos].color;
		#if CLOCK
		dominos[nn].clock = dominos[ndominos].clock;
		#endif
		}
	
	return ndominos;			// all done!
}

// remove domino number nn, if there is one.
// returns ndominos if domino removed, -1 if nn too big.
long removedominonum(long nn)
{
long at;

	if(nn >= ndominos)				// not that many!
		return -1;
	
	at = dominos[nn].atnode1;	// clear domino from nodes[]
	nodes[at].occ = -1;
	at = dominos[nn].atnode2;
	nodes[at].occ = -1;
		
	--ndominos;
	if(nn != ndominos)			// if we didn't happen to delete the last domino on the list
		{						// move domino at end of list onto removed domino
//		dominos[nn].atnode1 = dominos[ndominos].atnode1;
//		dominos[nn].atnode2 = dominos[ndominos].atnode2;
		at = dominos[ndominos].atnode1;
		dominos[nn].atnode1 = at;
		nodes[at].occ = nn;		// also change domino number in nodes[].occ!
		at = dominos[ndominos].atnode2;
		dominos[nn].atnode2 = at;
		nodes[at].occ = nn;
		dominos[nn].color = dominos[ndominos].color;
		#if CLOCK
		dominos[nn].clock = dominos[ndominos].clock;
		#endif
		}
	
	return ndominos;			// all done!
}

// attempt to add n dominos at random positions.
#define MAXY 1000000
long addtoem(long n)
{
long VacantNode[NMAX];
long i,ii=0,r1,r2,target,nn;

for(i=0;i<NMAX;i++)
	{
	if(nodes[i].occ == -1)	// make list of free nodes
		VacantNode[ii++] = i;
	}
//printf("free nodes %d\n",ii);
//printf("node 0 %d\n",VacantNode[0]);
//printf("node ii-1 %d\n",VacantNode[ii-1]);
target = ndominos + n;

for(i=0;i<MAXY;i++)
	{
	r1 = n_rand(ii);
	r1 = VacantNode[r1];
	r2 = n_rand(4);
//	if(i == 0) printf("%d %d\n",r1,r2);
	
	if(r2 == 0)
		{
		if(r1 < ROWL)
			nn = createdominoc(r1,r1+(NROWS-1)*ROWL,RED);
		else
			nn = createdominoc(r1,r1-ROWL,RED);
		}
	else if(r2 == 1)
		{
		if(r1%ROWL == (ROWL-1))
			nn = createdominoc(r1,r1-ROWL+1,RED);
		else
			nn = createdominoc(r1,r1+1,RED);
		}
	else if(r2 == 2)
		{
		if(r1 > (NROWS-1)*ROWL)
			nn = createdominoc(r1,r1%ROWL,RED);
		else
			nn = createdominoc(r1,r1+ROWL,RED);
		}
	else
		{
		if(r1%ROWL == 0)
			nn = createdominoc(r1,r1+ROWL-1,RED);
		else
			nn = createdominoc(r1,r1-1,RED);
		}
	if(nn == target)
		{
		desired = ndominos;
		return(ndominos);
		}
	}
desired = ndominos;
return ndominos;
}

// remove n dominos from random positions.
long subfromem(long n)
{
long i,rnd;

for(i=0;i<n;i++)
	{
	rnd = n_rand(ndominos);
	removedominonum(rnd);
	}
desired = ndominos;
return ndominos;
}

// make one domino at lattice position n.
long initdomino0(long n)
{
long i;

ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
createdomino(n,n+1);
//createdomino(n,n+ROWL);
return ndominos;
}

// add dominos if possible into nodes at top of domain,
// if density computed over the top "nrws" rows is
// less than "dense".
// don't include top row in density calculation...
long sourceline(long nrws, float dense)
{
    long i,j,iaddr,dcnt=0,nadd,arem=0;
    long Nlist[ROWL];
    float mdens;

    iaddr = (NROWS-nrws)*ROWL;
    iaddr -= ROWL;						// don't include top row!
    for(j=0;j<nrws;j++)					// count number in top nrws
	for(i=0;i<ROWL;i++)
	    {
		if(nodes[iaddr++].occ > -1)
		    {
			//printf("node %d\n",nodes[iaddr].occ);
			++dcnt;
		    }
	    }

    mdens = (float)dcnt/(float)(nrws*ROWL);
    //if(altctl)
    //printf("%f\n",mdens);
    nadd = dense*nrws*ROWL - dcnt;		// number to add (can be negative)
#if 0
    if(altctl)
	{
	    if(nadd > 0)
		{
		    printf("%f\n", mdens);
		    printf("%d dcnt  %d nadd\n",dcnt,nadd);
		    --altctl;
		}
	}
#endif
    if(nadd < 0) return 0;
    //printf("nadd %d   ",nadd);

    for(i=0;i<ROWL;i++)				// construct list of highest row nodes
	Nlist[i] = i+(NROWS-10)*ROWL;

    shuffle(Nlist,ROWL);			// shuffle the list

    i = 0;
    while(nadd > 0)
	{
	    int occ;
	
	    iaddr = Nlist[i++];
	    occ = nodes[iaddr].occ;
	    if(occ == -1)
		{
		    long rtn;
		    rtn = createdominoc(iaddr,iaddr+1,RED);
		    //rtn = createdominoc(iaddr,iaddr-ROWL,RED);
		    if(rtn != -1)			// domino successfully added
			{
			    //--nadd;
			    nadd -= 2;			// 2 nodes per domino!
			    ++arem;				// number actually added
			}
		}
	    if(i==ROWL) break;
	}
    //createdominoc(100,101,RED);
    //printf("arem %d\n",arem);
    return arem;

}

// add "ndoms" dominos if possible into nodes at top of domain,
// start "startrow" down...
long sourceline2(long nrws, long startrow, long ndoms)
{
long i,iaddr,arem=0;
long Nlist[NROWS*ROWL];

iaddr = (NROWS-startrow-nrws+1)*ROWL;		// starting point for list

for(i=0;i<nrws*ROWL;i++)					// construct list of highest row nodes
	Nlist[i] = iaddr++;

shuffle(Nlist,nrws*ROWL);					// shuffle the list

i = 0;
arem = 0;

while(ndoms > 0)		// add dominos if necessary
//if(ndoms > 0)			// try just adding one per call
	{
	int occ;
	
	iaddr = Nlist[i++];
	occ = nodes[iaddr].occ;
		if(occ == -1)
		{
		long rtn,orient;
		orient = n_rand4();					// generate random orientation
		rtn = createdomoc(iaddr,orient,RED);
		if(rtn != -1)						// domino successfully added
			{
			--ndoms;
			++arem;							// number actually added
			}
		}
	if(i==nrws*ROWL) break;
	}

return arem;
}

// add "ndoms" dominos if possible into nodes at top of domain,
// start "startrow" down...
// add only horizontal dominos
long sourceline2h(long nrws, long startrow, long ndoms)
{
long i,iaddr,arem=0;
long Nlist[NROWS*ROWL];

iaddr = (NROWS-startrow-nrws+1)*ROWL;		// starting point for list

for(i=0;i<nrws*ROWL;i++)					// construct list of highest row nodes
	Nlist[i] = iaddr++;

shuffle(Nlist,nrws*ROWL);					// shuffle the list

i = 0;
arem = 0;

while(ndoms > 0)		// add dominos if necessary
//if(ndoms > 0)			// try just adding one per call
	{
	int occ;
	
	iaddr = Nlist[i++];
	occ = nodes[iaddr].occ;
		if(occ == -1)
		{
		long rtn,orient;
		orient = n_rand4();					// generate random orientation
		if(orient == 0) orient = 1;			// set horizontal if vertical
		if(orient == 2) orient = 3;
		rtn = createdomoc(iaddr,orient,RED);
		if(rtn != -1)						// domino successfully added
			{
			--ndoms;
			++arem;							// number actually added
			}
		}
	if(i==nrws*ROWL) break;
	}

return arem;
}

// add "ndoms" dominos if possible into nodes at top of domain,
// start "startrow" down...
// add only vertical dominos
long sourceline2v(long nrws, long startrow, long ndoms)
{
long i,iaddr,arem=0;
long Nlist[NROWS*ROWL];

iaddr = (NROWS-startrow-nrws+1)*ROWL;		// starting point for list

for(i=0;i<nrws*ROWL;i++)					// construct list of highest row nodes
	Nlist[i] = iaddr++;

shuffle(Nlist,nrws*ROWL);					// shuffle the list

i = 0;
arem = 0;

while(ndoms > 0)		// add dominos if necessary
//if(ndoms > 0)			// try just adding one per call
	{
	int occ;
	
	iaddr = Nlist[i++];
	occ = nodes[iaddr].occ;
		if(occ == -1)
		{
		long rtn,orient;
		orient = n_rand4();					// generate random orientation
		if(orient == 1) orient = 0;			// set vertical if horizontal
		if(orient == 3) orient = 2;
		rtn = createdomoc(iaddr,orient,RED);
		if(rtn != -1)						// domino successfully added
			{
			--ndoms;
			++arem;							// number actually added
			}
		}
	if(i==nrws*ROWL) break;
	}

return arem;
}

// the top two rows of the domain consist of staggered vertical dominos.
// if any domino location becomes completely vacant, it is immediately replaced.
// the number of dominos actually added is returned.
long sourceline3v()
{
long nadd = 0,iaddr;
long i,altctl=1;

iaddr = ROWL*(NROWS-1);

for(i=0;i<ROWL;i++)
	{
	if(altctl)		// up against top boundary
		{
		
		if(createdomoc(iaddr+i,0,RED) > 0)
			++nadd;
		}
	else			// one space down from top
		{
		if(createdomoc(iaddr-ROWL+i,0,RED) > 0)
			++nadd;
		}
	altctl ^= 1;
	}
return nadd;
}

// simple attempt to add horizontal dominos at the top row
long sourceline3h()
{
long i,nadd = 0,iaddr;

iaddr = ROWL*(NROWS-1);

for(i=0;i<ROWL;i++)
	{
	if(createdomoc(iaddr+i,1,RED) > 0)
		++nadd;
	}
return nadd;
}

#define IOFFF 1
// finds vacancies, shuffles, then shoves in n.
long adddominos(long num)
{
    long i,j,nvacant,tst,numplaced;
	long VacantNode[NMAX];
//	long r1,r2,rv,rrv;
//	long rLkup[NMAX];
//	long k,rr;
	long offset = IOFFF*ROWL;

	myrand();
//myrand();
	
// mark bottom IOFFF rows "occupied"
	for(i=0;i<offset;i++)
		if(nodes[i].occ == -1)
			nodes[i].occ = 3000000;

// construct shuffled list of vacant nodes...	
	nvacant = 0;
	for(j=0;j<NMAX;j++)
	{
		if(nodes[j].occ == -1)
		{
			VacantNode[nvacant] = j;
			++nvacant;
		}
	}
shuffle(VacantNode,nvacant);
shuffle(VacantNode,nvacant);
shuffle(VacantNode,nvacant);
shuffle(VacantNode,nvacant);
	shuffle(VacantNode,nvacant);
	if(num>nvacant) num = nvacant;
	numplaced = num;
	for(j=0,i=0;i<num && j<nvacant;j++,i++){
	    while((tst = createdominoc(VacantNode[j],VacantNode[j]+1,RED))
		  == -1){
		    j++;	// go to next vacancy
		    if(j == nvacant){ 
			fprintf(stderr,"warning: couldn't place.\n");
			numplaced = i+1;
			break;	// and will now quit loop
		    }
		}
	}

//clearem:	// mark bottom IOFFF rows free
for(i=0;i<offset;i++)
	if(nodes[i].occ == 3000000)
		nodes[i].occ = -1;

	return numplaced;
}

// remove dominos if possible from nodes at bottom of domain,
// if density computed over the bottom "nrws" rows is
// greater than "dense".

long sinkline(long nrws, float dense)
{
long i,j,iaddr=0,dcnt=0,nrem,arem=0;
long Nlist[ROWL];

for(j=0;j<nrws;j++)					// count number in bottom nrws
	for(i=0;i<ROWL;i++)
		{
		if(nodes[iaddr++].occ > -1)
			++dcnt;
		}

nrem = dcnt - dense*nrws*ROWL;		// number to remove (can be negative)
if(nrem < 0) return 0;

for(i=0;i<ROWL;i++)				// construct list of lowest row nodes
	Nlist[i] = i;

shuffle(Nlist,ROWL);			// shuffle the list

i = 0;
while(nrem > 0)
	{
	int occ;
	
	iaddr = Nlist[i++];
	occ = nodes[iaddr].occ;
	if(occ > -1)
		{
		removedominonum(occ);
		--nrem;
		++arem;					// number actually removed
		}
	if(i==ROWL) break;
	}

return arem;		
}

long sinkall(long nrws)			// like sinkline with dense=0
{
	long i,j,arem=0,nn,idx;

	for(j=0;j<nrws;j++)
	    for(i=0;i<ROWL;i++)
		{
		    idx = j*ROWL+i;
		    nn = nodes[idx].occ;
		    if(nn > -1)
			{				
			    removedominonum(nn);
			    arem++;
			}
		}	
	return arem;		
}


// remove dominos if possible from nodes at bottom of domain,
// and correctly update the "domino" and "nodes" structures!
// examine the lowest nrws rows.
// return number actually removed.
long sinkline1(long nrws)
{
long i,j,iaddr=0,arem=0,occ;

for(j=0;j<nrws;j++)					// count number in bottom nrws
	for(i=0;i<ROWL;i++)
		{
		if((occ = nodes[iaddr++].occ) > -1)
			{
			removedominonum(occ);
			++arem;
			}
		}

return arem;		
}


// count number of filled nodes in "nlines" lines,
// starting at row "nrow".
long countem(long nlines, long nrow)
{
long i,j,cnt,idx;

cnt = 0;
idx = ROWL*nrow;
for(j=0;j<nlines;j++)
	for(i=0;i<ROWL;i++)
		if(nodes[idx++].occ != -1) ++cnt;

return cnt;
}

// count number of filled nodes in "nlines" lines,
// starting at row "nrow".
// count number of dominos in horizontal and vertical
// orientations.  vertical dominos which are halfway
// in the region are only counted at the upper edge.
long countem1(long nlines, long nrow, long *horiz, long *vert)
{
long i,j,cnt,idx,num;

cnt = 0;*horiz=*vert=0;
//idx = ROWL*nrow;
for(j=0;j<nlines;j++)
	for(i=0;i<ROWL-1;i++)
		{
		idx = ROWL*(nrow+j) + i;
		num = nodes[idx].occ;
		if(num != -1)
			{
			//++cnt;
			if(num != 1000000)	// actually a domino
				{
				++cnt;
				//if(i==ROWL-1)	// end of row
				///	{
					if(nodes[idx+1].occ == num)
						++(*horiz);	// found a horizontal domino
				//	}
				//else
				//	{
				//if(nodes[idx+1-ROWL].occ == num)
				//	++(*horiz);	// found a horizontal domino
				//	}
				if(nodes[idx+ROWL].occ == num)
					++(*vert);	// found a vertical
					
					
				//if(nodes[idx-ROWL].occ == num)
				//	if(j != 0)	// don't count lower edge
				//		++(*vert);	// found a vertical
				}
			}
//		++idx;
		}
return cnt;
}

// try to make n dominos, horizontal lined up from bottom.
long initdomino1(long n)
{
long i,j,nn;

ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
for(j=0;j<NROWS;j++)
	for(i=0;i<ROWL-1;i+=2)
		{
		long index;
		index = j*ROWL + i;
		nn = createdomino(index,index+1);
		if(nn == n) return(ndominos);
		}
return ndominos;
}

// try to make n dominos, vertical lined up from bottom, offset
long initdomino2(long n)
{
long i,nn;

ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
for(i=0;i<NMAX-ROWL;i+=2)
	{
	nn = createdomino(i,i+ROWL);
	if(nn == n) return(ndominos);
	}
return ndominos;
}

// try to make n dominos, vertical lined up from bottom, not offset
long initdomino2a(long n)
{
long i,nn;

ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
for(i=0;i<NMAX-ROWL;i++)
	{
	//nn = createdomino(i,i+ROWL);
	nn = createdominoc(i,i+ROWL,RED);
	if(nn == n) return(ndominos);
	}
return ndominos;
}

// try to make n dominos, vertical lined up from left, not offset
long initdomino2b(long n)
{
long i,j,nn;

ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
for(i=0;i<ROWL;i++)
	{
	for(j=0;j<NROWS-1;j+=2)
		{
		//nn = createdomino(j*ROWL+i,j*ROWL+i+ROWL);
		nn = createdominoc(j*ROWL+i,j*ROWL+i+ROWL,RED);
		if(nn == n) return(ndominos);
		}
	}
return ndominos;
}

// try to make n dominos, vertical lined up from left, not offset
// color the first nblue dominos blue
long initdomino2c(long n,long nblue)
{
long i,j,nn;

ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
for(i=0;i<ROWL;i++)
	{
	for(j=0;j<NROWS-1;j+=2)
		{
		nn = createdomino(j*ROWL+i,j*ROWL+i+ROWL);
		// maybe should put in creatdomino()...
		if(nn <= nblue)
			//dominos[nn-1].color = 1;
			dominos[nn-1].color = BLUE;
		else
			//dominos[nn-1].color = 0;
			dominos[nn-1].color = RED;
		if(nn == n) return(ndominos);
		}
	}
return ndominos;
}

// try to make n dominos, randomly positioned!
//#define MAXTRIES 160000
//#define MAXTRIES 4000000
#define MAXTRIES 1000000
long initdomino3(long n)
{
long i,nn=0,r1,r2;
//register unsigned long _seed = myseedy;

//_seed = myseedy;
ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
for(i=0;i<MAXTRIES;i++)
	{
	r1 = n_rand(NMAX);
	r2 = n_rand(4);
	//if(i == 0) printf("%d %d\n",r1,r2);
	if(r2 == 0)
		//nn = createdomino(r1,r1+ROWL);
		nn = createdominoc(r1,r1+ROWL,RED);
		//nn = createdomino(r1+ROWL,r1);
	if(r2 == 1)
		//nn = createdomino(r1,r1+1);
		nn = createdominoc(r1,r1+1,RED);
	if(r2 == 2)
		//nn = createdomino(r1,r1-ROWL);
		//nn = createdomino(r1-ROWL,r1);
		nn = createdominoc(r1,r1-ROWL,RED);
	if(r2 == 3)
		//nn = createdomino(r1,r1-1);
		//nn = createdomino(r1-1,r1);
		nn = createdominoc(r1-1,r1,RED);
	if(nn == n) return(ndominos);
	}
//myseedy = _seed;
return ndominos;
}

// try to make n randomly positioned dominos.
// this version keeps a list of vacant nodes,
// and only checks these.
// further, when it becomes impossible to add
// any more because there are no more vacancies
// that are adjacent, a stepdomino() rule is
// applied to hopefully generate more domino-shaped
// spaces.
#define NTRIALS 20000		// number of times to try and apply dynamics
#define NITERS	1		// number of sweep steps each trial

long initdomino4(long n)
{
long i,j,nvacant,fillctl,nn=0,jj;
long VacantNode[NMAX],VacantNbr[4];
long r1,r2,rv,rrv;
long rLkup[NMAX];
long k,rr;

myrand();
//myrand();
ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
// construct shuffled list of vacant nodes...
nvacant = NMAX;
////nvacant = ROWL*(NROWS-offset);

for(i=0;i<NMAX;i++)
////for(i=0;i<NMAX-offset*ROWL;i++)
	VacantNode[i] = i;
////	VacantNode[i] = i + offset*ROWL;
shuffle(VacantNode,NMAX);
shuffle(VacantNode,NMAX);
shuffle(VacantNode,NMAX);
// construct lookup table of entries...
for(i=0;i<NMAX;i++)
////for(i=0;i<NMAX-offset*ROWL;i++)
	{
	long index;
	index = VacantNode[i];
	////index = VacantNode[i]-offset*ROWL;
	rLkup[index] = i;
	}

//nnbr = 4;
for(i=0;i<4;i++)
	VacantNbr[i] = i;

while(nvacant > 0)
	{
	fillctl = 0;
	--nvacant;
	r1 = VacantNode[nvacant];
//	printf("r1 %d  nvacant %d  ii %d  n %d\n",r1,nvacant,ii,n);
//	if(nodes[r1].occ != -1)	// node free, check nbrs (should always be free here)
//		{					// (unless an object present)
//		printf("wha!\n");
//		sleep(4);
//		}
	i = n_rand(12);
	//i = 1;
	for(j=0;j<i;j++)
		shuffle(VacantNbr,4);
	for(j=0;j<4;j++)
//	for(j=0;j<1;j++)		// "true" random over checkerboard?...
		{
		jj = VacantNbr[j];
		r2 = nodes[r1].Nbrs[jj];
		if(nodes[r2].occ == -1)	// node free, install domino
			{
			switch(jj)	// establish orientation...
				{
				case 0:
				case 3:
					//nn = createdomino(r2,r1);
					nn = createdominoc(r2,r1,RED);
					break;
				case 1:
				case 2:
					//nn = createdomino(r1,r2);
					nn = createdominoc(r2,r1,RED);
				}
			// find r2 on VacantNode list...
			rv = rLkup[r2];
			// shrink VacantNode[] list...
			--nvacant;
			rrv = VacantNode[nvacant];
			VacantNode[rv] = rrv;
			rLkup[rrv] = rv;
			fillctl = 1;
			break;
			}
		}
	if(nn == n) return(ndominos);
	}
//  if we arrived here, we weren't able to place
//  n dominos on the domain.  apply some dynamics.
for(i=0;i<NTRIALS;i++)
	{
	for(j=0;j<NITERS;j++)
		{
		for(k=0;k<ndominos;k++)
			{
			rr = n_rand(ndominos);
			//nn = stepdomino2(rr);
			stepdomino2(rr);
			}
		}
	// construct shuffled list of vacant nodes...
	nvacant = 0;
	for(j=0;j<NMAX;j++)
		{
		if(nodes[j].occ == -1)
			{
			VacantNode[nvacant] = j;
			++nvacant;
			}
		}
	shuffle(VacantNode,nvacant);
	//printf("nvacant %d  ndominos %d\n",nvacant, ndominos);
	//printf("%d\n",NMAX-2*ndominos);
	
	// construct lookup table of entries...
	for(j=0;j<nvacant;j++)
		{
		long index;
		index = VacantNode[j];
		rLkup[index] = j;
		}

	for(j=0;j<4;j++)
		VacantNbr[j] = j;
		
		

		
	while(nvacant > 0)
		{
		--nvacant;
		r1 = VacantNode[nvacant];
//		if(nodes[r1].occ != -1)	// node free, check nbrs (should always be free here)
//			{					// (unless obstacles present)
//			printf("wha!\n");
//			sleep(4);
//			}
		shuffle(VacantNbr,4);
		for(j=0;j<4;j++)
			{
			jj = VacantNbr[j];
			r2 = nodes[r1].Nbrs[jj];
			if(nodes[r2].occ == -1)	// node free, install domino
				{
				switch(jj)	// establish orientation...
					{
					case 0:
					case 3:
						//nn = createdomino(r2,r1);
						nn = createdominoc(r2,r1,RED);
						break;
					case 1:
					case 2:
						//nn = createdomino(r1,r2);
						nn = createdominoc(r2,r1,RED);
					}
				// find r2 on VacantNode list...
				rv = rLkup[r2];
				// shrink VacantNode[] list...
				--nvacant;
				rrv = VacantNode[nvacant];
				VacantNode[rv] = rrv;
				rLkup[rrv] = rv;
				break;
				}
			}
		if(nn == n) return(ndominos);
		}
	
	}
return ndominos;
}

#if 0
// this one only fills the top, leaves the bottom
// IOFF rows domino-free...
#define IOFF 80
long initdomino4a(long n)
{
long i,j,nvacant,fillctl,nn,jj;
long VacantNode[NMAX],VacantNbr[4];
long r1,r2,rv,rrv;
long rLkup[NMAX];
long k,rr;
long offset = IOFF*ROWL;

myrand();
//myrand();
ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
// construct shuffled list of vacant nodes...
//nvacant = NMAX;
nvacant = ROWL*(NROWS-IOFF);

//for(i=0;i<NMAX;i++)
for(i=0;i<NMAX-offset;i++)
	{
	VacantNode[i] = i;
	//printf("%d\n",VacantNode[i]);
	}
shuffle(VacantNode,NMAX-offset);
shuffle(VacantNode,NMAX-offset);
shuffle(VacantNode,NMAX-offset);
// construct lookup table of entries...
//for(i=0;i<NMAX;i++)
for(i=0;i<NMAX-offset;i++)
	{
	long index;
	index = VacantNode[i];
	//index = VacantNode[i]-offset;
	
	rLkup[index] = i;
	}

//nnbr = 4;
for(i=0;i<4;i++)
	VacantNbr[i] = i;

while(nvacant > 0)
	{
	fillctl = 0;
	--nvacant;
	r1 = VacantNode[nvacant];
	//printf("r1 %d  nvacant %d   n %d\n",r1,nvacant,n);
//	if(nodes[r1].occ != -1)	// node free, check nbrs (should always be free here)
//		{					// (unless obstacles present)
//		printf("wha!\n");
//		sleep(4);
//		}
	i = n_rand(12);
	//i = 1;
	for(j=0;j<i;j++)
		shuffle(VacantNbr,4);
	for(j=0;j<4;j++)
//	for(j=0;j<1;j++)		// "true" random over checkerboard?...
		{
		jj = VacantNbr[j];
		r2 = nodes[r1].Nbrs[jj];
		if(nodes[r2].occ == -1)	// node free, install domino
			{
			switch(jj)	// establish orientation...
				{
				case 0:
				case 3:
					//nn = createdomino(r2,r1);
					nn = createdominoc(r2,r1,RED);
					break;
				case 1:
				case 2:
					//nn = createdomino(r1,r2);
					nn = createdominoc(r1,r2,RED);
				}
			// find r2 on VacantNode list...
			rv = rLkup[r2];
			// shrink VacantNode[] list...
			--nvacant;
			rrv = VacantNode[nvacant];
			VacantNode[rv] = rrv;
			rLkup[rrv] = rv;
			fillctl = 1;
			break;
			}
		}
	//if(nn == n) return(ndominos);
	if(nn == n) goto swapem;
	}
//  if we arrived here, we weren't able to place
//  n dominos on the domain.  apply some dynamics.
for(i=0;i<NTRIALS;i++)
	{
	for(j=0;j<NITERS;j++)
		{
		for(k=0;k<ndominos;k++)
			{
			rr = n_rand(ndominos);
			nn = stepdomino2(rr);
			}
		}
	// construct shuffled list of vacant nodes...
	nvacant = 0;
	for(j=0;j<NMAX;j++)
		{
		if(nodes[j].occ == -1)
			{
			VacantNode[nvacant] = j;
			++nvacant;
			}
		}
	shuffle(VacantNode,nvacant);
	//printf("nvacant %d  ndominos %d\n",nvacant, ndominos);
	//printf("%d\n",NMAX-2*ndominos);
	
	// construct lookup table of entries...
	for(j=0;j<nvacant;j++)
		{
		long index;
		index = VacantNode[j];
		rLkup[index] = j;
		}

	for(j=0;j<4;j++)
		VacantNbr[j] = j;
		
	while(nvacant > 0)
		{
		--nvacant;
		r1 = VacantNode[nvacant];
//		if(nodes[r1].occ != -1)	// node free, check nbrs (should always be free here)
//			{					// (unless obstacles present)
//			printf("wha!\n");
//			sleep(4);
//			}
		shuffle(VacantNbr,4);
		for(j=0;j<4;j++)
			{
			jj = VacantNbr[j];
			r2 = nodes[r1].Nbrs[jj];
			if(nodes[r2].occ == -1)	// node free, install domino
				{
				switch(jj)	// establish orientation...
					{
					case 0:
					case 3:
						//nn = createdomino(r2,r1);
						nn = createdominoc(r2,r1,RED);
						break;
					case 1:
					case 2:
						//nn = createdomino(r1,r2);
						nn = createdominoc(r2,r1,RED);
					}
				// find r2 on VacantNode list...
				rv = rLkup[r2];
				// shrink VacantNode[] list...
				--nvacant;
				rrv = VacantNode[nvacant];
				VacantNode[rv] = rrv;
				rLkup[rrv] = rv;
				break;
				}
			}
		//if(nn == n) return(ndominos);
		if(nn == n) goto swapem;
		}
	
	}
swapem:	// move dominos up IOFF rows...
#if 1
for(i=0;i<ndominos;i++)
	{
	long iy,ix,iold,inew;
	iold = dominos[i].atnode1;
	ix = iold%ROWL;
	iy = iold/ROWL;
	iy += IOFF;
	if(iy >= NROWS) iy -= NROWS;
	inew = ROWL*iy + ix;
	dominos[i].atnode1 = inew;
	nodes[iold].occ = -1;
	nodes[inew].occ = i;
	
	iold = dominos[i].atnode2;
	ix = iold%ROWL;
	iy = iold/ROWL;
	iy += IOFF;
	if(iy >= NROWS) iy -= NROWS;
	inew = ROWL*iy + ix;
	dominos[i].atnode2 = inew;
	nodes[iold].occ = -1;
	nodes[inew].occ = i;
	}
#endif
return ndominos;
}
#endif

// this one only fills the top, leaves the bottom
// IOFF rows domino-free...
// call object-adding routines after this one,
// as this one messes with nodes[i].occ
// that problem fixed...
//#define IOFF 50
#define IOFF (MTHICK+CHAMB1+0)
long initdomino4a(long n)
{
long i,j,nvacant,fillctl,nn=0,jj;
long VacantNode[NMAX],VacantNbr[4];
long r1,r2,rv,rrv;
long rLkup[NMAX];
long k,rr;
long offset = IOFF*ROWL;

myrand();
//myrand();
ndominos = 0;
for(i=0;i<NDOMS;i++)
	dominos[i].exists = 0;
	
// mark bottom IOFF rows "occupied"
for(i=0;i<offset;i++)
	if(nodes[i].occ == -1)
		nodes[i].occ = 2000000;

// construct shuffled list of vacant nodes...	
nvacant = 0;
for(j=0;j<NMAX;j++)
	{
	if(nodes[j].occ == -1)
		{
		VacantNode[nvacant] = j;
		++nvacant;
		}
	}
shuffle(VacantNode,NMAX-offset);

// construct lookup table of entries...
for(i=0;i<nvacant;i++)
	{
	long index;
	index = VacantNode[i];
	rLkup[index] = i;
	}

//nnbr = 4;
for(i=0;i<4;i++)
	VacantNbr[i] = i;

while(nvacant > 0)
	{
	fillctl = 0;
	--nvacant;
	r1 = VacantNode[nvacant];
	//printf("r1 %d  nvacant %d   n %d\n",r1,nvacant,n);
//	if(nodes[r1].occ != -1)	// node free, check nbrs (should always be free here)
//		{					// (unless obstacles present)
//		printf("wha! %d\n",nodes[r1].occ);
//		sleep(4);
//		}
	i = n_rand(12);
	//i = 1;
	for(j=0;j<i;j++)
		shuffle(VacantNbr,4);
	for(j=0;j<4;j++)
//	for(j=0;j<1;j++)		// "true" random over checkerboard?...
		{
		jj = VacantNbr[j];
		r2 = nodes[r1].Nbrs[jj];
		if(nodes[r2].occ == -1)	// node free, install domino
			{
			switch(jj)	// establish orientation...
				{
				case 0:
				case 3:
					//nn = createdomino(r2,r1);
					nn = createdominoc(r2,r1,RED);
					break;
				case 1:
				case 2:
					//nn = createdomino(r1,r2);
					nn = createdominoc(r1,r2,RED);
				}
			// find r2 on VacantNode list...
			rv = rLkup[r2];
			// shrink VacantNode[] list...
			--nvacant;
			rrv = VacantNode[nvacant];
			VacantNode[rv] = rrv;
			rLkup[rrv] = rv;
			fillctl = 1;
			break;
			}
		}
	//if(nn == n) return(ndominos);
	if(nn == n) goto clearem;
	}
//  if we arrived here, we weren't able to place
//  n dominos on the domain.  apply some dynamics.
for(i=0;i<NTRIALS;i++)
	{
	for(j=0;j<NITERS;j++)
		{
		for(k=0;k<ndominos;k++)
			{
			rr = n_rand(ndominos);
			//nn = stepdomino2(rr);
			stepdomino2(rr);
			}
		}
	// construct shuffled list of vacant nodes...
	nvacant = 0;
	for(j=0;j<NMAX;j++)
		{
		if(nodes[j].occ == -1)
			{
			VacantNode[nvacant] = j;
			++nvacant;
			}
		}
	shuffle(VacantNode,nvacant);
	//printf("nvacant %d  ndominos %d\n",nvacant, ndominos);
	//printf("%d\n",NMAX-2*ndominos);
	
	// construct lookup table of entries...
	for(j=0;j<nvacant;j++)
		{
		long index;
		index = VacantNode[j];
		rLkup[index] = j;
		}

	for(j=0;j<4;j++)
		VacantNbr[j] = j;
		
	while(nvacant > 0)
		{
		--nvacant;
		r1 = VacantNode[nvacant];
		if(nodes[r1].occ != -1)	// node free, check nbrs (should always be free here)
//			{					// (unless obstacles present)
//			printf("wha! (#2)\n");
//			sleep(4);
//			}
		shuffle(VacantNbr,4);
		for(j=0;j<4;j++)
			{
			jj = VacantNbr[j];
			r2 = nodes[r1].Nbrs[jj];
			if(nodes[r2].occ == -1)	// node free, install domino
				{
				switch(jj)	// establish orientation...
					{
					case 0:
					case 3:
						//nn = createdomino(r2,r1);
						nn = createdominoc(r2,r1,RED);
						break;
					case 1:
					case 2:
						//nn = createdomino(r1,r2);
						nn = createdominoc(r2,r1,RED);
					}
				// find r2 on VacantNode list...
				rv = rLkup[r2];
				// shrink VacantNode[] list...
				--nvacant;
				rrv = VacantNode[nvacant];
				VacantNode[rv] = rrv;
				rLkup[rrv] = rv;
				break;
				}
			}
		//if(nn == n) return(ndominos);
		if(nn == n) goto clearem;
		}
	
	}
clearem:	// mark bottom IOFF rows free
for(i=0;i<offset;i++)
	if(nodes[i].occ == 2000000)
		nodes[i].occ = -1;

return ndominos;
}
#if 0
void initpot1()
{
  int i,idx;
  for(i=0;i<NMAX;i++) potpl[i]=0;
  for(i=0;i<ROWL;i++)			
    {
      idx = NROWS*ROWL/2+i;
      potpl[idx] = 1;
    }
}

void initpot2()			// put a well in a column (for gravity shear)
{
  int i,idx;
  for(i=0;i<NMAX;i++) potpl[i]=0;
  for(i=0;i<NROWS;i++)			
    {
      idx = i*ROWL+ROWL/2;
      potpl[idx] = 1;
      idx = i*ROWL+ROWL/2+1;
      potpl[idx] = 1;
      idx = i*ROWL+ROWL/2+2;
      potpl[idx] = 1;

    }
}

void initpotall()
{
  int i;
  for(i=0;i<NMAX;i++) potpl[i]=1;
}
#endif
