#------------------------------------------------------------------------------
# Makefile for any client of any two ADTs in C
#------------------------------------------------------------------------------
ASSIGNMENT	    = pa4
TESTER			= ex4
CLIENT          = Simulation
ADT1            = IntegerQueue
ADT2            = Job
SOURCE          = $(CLIENT).c
OBJECT          = $(CLIENT).o
ADT1_SOURCE     = $(ADT1).c
ADT1_OBJECT     = $(ADT1).o
ADT1_HEADER     = $(ADT1).h
ADT2_SOURCE     = $(ADT2).c
ADT2_OBJECT     = $(ADT2).o
ADT2_HEADER     = $(ADT2).h
COMPILE         = gcc -c -std=c99 -Wall
LINK            = gcc -o
REMOVE          = rm -f
MEMCHECK        = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
FILES           = README Makefile $(SOURCE2) $(ADT_HEADER) $(ADT_SOURCE) $(SOURCE) Job.h Job.c
SUBMIT          = submit cse015-pt.f19 $(ASSIGNMENT)

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) 

memcheck : $(CLIENT)
	clear
	$(MEMCHECK) $(CLIENT) $(TESTER)

check : 
	ls /afs/cats.ucsc.edu/class/cse015-pt.f19/pa4/jfrankne

r : 
	make clean
	make
	clear
	$(CLIENT) $(TESTER)

submit : $(FILES)
	$(SUBMIT) $(FILES)
