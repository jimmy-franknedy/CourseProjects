/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		DictionaryTest.c
* File Description: Program for testing the Dictionary ADT functions
*********************************************************************************/
int main()
{
	Dictionary A = newDictionary(0);
	Dictionary B = newDictionary(1);
	Dictionary C = newDictionary(1);
	Dictionary D = newDictionary(1);

	char* key1 = "a";
	int   val1 = 1;

	char* key2 = "b";
	int   val2 = 2;

	char* key3 = "c";
	int   val3 = 3;

	printf("Welcome to Jimmy's BigIntegerTest.c\n");
	printf("Programs will only prompt 'error' if there exists and error. Else the function works!\n");
	printf("\n ==================== Testing Access Fucntions ==================== \n");
	printf("Testing size():\n");
	if(size(A) != 0)
	{
		printf("error (1)\n");
	}
	printf("Testing getUnique():\n");
	if(getUnique(A) != 0)
	{
		printf("error (2)\n");
	}
	printf("Testing lookup():\n");

	printf("\n ================= Testing Manipulation Procedures ================ \n");
	printf("Testing insert():\n");
	// Tested above

	printf("Testing delete():\n");
	// ==============
	insert(D,key2,val2);
	insert(D,key3,val3);
	insert(D,key1,val1);
	delete(D,key3);
	delete(D,key1);
	delete(D,key2);
	// ==============
	makeEmpty(D);
	insert(D,key2,val2);
	insert(D,key3,val3);
	delete(D,key2);
	delete(D,key3);
	// ==============
	makeEmpty(D);
	insert(D,key2,val2);
	insert(D,key1,val1);
	delete(D,key2);
	delete(D,key1);
	// ==============
	makeEmpty(D);
	insert(D,key2,val2);
	insert(D,key3,val3);
	insert(D,key1,val1);
	delete(D,key2);
	delete(D,key3);
	delete(D,key1);
	// ==============
	insert(D,key2,val2);
	delete(D,key2);
	// ==============
	insert(D,key2,val2);
	insert(D,key1,val1);
	delete(D,key2);
	delete(D,key1);

	printf("Testing makeEmpty():\n");
	insert(C,"1",1);
	insert(C,"0",0);
	insert(C,"5",5);
	insert(C,"4",4);
	insert(C,"16",16);
	insert(C,"2",2);
	insert(C,"176",176);
	insert(C,"150",150);
	insert(C,"3214",3214);

	printf("Testing beginForward():\n");
    insert(B, "d", 1);
    insert(B, "b", 5);
    insert(B, "c", 16);
    insert(B, "f", 176);
    insert(B, "e", 3214);
    if(beginForward(B) != 5) printf("beginForward(B): %d\n",beginForward(B));
    if(currentVal(B) != 5) printf("currentVal(B): %d\n",currentVal(B));

	printf("Testing beginReverse():\n");
	printf("Testing currentKey():\n");
	printf("Testing currentVal():\n");
	printf("Testing next():\n");
    insert(A, "a", 1);
    insert(A, "b", 5);
    insert(A, "c", 16);
    insert(A, "d", 176);
    insert(A, "e", 3214);
    beginForward(A);
    next(A);
    next(A);
    if(strcmp(currentKey(A), "c") != 0)
    {
    	printf("currentKey(A): %s\n",currentKey(A));
    	printf("Expected Key : c\n");
    }
    if(currentVal(A) != 16)
    {
    	printf("currentVal(A): %d\n",currentVal(A));
    	printf("Expected Val : 16\n");
    }
	printf("Testing prev():\n");
	makeEmpty(A);
    insert(A, "a", 1);
    insert(A, "b", 5);
    insert(A, "e", 3214);
    beginReverse(A);
    prev(A);
    if (strcmp(currentKey(A), "b") != 0)
    {
    	printf("currentKey(A): %s\n",currentKey(A));
    	printf("Expected Key : b\n");
    }
    if (currentVal(A) != 5)
    {
    	printf("currentVal(A): %d\n",currentVal(A));
    	printf("Expected Val : 5\n");
    }
    prev(A);
    prev(A);
    if (currentKey(A) != KEY_UNDEF)
    {
    	printf("currentKey(A): %s\n",currentKey(A));
    	printf("Expected Key : KEY_UNDEF\n");
    }
    if (currentVal(A) != VAL_UNDEF)
    {
    	printf("currentVal(A): %d\n",currentVal(A));
    	printf("Expected Val : VAL_UNDEF\n");
    }
	printf("\n ==================== Testing Other Operations ==================== \n");
	printf("Testing printDictionary():\n\n");

	freeDictionary(&A);
	freeDictionary(&B);
	freeDictionary(&C);
	freeDictionary(&D);
}