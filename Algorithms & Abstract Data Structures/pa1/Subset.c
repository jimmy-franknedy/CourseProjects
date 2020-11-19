
// Name:		 Jimmy Franknedy
// CruzID:    	 jfrankne
// Class: 		 CSE-015
// Date:		 10/10/2019
// Project Name: Subset.c
// Project Desc: A program that uses recursion to print out all the k-element subsets of the n-element set {1, 2, 3, … , 𝑛}, where both 𝑛 and 𝑘 are given on the command line.

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define ERROR_STRING "Usage: Subset 𝑛 𝑘 (𝑛 and 𝑘 are ints satisfying 0<=𝑘<=𝑛<=100)\n"
#define MARK -1
#define PASS_VALUE 2

// Declare Function Prototypes
void printSubsets(int B[], int n, int k, int i);
void printSet(int B[], int n);

int main(int argc, char* argv[]) 
{
	int n,status,pass = 0;
	int N_val = 0;
	int K_val = 0;
	char ch;
	for (int i = 0; i <argc; i++)
	{
      // Parse as an integer
		status = sscanf(argv[i], "%d%c", &n, &ch);

		// Check to see what is the value of the current [i]th argument given in the command line
		if(status==1) pass++;
	}
	if(pass == PASS_VALUE)
	{
		// Set the value of "n"
		N_val = atoi(argv[1]);

  		// Set the value of "k"
		K_val = atoi(argv[2]);

		if(N_val >= K_val)
		{
			// Create the array to hold the subset
			int SubsetArray[MAX_SIZE+1];

			// Call the function
			printSubsets(SubsetArray,N_val,K_val,1);
		}
		// Print error argument
		else printf(ERROR_STRING);
	}
	// Print error argument
	else printf(ERROR_STRING);
	return 0;
}

void printSubsets(int B[], int n, int k, int i)
{
	if(k>n-i+1) return;
	else if(k == 0) printSet(B,n);
	else
	{
		B[i] = 1;
		printSubsets(B,n,k-1,i+1);
		B[i] = 0;
		printSubsets(B,n,k,i+1);
	}
}

void printSet(int B[], int n)
{
	static int CommaCounter = 0;
	printf("{");
	for(int i = 1; i<n+1; i++)
	{
		if(B[i] == 1) CommaCounter++;
	} 
	CommaCounter--;
	if(CommaCounter == MARK) printf(" ");
	for(int h = 1; h < n+1; h++)
	{
		if(B[h] == 1)
		{
			printf("%d", h);
			if(CommaCounter)
			{
				printf(",");
				CommaCounter--;
			}
		}
	}
	printf("}\n");
}