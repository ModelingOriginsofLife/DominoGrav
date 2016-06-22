//  domino.h - yet another include file
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "macsdl.h"
#include "myrand4.h"

#define REAL float
//#define SIZEX 768
//#define SIZEY 512
#define SIZEX 720
#define SIZEY 480
#define XFAC (REAL)SIZEX/SIZEY
#define RES 0		// resolution switch...
#if RES == 0
#define CELLSZ .01
#endif
#if RES == 1
#define CELLSZ .02
#endif
#if RES == 2
#define CELLSZ .04
#endif
#if RES == 3
#define CELLSZ .08
#endif
#define DOMX (long)(3.0/CELLSZ)
#define DOMY (long)(2.0/CELLSZ)

//  for a larger lattice than can be displayed, comment out the first two lines
//  and uncomment out the second two, filling in desired lattice size.  then use
//  displaypart() rather than display() in the main() program.

#define ROWL (long)(3.0/CELLSZ)
#define NROWS (long)(2.0/CELLSZ)
//#define ROWL 300
//#define NROWS 200

// #define NMAX NROWS*ROWL       // see below...
//#define NNBRS 6			// for 2-cell dominos
#define NNBRS 4			// neighbors of nodes!
//#define NNBRS 8			// neighbors of nodes! (including next-nearest)
#define NDOMS NMAX/2	// for 2-cell dominos
#define NENTS 1024	// max number of histogram entries...
#define HLOAD 100	// interval over which to accumulate histogram...
#define SLIP 1		// set to 1 for slip-type dynamics
#define OBS	 1		// set to 1 to enable obstacle display
#define FPTR 1		// set to 1 to enable function pointers
#define CLOCK 0		// set to 1 to enable domino clocks...
#define DISPLAY 1	// set to 0 to turn off display, keyboard

#define NRUNS 10	// number of data runs
#define NTRANS 20000	// transient steps before taking data...
#define NSTEPS 3000000	// total number time steps
// modernize
#define DSTEP 1000		// time steps per data point
#define SEED 400		// random number seed
#define DATAFILE "data/leak4.dat"
#define REMARK "leak into near vaccum, start with 3800 dominos, nrand() update..."
#define FXSTART 0.01
//#define FXSTART 0.9
#define FXSTEP .05
#define MTHICK 1		// membrane thickness...
#define MSPACE 4		// membrane pore spacing...
#define NPORES ((ROWL+MSPACE-2)/MSPACE)	/// number of pores...
#define CHAMB1	(NROWS/2)		// lower chamber height
//#define CHAMB2	NROWS		// upper chamber height
#define CHAMB2	10		// upper chamber height
//#define NROWS (CHAMB1+CHAMB2+MTHICK)	// set NROWS here
#define NMAX NROWS*ROWL
/***** for boltzman stuff; gravity, potential wells, etc:
BOLTZ == 0 old dominos
BOLTZ == 1 dominos w/ wait state
BOLTZ == 2 dominos w/ gravity
BOLTZ == 3 dominos w/ potential wells
**************************************/
#define BOLTZ 3

void drawdomino(long n1,long n2,long c);
void drawdominocb(long n1,long n2,long c);
void drawdominopart(long n1,long n2,long c);
void drawnode(long n,long c);
void border();
void initnodes();
void initnodescb();
void initnodes8();
void initobstacle();
long createdomino(long node1,long node2);
long createdominoc(long node1,long node2,long col);
long initdomino0(long n);
long initdomino1(long n);
long initdomino2(long n);
long initdomino2a(long n);
long initdomino2b(long n);
long initdomino2c(long n,long nblue);
long initdomino3(long n);
long initdomino4(long n);
long stepdomino(long nn);
long stepdomino1(long nn);
long stepdomino2(long nn);
void stepdomm();
void stepdomm1();
void stepdomm2();
long boltz();
long checkboltz(long index);
void initgravboltz(double temp,double grav);
void initgboltz(double temp,double grav);
unsigned long copyclearhist(unsigned long H1[],unsigned long H2[],long nents);
void ldhist0(unsigned long H[]);
void ldhist1(unsigned long H[]);
void ldhist2(unsigned long H[]);
void ldhist3(unsigned long H[]);
void plthist(unsigned long H[],long nmax,unsigned long ymax);
void display();
void displaypart();
void displaytt(long at1,long at2);
void printhz(long nstps,long ll);
long kbd();
void bail(char *str);
void getmouse(long *ix,long *iy);
void mkmbrane();
void drawbdy(long n1,long n2);
void drawbndys();
void writebrane();
void rdbrane(char *fname);
void initbrane();
void shuffle(void *Ptr,long n);
void coloremtet();
void coloremnbrs();
void coloremtop(long top,long col);
void coloremall(long col);
// long flux(struct domstate *S1,struct domstate *S2);
void setcbreak();
void unsetcbreak();
long addtoem(long n);
long subfromem(long n);
void initmem1(long thick,long space, long height);
long initdomino4a(long n);
void Display();

// node structure.
struct node{
	long occ;
	long Nbrs[NNBRS];	// list of neighbors
};
extern struct node nodes[NMAX];

////extern long freenode[NNBRS];

// object structure
struct domino{
	long exists;	// 1 means it actually exists
	long atnode1;	// where it is in configuration space...
	long atnode2;
	long color;
};
extern struct domino dominos[NDOMS];

// domino state structure
struct domstate{
	long ndominos;
	struct domino dominos[NDOMS];
};


// boundary structure
struct bndy{
	long n1;		// first node number
	long n2;		// second node number
};
extern struct bndy bndys[NMAX];

// potential well defition plane
#if BOLTZ == 3
int potpl[NMAX];
#endif

extern unsigned long Histo[NENTS],Histo1[NENTS];
extern long ndominos;
extern long nsteps;
extern long nbndys;			// number of boundary entries...
extern long slowctl;
extern long pausectl;
extern long stepctl;
extern long histctl;
extern long addctl;			// ctl to add a bndy entry...
extern long Ptot,Pav,pint;		// variables for pressure measurements...
extern long myseedy;			// random number seed
extern long altctl;
extern long freezctl;		// let only one domino move...
extern long tempctl;			// temperature change flag
extern double Gravity;
extern double Temp;
extern long (*stepptr)(long);	// pointer to stepdomino() function
extern void (*stepdptr)();		// pointer to stepdomm() function
extern long funum;				// function number
extern long nobs;				// number of obstacle nodes
extern long Obs[];				// obstacle addresses
extern long colorctl;			// domino color control flag
// added to modernize...
extern long fluxctl;			// flux measurement flag
extern long netflux;			// total flux
extern long avgflux;			// average over fluxint
extern long fluxint;
extern long dispctl;			// red/blue domino flag
extern struct domstate state1;
extern long nsource,nsink;		// source, sink per step
extern float upprob,dnprob;		// domino block probability
extern long blkctl;				// single block freeze control
extern float faderate;			// color fade rate divisor
extern long sourcectl;			// source line control flag
extern float diffscale;			// display scaling for difference histogram
extern unsigned long totalflux;	// total flux passing through bottom
extern long desired;			// number of desired dominos in upper chamber
extern long mode,oldmode;		// for testing meansq
extern long startctl;			// display starting domino position
extern long npaths;				// total number diffusion paths sampled
extern long dctl;				// display control flag
extern long ppctl;				// plot paths[] flag
extern float sxx,syy;			// display scaling factors
extern float pyscale;			// path plot yscale

