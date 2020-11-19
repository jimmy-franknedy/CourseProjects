#---------------------------------------------------
# Makefile for Queens.c with macros
#---------------------------------------------------
ASSIGNMENT = pa2
EXEBIN = Queens
SOURCES = $(EXEBIN).c
OBJECTS = $(EXEBIN).o
FLAGS = -std=c99 -Wall
FILES = $(SOURCES) Makefile README 
SUBMIT = submit cse015-pt.f19 $(ASSIGNMENT)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

submit : $(FILES)
	$(SUBMIT) $(FILES)

memcheck : $(EXEBIN)
	valgrind --leak-check=full $(EXEBIN) -v 8
	
run : 
	make clean
	make
	$(EXEBIN)

check: 
	ls /afs/cats.ucsc.edu/class/cse015-pt.f19/pa2/jfrankne
