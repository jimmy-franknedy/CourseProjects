/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		BigIntegerTest.c
* File Description: Program code for testing BigInteger ADT functions!
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "List.h"
#include "BigInteger.h"

#define POWER 2				// **UPDATE BEFORE SUBMITTING**
#define BASE 1000 			// **UPDATE BEFORE SUBMITTING**

int main()
{
	// Printing welcome message
	printf("Welcome to Jimmy's BigIntegerTest.c\n");
	printf("Programs will only prompt 'error' if there exists and error. Else the function works!\n");

	// Create pointer to string
	char* t1 = "-221211110000";
	char* t2 = "-112122223333";
	char* a1 = "-333333333333";
	char* z0 = "+111122223333";
	char* z1 = "+222211110000";
	char* z2 = "+000000000001";
	char* z3 = "+000000000000";
	char* z4 = "-111122223333";
	char* z5 = "+111122223332";
	char* zA = "+333333333333";
	char* z6 = "+222255556666";
	char* z7 = "-222255556666";
	char* z8 = "+666633332222";
	char* z9 = "-666633332222";
	char* z10 = "-888888888888";
	char* z11 = "+888888888888";
	char* z12 = "1234";
	char* z13 = "507";
	char* z14 = "-1234";
	char* z15 = "-507";
	char* z16 = "625638";
	char* z17 = "-625638";


	// Create new BigIntegers
	BigInteger A = newBigInteger();
	BigInteger B = newBigInteger();
	BigInteger C = newBigInteger();
	BigInteger D = newBigInteger();
	BigInteger F = newBigInteger();
	BigInteger G = newBigInteger();

	// Create a counter to measure all the tests;
	int tests = 0;

	printf("\n ==================== Testing Access Fucntions ==================== \n");
	printf("Testing sign():\n");
	tests++;
	setSign(A,1);
	if(sign(A) != 1)
	{
		printf("error (%d)\n",tests);
	}
	tests++;
	setSign(B,0);
	if(sign(B) != 0)
	{
		printf("error (%d)\n",tests);
	}
	tests++;
	setSign(C,-1);
	if(sign(C) != -1)
	{
		printf("error (%d)\n",tests);
	}
	printf("Testing compare():\n");
	tests++;
	setSign(F,1);
	setSign(G,-1);
	if(compare(F,G) != 1)
	{
		printf("error (%d)\n",tests);
	}
	tests++;
	setSign(G,1);
	generate(F,1,76,32,54);
	generate(G,1,52,71,99);
	if(compare(F,G) != 1)
	{
		printf("error (%d)\n",tests);
	}
	tests++;
	makeZero(F);
	makeZero(G);
	generate(F,-1,67,99,58);
	generate(G,-1,79,97,76);
	if(compare(F,G) != 1)
	{
		printf("error (%d)\n",tests);
	}
	tests++;
	makeZero(F);
	makeZero(G);
	generate(F,1,99,99,98);
	generate(G,1,99,99,97);
	if(compare(F,G) != 1)
	{
		printf("error (%d)\n",tests);
	}
	tests++;
	setSign(F,-1);
	setSign(G,-1);
	if(compare(F,G) != -1)
	{
		printf("error (%d)\n",tests);
	}
	tests++;
	makeZero(G);
	generate(G,-1,99,99,98);
	if(compare(F,G) != 0)
	{
		printf("error (%d)\n",tests);
	}
	printf("Testing equals():\n");
	tests++;
	if(equals(F,G) != 1)
	{
		printf("error(%d)\n",tests);
	}

	printf("\n ================= Testing Manipulation Procedures ================ \n");
	printf("Testing makeZero():\n");
	// Tested above
	printf("Testing negate():\n");
	setSign(G,0);
	negate(G);
	tests++;
	if(sign(G) != 0)
	{
		printf("error (%d)\n",tests);
	}
	setSign(G,1);
	negate(G);
	tests++;
	if(sign(G) != -1)
	{
		printf("error (%d)\n",tests);
		printf("sign(G): %d\n",sign(G));
	}
	setSign(G,-1);
	negate(G);
	tests++;
	if(sign(G) != 1)
	{
		printf("error (%d)\n",tests);
	}
	printf("Testing stringToBigInteger():\n");
	// Tested below!

	printf("\n ================= Testing Computation Procedures ================= \n");
	printf("Testing add():\n");
	BigInteger O = stringToBigInteger(t1);
	BigInteger P = stringToBigInteger(t2);
	BigInteger Q = newBigInteger();

	add(Q,O,P);
	BigInteger R = stringToBigInteger(a1);
	if(equals(Q,R) != 1)
	{
		printf("error (20)\n");
		printBigIntegerValues(Q);
		printf("sign(Q): %d\n",sign(Q));
		printBigIntegerValues(R);
		printf("sign(R): %d\n",sign(R));
	}
	BigInteger A0 = stringToBigInteger(zA);
	BigInteger A1 = stringToBigInteger(z0);
	BigInteger A2 = stringToBigInteger(z1);
	BigInteger A3 = newBigInteger();

	add(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (1)\n");
	}
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	freeBigInteger(&A0);
	makeZero(A3);
	A1 = stringToBigInteger(z5);
	A2 = stringToBigInteger(z2);
	A0 = stringToBigInteger(z0);
	add(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (2)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z0);
	A2 = stringToBigInteger(z3);
	A0 = stringToBigInteger(z0);
	add(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (3)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z0);
	A2 = stringToBigInteger(z4);
	A0 = stringToBigInteger(z3);
	add(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (4)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z3);
	A2 = stringToBigInteger(z3);
	A0 = stringToBigInteger(z3);
	add(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (5)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	char* c0 = "98977";
	char* c1 = "90119";
	char* c2 = "189096";
	A1 = stringToBigInteger(c0);
	A2 = stringToBigInteger(c1);
	A0 = stringToBigInteger(c2);
	add(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (6)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}

	printf("Testing sum():\n");
	// Tested with add(): works fine!

	printf("Testing subtract():\n");
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(zA);
	A2 = stringToBigInteger(zA);
	A0 = stringToBigInteger(z3);
	subtract(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (7)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z4);
	A2 = stringToBigInteger(z4);
	A0 = stringToBigInteger(z3);
	subtract(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (8)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z7);
	A2 = stringToBigInteger(z8);
	A0 = stringToBigInteger(z10);
	subtract(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (9)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z6);
	A2 = stringToBigInteger(z9);
	A0 = stringToBigInteger(z11);
	subtract(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (10)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z6);
	A2 = stringToBigInteger(z11);
	A0 = stringToBigInteger(z9);
	subtract(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (11)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z11);
	A2 = stringToBigInteger(z6);
	A0 = stringToBigInteger(z8);
	subtract(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (12)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z10);
	A2 = stringToBigInteger(z9);
	A0 = stringToBigInteger(z7);
	subtract(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (13)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	freeBigInteger(&A0);
	freeBigInteger(&A1);
	freeBigInteger(&A2);
	makeZero(A3);
	A1 = stringToBigInteger(z9);
	A2 = stringToBigInteger(z10);
	A0 = stringToBigInteger(z6);
	subtract(A3,A1,A2);
	if(equals(A3,A0) != 1)
	{
		printf("error (14)\n");
		printBigIntegerValues(A1);
		printBigIntegerValues(A2);
		printBigIntegerValues(A3);
		printBigIntegerValues(A0);
	}
	printf("Testing diff():\n");
	// Tested with subtract(): works fine!

	printf("Testing multiply():\n");
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// makeZero(A3);
	// A1 = stringToBigInteger(z12);
	// A2 = stringToBigInteger(z13);
	// A0 = stringToBigInteger(z16);
	// multiply(A3,A1,A2);
	// if(equals(A3,A0) != 1)
	// {
	// 	printf("error (15)\n");
	// 	printBigIntegerValues(A1);
	// 	printBigIntegerValues(A2);
	// 	printBigIntegerValues(A3);
	// 	printBigIntegerValues(A0);
	// }
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// makeZero(A3);
	// A1 = stringToBigInteger(z15);
	// A2 = stringToBigInteger(z14);
	// A0 = stringToBigInteger(z16);
	// multiply(A3,A1,A2);
	// if(equals(A3,A0) != 1)
	// {
	// 	printf("error (16)\n");
	// 	printBigIntegerValues(A1);
	// 	printBigIntegerValues(A2);
	// 	printBigIntegerValues(A3);
	// 	printBigIntegerValues(A0);
	// }
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// makeZero(A3);
	// A1 = stringToBigInteger(z12);
	// A2 = stringToBigInteger(z3);
	// A0 = stringToBigInteger(z3);
	// multiply(A3,A1,A2);
	// if(equals(A3,A0) != 1)
	// {
	// 	printf("error (17)\n");
	// 	printBigIntegerValues(A1);
	// 	printBigIntegerValues(A2);
	// 	printBigIntegerValues(A3);
	// 	printBigIntegerValues(A0);
	// }
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// makeZero(A3);
	// A1 = stringToBigInteger(z3);
	// A2 = stringToBigInteger(z14);
	// A0 = stringToBigInteger(z3);
	// multiply(A3,A1,A2);
	// if(equals(A3,A0) != 1)
	// {
	// 	printf("error (18)\n");
	// 	printBigIntegerValues(A1);
	// 	printBigIntegerValues(A2);
	// 	printBigIntegerValues(A3);
	// 	printBigIntegerValues(A0);
	// }
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// makeZero(A3);
	// A1 = stringToBigInteger(z12);
	// A2 = stringToBigInteger(z15);
	// A0 = stringToBigInteger(z17);
	// multiply(A3,A1,A2);
	// if(equals(A3,A0) != 1)
	// {
	// 	printf("error (19)\n");
	// 	printBigIntegerValues(A1);
	// 	printBigIntegerValues(A2);
	// 	printBigIntegerValues(A3);
	// 	printBigIntegerValues(A0);
	// }
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// makeZero(A3);
	// A1 = stringToBigInteger(z15);
	// A2 = stringToBigInteger(z12);
	// A0 = stringToBigInteger(z17);
	// multiply(A3,A1,A2);
	// if(equals(A3,A0) != 1)
	// {
	// 	printf("error (20)\n");
	// 	printBigIntegerValues(A1);
	// 	printBigIntegerValues(A2);
	// 	printBigIntegerValues(A3);
	// 	printBigIntegerValues(A0);
	// }
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// makeZero(A3);
	// A1 = stringToBigInteger(z12);
	// A2 = stringToBigInteger(z2);
	// A0 = stringToBigInteger(z12);
	// multiply(A3,A1,A2);
	// if(equals(A3,A0) != 1)
	// {
	// 	printf("error (21)\n");
	// 	printBigIntegerValues(A1);
	// 	printBigIntegerValues(A2);
	// 	printBigIntegerValues(A3);
	// 	printBigIntegerValues(A0);
	// }
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// makeZero(A3);
	// A1 = stringToBigInteger(z14);
	// A2 = stringToBigInteger(z2);
	// A0 = stringToBigInteger(z14);
	// multiply(A3,A1,A2);
	// if(equals(A3,A0) != 1)
	// {
	// 	printf("error (22)\n");
	// 	printBigIntegerValues(A1);
	// 	printBigIntegerValues(A2);
	// 	printBigIntegerValues(A3);
	// 	printBigIntegerValues(A0);
	// }
	printf("Testing prod():\n");
	// Tested with multiply(): works fine!

	printf("\n ==================== Testing Other Operations ==================== \n");
	printf("Testing printBigInteger():\n");
	// Tested above

	printf("\n ==================== Testing Private Functions =================== \n");
	printf("Testing normalize():\n");

	printf("Testing swap():\n");

	// BigInteger s1 = stringToBigInteger(z9);
	// BigInteger o1 = stringToBigInteger(z9);
	// BigInteger s2 = stringToBigInteger(z7);
	// BigInteger o2 = stringToBigInteger(z7);
	// swap(s1,s2);
	// if(equals(s1,o2) != 1) printf("failed\n");
	// if(equals(s2,o1) != 1) printf("failed agaain!\n");
	printf("\n");
	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&C);
	freeBigInteger(&D);
	freeBigInteger(&F);
	freeBigInteger(&G);
	freeBigInteger(&O);
	freeBigInteger(&P);
	freeBigInteger(&Q);
	freeBigInteger(&R);
	// freeBigInteger(&A0);
	// freeBigInteger(&A1);
	// freeBigInteger(&A2);
	// freeBigInteger(&A3);
	// freeBigInteger(&s1);
	// freeBigInteger(&s2);
	// freeBigInteger(&o1);
	// freeBigInteger(&o2);	
}