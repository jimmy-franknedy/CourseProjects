//-----------------------------------------------------------------------------
// DictionaryTest.c
// Test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

int main()
{
   // Testing Values 1
   char key1[] = "Key";
   char* k1 = key1; 
   char val1[] = "grape";
   char* v1 = val1;

   // Testing Values 2
   char key2[] = "Str0n5 KE3Y!";
   char* k2 = key2; 
   char val2[] = "apple";
   char* v2 = val2;

   // Testing Values 3
   char key3[] = "A really really really long key";
   char* k3 = key3; 
   char val3[] = "banana";
   char* v3 = val3;

   // Testing Values 4
   char key4[] = "@ rE@11y 5T6oO_nG k3yg";
   char* k4 = key4; 
   char val4[] = "orange";
   char* v4 = val4;

   // Additional keys
   char key5[] = "one";
   char* k5 = key5; 

   char key6[] = "two";
   char* k6 = key6;

   char key7[] = "three";
   char* k7 = key7;

   char key8[] = "four";
   char* k8 = key8;

   printf("\nTesting newDictionary!\n");
   printf("Errors will prompt the program to print out details!");
   Dictionary d1 = newDictionary();
   Dictionary d2 = newDictionary();
   Dictionary d3 = newDictionary();
   Dictionary d4 = newDictionary();
   Dictionary d5 = newDictionary();
   Dictionary d6 = newDictionary();

   printf("\nTesting size!\n");
   printf("size(d1): %d\n", size(d1));
   printf("size(d2): %d\n", size(d2));
   printf("size(d3): %d\n", size(d3));
   printf("size(d4): %d\n", size(d4));
   printf("size(d5): %d\n", size(d3));
   printf("size(d6): %d\n", size(d4));

   printf("\nTesting insert!\n");
   insert(d1,k1,v1);
   insert(d2,k2,v2);
   insert(d3,k3,v3);
   insert(d4,k4,v4);
   insert(d5,k1,v1);
   insert(d5,k2,v2);
   insert(d5,k3,v3);
   insert(d5,k4,v4);

   printf("\nTesting size() after insert!\n");
   printf("size(d1): %d == 1\n", size(d1));
   printf("size(d2): %d == 1\n", size(d2));
   printf("size(d3): %d == 1\n", size(d3));
   printf("size(d4): %d == 1\n", size(d4));
   printf("size(d5): %d == 4\n", size(d5));

   printf("\nTesting lookup!\n");
   printf("lookup(d1,k1): %s\n",lookup(d1,k1));
   printf("lookup(d2,k2): %s\n",lookup(d2,k2));
   printf("lookup(d3,k3): %s\n",lookup(d3,k3));
   printf("lookup(d4,k4): %s\n",lookup(d4,k4));
   printf("lookup(d5,k4): %s\n",lookup(d5,k4));

   printf("\nTesting lookup with invalid keys!\n");
   if(lookup(d1,k2) != NULL &&
      lookup(d2,k3) != NULL &&
      lookup(d3,k4) != NULL)
   {
      printf("Error with lookup: Testing invalid keys!\n");
   }

   printf("\nTesting insert more!\n");
   insert(d1,k2,v2);
   insert(d1,k3,v3);
   insert(d2,k3,v3);
   insert(d2,k4,v4);
   insert(d3,k4,v4);
   insert(d3,k1,v1);
   insert(d4,k1,v1);
   insert(d4,k2,v2);

   printf("\nChecking size() again after insert!\n");
   printf("size(d1): %d == 3\n", size(d1));
   printf("size(d2): %d == 3\n", size(d2));
   printf("size(d3): %d == 3\n", size(d3));
   printf("size(d4): %d == 3\n", size(d4));
   printf("size(d5): %d == 4\n", size(d5));

   printf("\nTesting delete!\n");

   printf("Checking (d5) before delete():\n");
   printf("lookup(d5,k1): %s\n",lookup(d5,k1));
   printf("lookup(d5,k2): %s\n",lookup(d5,k2));
   printf("lookup(d5,k3): %s\n",lookup(d5,k3));
   printf("lookup(d5,k4): %s\n",lookup(d5,k4));
   printf("size(d5): %d == 4\n", size(d5));

   printf("\nDeleting 2 nodes in D with 4 Nodes!\n");
   printf("Before delete() | Size(d5): %d\n",size(d5));
   delete(d5,k1);
   delete(d5,k4);
   printf("After delete()  | Size(d5): %d\n",size(d5));
   printf("lookup(d5,k1): %s\n",lookup(d5,k1));
   printf("lookup(d5,k2): %s\n",lookup(d5,k2));
   printf("lookup(d5,k3): %s\n",lookup(d5,k3));
   printf("lookup(d5,k4): %s\n",lookup(d5,k4));

   printf("\nDeleting the head (i.e k1) in D with 2 Nodes!\n");
   printf("Before delete() | Size(d5): %d\n",size(d5));
   delete(d5,k2);
   printf("After delete()  | Size(d5): %d\n",size(d5));
   printf("lookup(d5,k1): %s\n",lookup(d5,k1));
   printf("lookup(d5,k2): %s\n",lookup(d5,k2));
   printf("lookup(d5,k3): %s\n",lookup(d5,k3));
   printf("lookup(d5,k4): %s\n",lookup(d5,k4));

   insert(d5,k2,v2);
   printf("\nlookup(d5,k1): %s\n",lookup(d5,k1));
   printf("lookup(d5,k2): %s\n",lookup(d5,k2));
   printf("lookup(d5,k3): %s\n",lookup(d5,k3));
   printf("lookup(d5,k4): %s\n",lookup(d5,k4));

   printf("\nDeleting the tail (i.e k2) in D with 2 Nodes!\n");
   printf("Before delete() | Size(d5): %d\n",size(d5));
   delete(d5,k3);
   printf("After delete()  | Size(d5): %d\n",size(d5));
   printf("lookup(d5,k1): %s\n",lookup(d5,k1));
   printf("lookup(d5,k2): %s\n",lookup(d5,k2));
   printf("lookup(d5,k3): %s\n",lookup(d5,k3));
   printf("lookup(d5,k4): %s\n",lookup(d5,k4));

   printf("\nDeleting the head (i.e ONLY HEAD) in D with 1 Node!\n");
   printf("Before delete() | Size(d5): %d\n",size(d5));
   delete(d5,k2);
   printf("After delete()  | Size(d5): %d\n",size(d5));
   printf("lookup(d5,k1): %s\n",lookup(d5,k1));
   printf("lookup(d5,k2): %s\n",lookup(d5,k2));
   printf("lookup(d5,k3): %s\n",lookup(d5,k3));
   printf("lookup(d5,k4): %s\n",lookup(d5,k4));

   printf("\nTesting makeEmpty!\n");

   makeEmpty(d4);
   printf("\nd4 after makeEmpty()\n");
   printf("lookup(d4,k4): %s\n",lookup(d4,k4));
   printf("lookup(d4,k1): %s\n",lookup(d4,k1));
   printf("lookup(d4,k2): %s\n",lookup(d4,k2));


   makeEmpty(d3);
   printf("\nd3 after makeEmpty()\n");
   printf("lookup(d3,k3): %s\n",lookup(d3,k3));
   printf("lookup(d3,k4): %s\n",lookup(d3,k4));
   printf("lookup(d3,k1): %s\n",lookup(d3,k1));


   makeEmpty(d2);
   printf("\nd2 after makeEmpty()\n");
   printf("lookup(d2,k2): %s\n",lookup(d2,k2));
   printf("lookup(d2,k3): %s\n",lookup(d2,k3));
   printf("lookup(d2,k4): %s\n",lookup(d2,k4));

   makeEmpty(d1);
   printf("\nd1 after makeEmpty()\n");
   printf("lookup(d1,k1): %s\n",lookup(d1,k1));
   printf("lookup(d1,k2): %s\n",lookup(d1,k2));
   printf("lookup(d1,k3): %s\n",lookup(d1,k3));

   printf("\nTesting DictionaryToString()\n");
   insert(d6,k5,v1);
   insert(d6,k6,v2);
   insert(d6,k7,v3);
   insert(d6,k8,v4);
   char* blank = DictionaryToString(d6);
   printf("\n%s",blank);

   printf("\nTesting Complete...Freeing!\n");
   printf("freeDictionary(&d1)\n");
   freeDictionary(&d1);
   printf("freeDictionary(&d2)\n");
   freeDictionary(&d2);
   printf("freeDictionary(&d3)\n");
   freeDictionary(&d3);
   printf("freeDictionary(&d4)\n");
   freeDictionary(&d4);
   printf("freeDictionary(&d5)\n");
   freeDictionary(&d5);
   printf("freeDictionary(&d6)\n");
   freeDictionary(&d6);
   free(blank);
}