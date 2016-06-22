#include "rstuff.h"
#include "glgraph.h"

#if RES == 0
#define SZ1 1   // for CELLSZ .01
#define SZ2 1
#define YDISP 2
#endif

#if RES == 1
#define SZ1 1   // for CELLSZ .02
#define SZ2 3
#define YDISP 4
#endif

#if RES == 2
#define SZ1 1   // for CELLSZ .04
#define SZ2 7
#define YDISP 8
#endif
#if RES == 3
#define SZ1 2   // for CELLSZ .08
#define SZ2 16
#define YDISP 17
#endif
// assumes cells correctly adjacent...
void drawdomino(long n1,long n2,long c)
{
float x1,y1,x2,y2;
long ix1,iy1,ix2,iy2,i1,j1,i2,j2;
long nn;

if(n1-n2 == 1)	// for correct graphics outline...
	{
	nn = n1;
	n1 = n2;
	n2 = nn;
	}
if(n1-n2 == -ROWL)
	{
	nn = n1;
	n1 = n2;
	n2 = nn;
	}
i1 = n1%ROWL;
j1 = n1/ROWL;
x1 = i1 * CELLSZ - 1.5;
y1 = j1 * CELLSZ - 1.0;
x1 -= gl_oleft;
x1 *= gl_oxfact;
ix1 = x1;
y1 -= gl_otop;
y1 *= gl_oyfact;
iy1 = y1 - YDISP;
i2 = n2%ROWL;
j2 = n2/ROWL;
x2 = i2 * CELLSZ - 1.5;
y2 = j2 * CELLSZ - 1.0;
x2 -= gl_oleft;
x2 *= gl_oxfact;
ix2 = x2;
y2 -= gl_otop;
y2 *= gl_oyfact;
iy2 = y2 - YDISP;
//if(c == 0)
//	color(RED);
//else
//	color(BLUE);
color(c);
//gl_rect(ix1+SZ1,iy1+SZ1,ix1+SZ2,iy1+SZ2);
//gl_rect(ix2+SZ1,iy2+SZ1,ix2+SZ2,iy2+SZ2);
brectf(ix1+SZ1,iy1+SZ1,ix2+SZ2,iy2+SZ2);
color(BLACK);
brect(ix1+SZ1,iy1+SZ1,ix2+SZ2,iy2+SZ2);
}

void drawdominocb(long n1,long n2,long c)
{
float x1,y1,x2,y2;
long ix1,iy1,ix2,iy2,i1,j1,i2,j2;
long nn;
#if 1
if(n1-n2 == 1)	// for correct graphics outline...
	{
	nn = n1;
	n1 = n2;
	n2 = nn;
	}
#endif
#if 1
if(n1-n2 == -ROWL)
	{
	nn = n1;
	n1 = n2;
	n2 = nn;
	}
#endif
// domino wrap-around...
// just skip for time bean...
// ok, now filling in with single squares.
if(n1-n2 == (ROWL-1)) goto cb;
if(n2-n1 == (ROWL-1)) goto cb;
if(n1-n2 == (NROWS-1)*ROWL) goto cb;
if(n2-n1 == (NROWS-1)*ROWL) goto cb;
i1 = n1%ROWL;
j1 = n1/ROWL;
x1 = i1 * CELLSZ - 1.5;
y1 = j1 * CELLSZ - 1.0;
x1 -= gl_oleft;
x1 *= gl_oxfact;
ix1 = x1;
y1 -= gl_otop;
y1 *= gl_oyfact;
iy1 = y1 - YDISP;
i2 = n2%ROWL;
j2 = n2/ROWL;
x2 = i2 * CELLSZ - 1.5;
y2 = j2 * CELLSZ - 1.0;
x2 -= gl_oleft;
x2 *= gl_oxfact;
ix2 = x2;
y2 -= gl_otop;
y2 *= gl_oyfact;
iy2 = y2 - YDISP;
//if(c == 0)
//	color(RED);
//else
//	color(BLUE);
color(c);
//gl_rect(ix1+SZ1,iy1+SZ1,ix1+SZ2,iy1+SZ2);
//gl_rect(ix2+SZ1,iy2+SZ1,ix2+SZ2,iy2+SZ2);
brectf(ix1+SZ1,iy1+SZ1,ix2+SZ2,iy2+SZ2);
color(BLACK);
brect(ix1+SZ1,iy1+SZ1,ix2+SZ2,iy2+SZ2);
return;
cb:
drawnode(n1,c);
drawnode(n2,c);
//nn = 3;		// dummy statement
//continue;
}

