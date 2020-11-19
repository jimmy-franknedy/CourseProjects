#------------------------------------------------------------------------------
# Makefile for any client of any ADT in C
#------------------------------------------------------------------------------

CLIENT         = DictionaryTest
ADT            = Dictionary
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT_SOURCE     = $(ADT).c
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes
FILES          = README Dictionary.c Dictionary.h DictionaryTest.c Makefile
SUBMIT         = submit cse015-pt.f19 pa5

$(CLIENT) : $(OBJECT) $(ADT_OBJECT) 
	$(LINK) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT_HEADER) 
	$(COMPILE) $(SOURCE)

$(ADT_OBJECT) : $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)

check : 
	ls /afs/cats.ucsc.edu/class/cse015-pt.f19/pa4/jfrankne

r : 
	make clean
	make
	clear
	$(CLIENT)

submit : $(FILES)
	$(SUBMIT) $(FILES)