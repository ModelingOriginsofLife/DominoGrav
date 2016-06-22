//  domino gas!  ...ok, dominos in brownian motion.
//  started december 7, 2004
#include <GLUT/glut.h>
#include "rstuff.h"
#include "glgraph.h"
unsigned long int _seed = 1;

unsigned long Vout[SIZEX * SIZEY];			// output display image

// node structure.
//struct node{
//	long occ;
//	long Nbrs[NNBRS];	// list of neighbors
//};
struct node nodes[NMAX];

// object structure
//struct domino{
//	long exists;	// 1 means it actually exists
//	long atnode1;	// where it is in configuration space...
//	long atnode2;
//};
struct domino dominos[NDOMS];

// boundary structure
//struct bndy{
//	long n1;		// first node number
//	long n2;		// second node number
//};
struct bndy bndys[NMAX];

unsigned long Histo[NENTS],Histo1[NENTS];

long ndominos = 1000;
long nsteps = 0;
long slowctl = 100;
long pausectl = 0;
long myseedy = 0;			// random number seed
double Gravity = 1.0;
double Temp = 1.0;
long (*stepptr)(long);		// pointer to stepdomino() function
void (*stepdptr)();			// pointer to stepdomm() function
long funum = 2;				// function number
long nobs = 0;				// number of obstacle nodes
long Obs[NMAX];				// obstacle addresses
long fluxctl = 0;			// flux measurement flag
long netflux = 0;			// total flux
long dispctl = 0;			// red/blue domino flag
float faderate = .25;		// color fade rate divisor
long desired;				// number of desired dominos in upper chamber

void Display()
{

long i;
if(pausectl) return;
for(i=0;i<slowctl;i++)
	{
	stepdptr();
	++nsteps;
	}

display();

glutSwapBuffers();
glutPostRedisplay();
++gl_framecount;
}

int main (int argc, const char * argv[])
{
float xx,yy;

printf("ROWL %ld  NROWS %ld NDOMS %ld\n",ROWL,NROWS,NDOMS);
initgravboltz(Temp,Gravity);
initgboltz(Temp,Gravity);

stepptr = stepdomino2;		// initial domino rule (nhp, stepdomino)
stepdptr = stepdomm2;		// initial domino rule (nhp, stepdomm)

glutInit(&argc, (char**) argv);
prefsize(SIZEX,SIZEY);
initgraph("domino gas!");
yy = 1.2; xx = yy * XFAC;
scale(-xx,xx,-yy,yy);

nsteps = 0;
++myseedy;
//initnodes();
initnodescb();
initdomino4a(ndominos);

//initmem1(MTHICK,MSPACE,CHAMB1);
initmem1(1,2,NROWS/4);					// for membrane
//initobstacle();					// for antlers

glutMainLoop();

return 1;
}