// clips dominos outside of (0,DOMX,0,DOMY) rectangle
void drawdominopart(long n1,long n2,long c)
{
float x1,y1,x2,y2;
long ix1,iy1,ix2,iy2,i1,j1,i2,j2;
long nn;
#if 1
if(n1-n2 == 1)	// for correct graphics outline...
	{
	nn = n1;
	n1 = n2;
	n2 = nn;
	}
#endif
#if 1
if(n1-n2 == -ROWL)
	{
	nn = n1;
	n1 = n2;
	n2 = nn;
	}
#endif
// domino wrap-around...
// just skip for time bean...
// ok, now filling in with single squares.
if(n1-n2 == (ROWL-1)) goto cb;
if(n2-n1 == (ROWL-1)) goto cb;
if(n1-n2 == (NROWS-1)*ROWL) goto cb;
if(n2-n1 == (NROWS-1)*ROWL) goto cb;
i1 = n1%ROWL;
if(i1 >= DOMX) return;
j1 = n1/ROWL;
if(j1 >= DOMY) return;
x1 = i1 * CELLSZ - 1.5;
y1 = j1 * CELLSZ - 1.0;
x1 -= gl_oleft;
x1 *= gl_oxfact;
ix1 = x1;
y1 -= gl_otop;
y1 *= gl_oyfact;
iy1 = y1 - YDISP;
i2 = n2%ROWL;
j2 = n2/ROWL;
x2 = i2 * CELLSZ - 1.5;
y2 = j2 * CELLSZ - 1.0;
x2 -= gl_oleft;
x2 *= gl_oxfact;
ix2 = x2;
y2 -= gl_otop;
y2 *= gl_oyfact;
iy2 = y2 - YDISP;
//if(c == 0)
//	color(RED);
//else
//	color(BLUE);
color(c);
//gl_rect(ix1+SZ1,iy1+SZ1,ix1+SZ2,iy1+SZ2);
//gl_rect(ix2+SZ1,iy2+SZ1,ix2+SZ2,iy2+SZ2);
brectf(ix1+SZ1,iy1+SZ1,ix2+SZ2,iy2+SZ2);
color(BLACK);
brect(ix1+SZ1,iy1+SZ1,ix2+SZ2,iy2+SZ2);
return;
cb:
i1 = n1%ROWL;
if(i1 >= DOMX) return;
j1 = n1/ROWL;
if(j1 >= DOMY) return;
drawnode(n1,c);
drawnode(n2,c);
}

// draws a single domino node
void drawnode(long n,long c)
{
float x1,y1,x2,y2;
long ix1,iy1,ix2,iy2,i1,j1,i2,j2;
//long nn;
long n1,n2;

n1 = n2 = n;
i1 = n1%ROWL;
j1 = n1/ROWL;
x1 = i1 * CELLSZ - 1.5;
y1 = j1 * CELLSZ - 1.0;
x1 -= gl_oleft;
x1 *= gl_oxfact;
ix1 = x1;
y1 -= gl_otop;
y1 *= gl_oyfact;
iy1 = y1 - YDISP;
i2 = n2%ROWL;
j2 = n2/ROWL;
x2 = i2 * CELLSZ - 1.5;
y2 = j2 * CELLSZ - 1.0;
x2 -= gl_oleft;
x2 *= gl_oxfact;
ix2 = x2;
y2 -= gl_otop;
y2 *= gl_oyfact;
iy2 = y2 - YDISP;

color(c);

//gl_rect(ix1+SZ1,iy1+SZ1,ix1+SZ2,iy1+SZ2);
//gl_rect(ix2+SZ1,iy2+SZ1,ix2+SZ2,iy2+SZ2);
brectf(ix1+SZ1,iy1+SZ1,ix2+SZ2,iy2+SZ2);
color(BLACK);
brect(ix1+SZ1,iy1+SZ1,ix2+SZ2,iy2+SZ2);
}

void border()
{
color(BLACK);
move(1.5,1.0);
pendn();
move(1.5,-1.0);
move(-1.5,-1.0);
move(-1.5,1.0);
move(1.5,1.0);
penup();
}

