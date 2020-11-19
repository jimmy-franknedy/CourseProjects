#/*********************************************************************************
#* Name: 			Jimmy Franknedy
#* CruzID:			jfrankne
#* Course: 			CSE 101 Spring 2020
#* File name: 		Makefile
#* File Description Makefile for building Arithmetic.c with 2 ADT
#*********************************************************************************/
CLIENT          = Arithmetic
ADT1            = List
ADT2            = BigInteger
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
MEMCHECK        = valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(ADT1) $(ADT2) $(ADT1_OBJECT) $(ADT2_OBJECT) $(OBJECT) 

memcheck :
	clear
	$(MEMCHECK) $(CLIENT) in out
	

check : 
	ls /afs/cats.ucsc.edu/class/cse015-pt.f19/pa4/jfrankne

r : 
	make clean
	make
	clear
	$(CLIENT) in out