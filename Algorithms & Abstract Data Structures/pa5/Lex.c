/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		Lex.c
* File Description: Application file for Lex.c using the Dictionary ADT
*********************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"
#define MAX 1010
void printKeysInOrder (FILE* out, Dictionary D);
int main(int argc, char* argv[])
{
	// Check the command line arguments for proper number of arguments
    if(argc != 3)
    {
        fprintf(stderr, "Inproper Usage: Invalid Lex input\n");
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

    // Counter of number of lines in file
    int num_string_lines = 0;

    // Dummy variable to hold incoming strings
    char buffer[MAX] = " ";

    // Get the number of lines in the file
    while(!feof(in))
    {
        fgets(buffer,MAX,in);
        num_string_lines++;
    }
    // Return to the 'start' of the file
    fseek(in,0,SEEK_SET);

    // Allocated Heap Memory for dedicated array
    char** InputArr = calloc(num_string_lines,sizeof(char*));

    // Loop through input file; grab string; add string to array of strings
    for(int i = 0; i < num_string_lines; i++)
    {
        // Allocate memory for each string
        InputArr[i] = calloc(MAX,sizeof(char));
        if(i == num_string_lines-1)
        {
            fgets(InputArr[i],MAX,in);
            int temp_length = strlen(InputArr[i]);
            char updated[temp_length+1];
            sprintf(updated,"%s\n",InputArr[i]);
            strcpy(InputArr[i],updated);
        }
        else fgets(InputArr[i],MAX,in);
    }
    Dictionary D = newDictionary(0);
    for(int i = 0; i< num_string_lines; i++) insert(D,InputArr[i],i);
	printKeysInOrder(out,D);
    // Exit cleanly
    freeDictionary(&D);
    for(int i = 0; i< num_string_lines; i++) free(InputArr[i]);
    free(InputArr);
    fclose(in);
    fclose(out);

    // Return the program with a success!
    return EXIT_SUCCESS;
}