// display active dominos, labels...
void display()
{
long i,n1,n2,c,vdisp=(DOMY-NROWS);

color(WHITE);
clear();
if(!dispctl)
	{
for(i=0;i<ndominos;i++)
	{
	n1 = dominos[i].atnode1;
	n2 = dominos[i].atnode2;
	#if CLOCK
	c = clocktocolor(dominos[i].clock);
	#else
	c = dominos[i].color;
	//c = RED;
	#endif
	
	if(vdisp != 0)
		{
		n1 += vdisp*ROWL;
		n2 += vdisp*ROWL;
		if(n1 >= ROWL)
			drawdominocb(n1,n2,c);
		}
	else
		drawdominocb(n1,n2,c);
	
	}
	}
else	// red/blue horizontal/vertical display
	{
	//sleep(1);
	for(i=0;i<ndominos;i++)
		{
		n1 = dominos[i].atnode1;
		n2 = dominos[i].atnode2;
		if((n1 == n2+1) || (n1 == n2-1) ||
		   (n1 == (n2-ROWL+1)) || (n1 == (n2+ROWL-1)))
			c = RED;
		else
			c = BLUE;
		drawdominocb(n1,n2,c);
		}
	}
border();
//drawbndys();	// what did this do?
#if OBS
for(i=0;i<nobs;i++)
	drawnode(Obs[i],BLACK);
#endif
#if FPTR
if(funum == 0)
	label("very soft",520,475);
if(funum == 1)
	label("soft",530,475);
if(funum == 2)
	label("nhp",532,475);
#endif
drawnum(ndominos,100,35);
drawnum(nsteps,520,35);
////drawnum(totalflux,300,35);	// defined in domhist.c
//drawnum(dominos[0].atnode1,250,35);
//drawnum(dominos[0].atnode2,350,35);
//label("P = ",520,480);
//drawnum(Pav,-1,-1);
if(fluxctl)
	{
	Printf("\nflux %d",netflux);
	labit(50,480);
	}
Printf("\nT = %.3lf",Temp);
labit(280,480);
//if(!histctl) drawbuffer();
}

// display active dominos, labels...
// display limited to available window space...
void displaypart()
{
long i,n1,n2,c;

color(WHITE);
clear();
for(i=0;i<ndominos;i++)
	{
	n1 = dominos[i].atnode1;
	n2 = dominos[i].atnode2;
	c = dominos[i].color;
	drawdominopart(n1,n2,c);
	}
border();
//drawbndys();
#if OBS
for(i=0;i<nobs;i++)
	drawnode(Obs[i],BLACK);
#endif
#if FPTR
if(funum == 0)
	label("very soft",520,475);
if(funum == 1)
	label("soft",530,475);
if(funum == 2)
	label("nhp",532,475);
#endif
drawnum(ndominos,100,35);
drawnum(nsteps,520,35);
//drawnum(dominos[0].atnode1,250,35);
//drawnum(dominos[0].atnode2,350,35);
//label("P = ",520,480);
//drawnum(Pav,-1,-1);
Printf("\nT = %.2lf",Temp);
labit(280,480);
if(fluxctl)
	{
	Printf("\nflux %d",netflux);
	labit(280,480);
	}
//if(!histctl) drawbuffer();
}

// display active dominos, labels...
// dominos are black, except for first,
// position of first handed in as argument
void displaytt(long at1,long at2)
{
long i,n1,n2;

color(WHITE);
clear();
for(i=1;i<ndominos;i++)
	{
	n1 = dominos[i].atnode1;
	n2 = dominos[i].atnode2;
	//drawdomino(n1,n2,c);
	drawdominocb(n1,n2,BLACK);
	}
drawnode(at1,RED);
drawnode(at2,BLUE);
border();
//drawbndys();
drawnum(ndominos,100,35);
drawnum(nsteps,520,35);
drawnum(dominos[0].atnode1,220,35);
drawnum(dominos[0].atnode2,350,35);

//drawbuffer();
}
#if 0
void displaypotpl()
{
  int i;
  color(WHITE);
  clear();
  for(i=0;i<NMAX;i++)
    if(potpl[i]>0) drawnode(i,RED);
  drawbuffer();
}
#endif

// prints iteration rate, ll is number of ticks...
void printhz(long nstps,long ll)
{
float hz;

hz = 60.0 * (float)nstps / (float)ll;
drawnum(hz,520,35);
label(" Hz     ",-1,-1);
//drawbuffer();
}

long Cmap[1024];
void ldCmap()
{
float r,g,b;
long i,c;

for(i=0;i<1024;i++)
	{
	r = (float)i/1023;
	g = (float)i/1023;
	b = (float)i/1023;
//	g=b=0;
	//r = 1.0;g=b=0;
	r = 1-r;
	b = 1-b;
	g = 1-g;
	c = RGBcolor(r,g,b);
	Cmap[i] = c;
	//printf("c %d\n",c);
	}
}

//translates clock value to color value
long clocktocolor(long clk)
{
long c;

//clk = clk/4;
clk = clk*faderate;
if(clk < 1024)
	c = Cmap[clk];
else
	c = Cmap[1023];
//printf("%d\n",clk);
return c;
}
