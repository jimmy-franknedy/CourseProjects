#/*********************************************************************************
#* Name: 			Jimmy Franknedy
#* CruzID:			jfrankne
#* Course: 			CSE 101 Spring 2020
#* File name: 		Makefile
#* File Description Makefile for building Lex
#*********************************************************************************/
CLIENT          = Lex
ADT1            = Dictionary
SOURCE          = $(CLIENT).c
OBJECT          = $(CLIENT).o
ADT1_SOURCE     = $(ADT1).c
ADT1_OBJECT     = $(ADT1).o
ADT1_HEADER     = $(ADT1).h
COMPILE         = gcc -c -std=c99 -Wall
LINK            = gcc -o
REMOVE          = rm -f
MEMCHECK        = valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) 
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1) $(ADT1_OBJECT) 

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