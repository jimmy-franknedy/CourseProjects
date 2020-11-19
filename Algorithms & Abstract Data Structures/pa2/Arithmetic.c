/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		Arithmetic.c
* File Description: High-level program utilizing the List and BigInteger ADT
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"
#include "BigInteger.h"
#define TEN 10

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Inproper Usage: Invalid Arithmetic input\n");
        exit(EXIT_FAILURE); 
    }
    // File Access 
    FILE* in;   // input file to read from
    FILE* out;  // output file to write to

    // Check to see if input file can be read
    in = fopen(argv[1], "r");
    if(in == NULL)
    {
    	fprintf(stderr, "Inproper Usage: Invalid input file\n");
        exit(EXIT_FAILURE);    
    }

    // Check to see if putput file can be written into
    out = fopen(argv[2], "wr+");
    if(out == NULL)
    {
        fprintf(stderr, "Inproper Usage: Invalid output file\n");
        exit(EXIT_FAILURE);          
    }
    char countE1[9];
    fscanf(in,"%s",countE1);
    int convert = atoi(countE1);
    char e1[convert];
    fscanf(in,"%s",e1);
    BigInteger A = stringToBigInteger(e1);
    char countE2[9];
    fscanf(in,"%s",countE2);
    convert = atoi(countE2);
    char e2[convert];
    fscanf(in,"%s",e2);
    BigInteger B = stringToBigInteger(e2);

    // A
    printBigInteger(out,A);
    printf("\n\n");

    // B
    printBigInteger(out,B);
    printf("\n\n");

    // A + B
    BigInteger C = sum(A,B);
    printBigInteger(out,C);
    freeBigInteger(&C);
	printf("\n\n");

    // A - B
    C = diff(A,B);
 	printBigInteger(out,C);
 	freeBigInteger(&C);
	printf("\n\n");

    // A - A
	BigInteger copyA = copy(A);
	C = diff(A,copyA);
	printBigInteger(out,C);
	freeBigInteger(&C);
	freeBigInteger(&copyA);


    // 3A - 2B
	printf("\n\n");
	char* aa = "3";
	char* bb = "2";
	BigInteger Aa = stringToBigInteger(aa);
	BigInteger Bb = stringToBigInteger(bb);
	BigInteger biggerA = prod(A,Aa);
	BigInteger biggerB = prod(B,Bb);
	C = diff(biggerA,biggerB);
	printBigInteger(out,C);
	freeBigInteger(&Aa);
	freeBigInteger(&Bb);
	freeBigInteger(&biggerA);
	freeBigInteger(&biggerB);
	freeBigInteger(&C);

    // A * B
	printf("\n\n");
	C = prod(A,B);
	printBigInteger(out,C);
	freeBigInteger(&C);

    // A * A
	printf("\n\n");
	copyA = stringToBigInteger(e1);
	C = prod(A,copyA);
	printBigInteger(out,C);
	freeBigInteger(&C);	
	freeBigInteger(&copyA);

    // B * B
	printf("\n\n");
	BigInteger copyB = stringToBigInteger(e2);
	C = prod(B,copyB);
	printBigInteger(out,C);
	freeBigInteger(&C);
	freeBigInteger(&copyB);

    // 9A^4 + 16B^5
	printf("\n\n");
	BigInteger copyA_1 = stringToBigInteger(e1);
	BigInteger copyA_2 = stringToBigInteger(e1);
	BigInteger copyA_1_2 = prod(copyA_1,copyA_2);
	BigInteger copyA_3_4 = copy(copyA_1_2);
	BigInteger copyA_5_6 = prod(copyA_1_2,copyA_3_4);
	char* scale_A = "9";
	BigInteger scalarA = stringToBigInteger(scale_A);
	BigInteger multiplierA = prod(copyA_5_6,scalarA);
	BigInteger copyB_1 = stringToBigInteger(e2);
	BigInteger copyB_2 = stringToBigInteger(e2);
	BigInteger copyB_1_2 = prod(copyB_1,copyB_2);
	BigInteger copyB_3_4 = copy(copyB_1_2);
	BigInteger copyB_5_6 = prod(copyB_1_2,copyB_3_4);
	BigInteger copyB_7_8 = prod(copyB_5_6,copyB_1);
	char* scaleB = "16";
	BigInteger scalarB = stringToBigInteger(scaleB);
	BigInteger multiplierB = prod(copyB_7_8,scalarB);
	C = sum(multiplierA,multiplierB);

	printBigInteger(out,C);
	freeBigInteger(&C);
	freeBigInteger(&copyA_1);
	freeBigInteger(&copyA_2);
	freeBigInteger(&copyA_1_2);
	freeBigInteger(&copyA_3_4);
	freeBigInteger(&copyA_5_6);
	freeBigInteger(&scalarA);
	freeBigInteger(&multiplierA);
	freeBigInteger(&copyB_1);
	freeBigInteger(&copyB_2);
	freeBigInteger(&copyB_1_2);
	freeBigInteger(&copyB_3_4);
	freeBigInteger(&copyB_5_6);
	freeBigInteger(&copyB_7_8);
	freeBigInteger(&scalarB);
	freeBigInteger(&multiplierB);
	printf("\n\n");
    freeBigInteger(&A);
    freeBigInteger(&B);
    fclose(in);
    fclose(out);
}
