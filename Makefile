# makefile
# fill TG in with program you want to compile
# for gdb use  % make DBG=-g

TG = domgrav
#TG = antlers

DBG = -O3
CFLAGS = $(DBG) -Wmost -Wno-deprecated-declarations -arch i386
LIBS = -framework OpenGL -framework GLUT -framework Carbon -arch i386
OBJ = glgraph.o vWindow.o $(TG).o displays.o inits.o shuffle.o boltz.o stepdomino.grav.o\
stepdommboltz.o		# for new improved boltzmann rule
#stepdomm.o		# for original boltzmann rule

$(TG):	$(OBJ)
	cc -o $(TG) $(OBJ) $(LIBS)

HEADERS = $(TG).h glgraph.h
$(OBJ): $(HEADERS)

clean:
	rm *.o $(TG)

tar:
	tar czvf $(TG).tgz *
