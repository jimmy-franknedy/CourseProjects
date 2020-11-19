/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		BigInteger.c
* File Description: Function implementation for BigInteger.c
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"
#include "BigInteger.h"
#define POWER 9						// **UPDATE BEFORE SUBMITTING**
#define BASE 1000000000 	        // **UPDATE BEFORE SUBMITTING**
#define TEN 10
#define MAX 9

// Exported type -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj
{
	long sign;	// indicates the sign of the BigInteger
	List L;		// List of single elements
}BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
	BigInteger B = malloc(sizeof(BigIntegerObj));
	assert(B != NULL);
	B->sign = 0;
	B->L = newList();
	return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN)
{
	if(pN != NULL && *pN != NULL)
	{
		makeZero(*pN);
		freeList(&(*pN)->L);
		free(*pN);
		*pN = NULL;
	}
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and
// 0 if N is in the zero state.
int sign(BigInteger N)
{
	// Checking validity
	if(N == NULL)
	{
		fprintf(stderr, "Access function: calling sign() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	// Return the sign of the BigInteger
	return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
	// Checking validity
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "Access function: calling compare() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Differnt signs
	if(A->sign > B->sign) return 1;
	else if (A->sign < B->sign) return -1;

	// Same Signs Different Length
	else if(A->sign == B->sign && length(A->L) != length(B->L))
	{
		if(length(A->L) > length(B->L))
		{
			if(sign(A) == 1) return 1;
			else return -1;
		}
		else if(length(A->L) < length(B->L))
		{
			if(sign(B) == 1) return -1;
			else return 1;
		}
	}

	// Same Signs Same Length
	else if (A->sign == B->sign && length(A->L) == length(B->L))
	{
		moveFront(A->L);
		moveFront(B->L);
		int cont = 1;
		while((index(A->L) != -1 && index(B->L) != -1) && cont == 1)
		{
			if(get(A->L) == get(B->L))
			{			
				moveNext(A->L);
				moveNext(B->L);
			}
			else cont = 0;
		}
		if(cont) return 0;
		else
		{
			if((get(A->L)) > (get(B->L)))
			{
				if(sign(A) == 1) return 1;
				else return -1;
			}
			else if(sign(B) == 1) return -1;
		}
	}
	return 1;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
	// Checking validity
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "Access function: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}

	if(A->sign == B->sign)
	{
		int result = equalz(A->L,B->L);
		if(result) return 1;
	}
	return 0;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
	// Checking validity
	if(N == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling makeZero() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	N->sign = 0;
	clear(N->L);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
	// Checking validity
	if(N == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling negate() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(sign(N) != 0)
	{
		if(N->sign == -1) N->sign = 1;
		else N->sign = -1;
	}
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
	// Checking validity
	if(s == NULL)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling stringToBigInteger() on NULL char* reference\n");
		exit(EXIT_FAILURE);			
	}
	if(strlen(s) == 0)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling stringToBigInteger() on empty char* reference\n");
		exit(EXIT_FAILURE);				
	}
	if(strlen(s) == 0 && (*s == 43 || *s == 45))
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling stringToBigInteger() on sign only char* reference\n");
		exit(EXIT_FAILURE);				
	}
	BigInteger S = newBigInteger();
	int counter = strlen(s);
	long temp = *s;
	if(temp == 45 || temp == 43)
	{
		if(temp == 45) S->sign = -1;	
		else S->sign = 1;	
		counter--;
		s++;
	}
	else S->sign = 1;
	if(counter <= 9 && counter < BASE)
	{
		long push = atoi(s);
		append(S->L,push);
	}
	else
	{
		List g = newList();
		while((counter % POWER) != 0)
		{
			temp = *s;
			temp -= 48;
			append(g,temp);
			counter--;
			s++;
			if((counter % POWER) == 0)
			{
				moveBack(g);
				long v = 0;
				long m = 1;
				while(index(g) != -1)
				{
					v += (get(g) * m);
					m *= 10;
					movePrev(g);
				}
				append(S->L,v);
			}
		}
		while(counter != 0)
		{
			if(length(g) > 0) clear(g);
			for(int i = 0; i < POWER; i++)
			{
				temp = *s;
				temp -= 48;
				append(g,temp);
				counter--;
				s++;	
			}
			moveBack(g);
			long v = 0;
			long m = 1;
			while(index(g) != -1)
			{
				v += (get(g) * m);
				m *= 10;
				movePrev(g);
			}
			append(S->L,v);
		}
		freeList(&g);
	}
	return S;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
	// Checking validity
	if(N == NULL)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling copy() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	BigInteger C = newBigInteger();
	C->sign = N->sign;
	freeList(&C->L);
	C->L = copyList(N->L);
	return C;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
	// Checking validity
	if(S == NULL || A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling add() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(length(S->L) > 0)
	{
		S->sign = 0;
		makeZero(S);
	}
	int originalSignA = sign(A);
	int originalSignB = sign(B);
	if(sign(A) == sign(B))
	{
		S->sign = A->sign;
		moveBack(A->L);
		moveBack(B->L);
		moveFront(S->L);
		long carryOut = 0;

		// Loop through each of 'A' and 'B' data values
		while(index(A->L) != -1 && index(B->L) != -1)
		{
			long result = get(A->L) + get(B->L) + carryOut;
			carryOut = 0;
			while(result >= BASE)
			{
				result -= BASE;
				carryOut++;
			}
			prepend(S->L,result);
			moveFront(S->L);
			movePrev(A->L);
			movePrev(B->L);		
		}
		if(index(A->L) != -1)
		{
			while(index(A->L) != -1)
			{
				if(carryOut == 0) prepend(S->L,get(A->L));
				else
				{
					long temp = get(A->L) + carryOut;
					carryOut = 0;
					while(temp >= BASE)
					{
						temp -= BASE;
						carryOut++;
					}
					prepend(S->L,temp);
				}
				movePrev(A->L);
			}
		}
		if(index(B->L) != -1)
		{
			while(index(B->L) != -1)
			{
				if(carryOut == 0) prepend(S->L,get(B->L));
				else
				{
					long temp = get(B->L) + carryOut;
					carryOut = 0;
					while(temp >= BASE)
					{
						temp -= BASE;
						carryOut++;
					}
					prepend(S->L,temp);
				}
				movePrev(B->L);
			}
		}
		if(carryOut != 0) prepend(S->L,carryOut);
	}

	// Cond. pos + neg = 0 ; neg + pos = 0
	else if(sign(A) != sign(B) && (equalz(A->L,B->L) == 1))
	{
		S->sign = 0;
		append(S->L,0);
	}
	// Cond. adding 0
	else if(sign(A) == 0 || sign(B) == 0)
	{
		freeList(&S->L);
		if(sign(A) == 0)
		{
			S->L = copyList(B->L);
			S->sign = sign(B);
		}
		else
		{
			S->L = copyList(A->L);
			S->sign = sign(A);
		}
	}
	// Cond. pos + neg < 0 ; pos + neg > 0 ; neg + pos < 0 ; neg + pos > 0

	// 						  A    B
	// i)	pos + neg < 0 >>  2 + -5 = -3 >> 5 - 2 (neg Out)
	// ii)	pos + neg > 0 >>  5 + -2 = 3  >> 5 - 2 
	// iii)	neg + pos < 0 >> -2 + 5  = 3  >> 5 - 2
	// iv)	neg + pos > 0 >> -5 + 2  = -3 >> 5 - 2 (neg Out)
	else
	{
		if(sign(A) == 1)
		{
			negate(B);
			if(compare(A,B) == 1)
			{
				S->sign = 1;
				subtract(S,A,B);
			}
			else
			{
				S->sign = -1;
				subtract(S,B,A);
			}
		}
		else
		{
			negate(A);
			if(compare(A,B) == 1)
			{
				S->sign = -1;
				subtract(S,A,B);
			}
			else
			{
				S->sign = 1;
				subtract(S,B,A);
			}
		}
	}
	A->sign = originalSignA;
	B->sign = originalSignB;
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
	// Checking validity
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling sum() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	BigInteger S = newBigInteger();
	add(S,A,B);
	return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
	// Checking validity
	if(D == NULL || A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling subtract() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(length(D->L) > 0)
	{
		D->sign = 0;
		makeZero(D);
	}
	int originalSignA = sign(A);
	int originalSignB = sign(B);
	// Zero cases
	if((sign(A) == sign(B)) && equalz(A->L,B->L) == 1)
	{
		D->sign = 0;
		append(D->L,0);
	}
	else if(sign(A) == 0 || sign(B) == 0)
	{
		freeList(&D->L);
		if(sign(A) == 0)
		{
			D->L = copyList(B->L);
			if(sign(B) == 1) D->sign = -1;
			else D->sign = 1;
		}
		else
		{
			D->L = copyList(A->L);
			if(sign(A) == 1) D->sign = -1;
			else D->sign = 1;
		}
	}

	// Add case
	else if (sign(A) != sign(B))
	{
		if(sign(A) == 1)
		{
			negate(B);
			add(D,A,B);
		}
		else
		{
			negate(A);
			add(D,A,B);
			negate(D);
		}
	}

	// Main Subtraction
	else if (sign(A) == 1 && sign(B) == 1 && compare(A,B) == 1)
	{
		if(sign(D) == 0) D->sign = 1;
		moveBack(A->L);
		moveBack(B->L);
		moveFront(D->L);
		long carryOut = 0;

		// Loop through each of 'A' and 'B' data values
		while(index(A->L) != -1 && index(B->L) != -1)
		{
			long result = (get(A->L) - get(B->L)) - carryOut;
			carryOut = 0;
			while(result < 0)
			{
				result += BASE;
				carryOut++;
			}
			prepend(D->L,result);
			moveFront(D->L);
			movePrev(A->L);
			movePrev(B->L);	
		}
		if(index(A->L) != -1)
		{
			prepend(D->L,get(A->L));
			movePrev(A->L);
		}
	}	
	else
	{
		// pos - pos
		if(sign(A) == 1 && sign(B) == 1)
		{
			// A > B (i.e 5 - 2)
			if(compare(A,B) == 1)
			{
				subtract(D,A,B);
				D->sign = 1;
			}

			// A < B (i.e 2 - 5)
			else
			{
				subtract(D,B,A);
				D->sign = -1;
			}
		}

		// neg - neg
		if(sign(A) == -1 && sign(B) == -1)
		{
			negate(A);
			negate(B);

			// A > B   (i.e -5 - -2)
			// negated (i.e  5 - 2 )
			if(compare(A,B) == 1)
			{
				// 5 - 2 = 3 >> -3
				subtract(D,A,B);
				D->sign = -1;
			}

			// A < B 	(i.e -2 - -5)
			// negated  (i.e  2 - 5 )
			else
			{
				// 5 - 2 = 3 >> 3
				subtract(D,B,A);
				D->sign = 1;
			}
		}
	}
	A->sign = originalSignA;
	B->sign = originalSignB;
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
	// Checking validity
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling diff() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	BigInteger D = newBigInteger();
	subtract(D,A,B);
	return D;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
	// Checking validity
	if(P == NULL || A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling multiply() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(length(P->L) > 0)
	{
		P->sign = 0;
		makeZero(P);
	}
	int originalSignA = sign(A);
	int originalSignB = sign(B);
	int specialSkip = 1;

	// Zero case
	if(sign(A) == 0 || sign(B) == 0)
	{
		P->sign = 0;
		append(P->L,0);
		specialSkip = 0;
	}
	// One case
	if((length(A->L) == 1 || length(B->L) == 1) && specialSkip == 1)
	{
		moveBack(B->L);
		moveBack(A->L);
		if(length(A->L) == 1 && get(A->L) == 1)
		{
			freeList(&P->L);
			P->L = copyList(B->L);
			specialSkip = 0;
		}
		else if (length(B->L) == 1 && get(B->L) == 1)
		{
			freeList(&P->L);
			P->L = copyList(A->L);
			specialSkip = 0;
		}
	}
	if(specialSkip == 1)
	{
		if(sign(A) != 1) negate(A);
		if(sign(B) != 1) negate(B);
		if(compare(A,B) == -1)
		{
			swap(A,B);
			specialSkip = 2;
		}
		moveBack(A->L);
		moveBack(B->L);
		long carryOut = 0;
		long rowCount = 0;
		BigInteger temp = newBigInteger();
		temp->sign = 1;
		BigInteger prev = newBigInteger();
		prev->sign = 1;
		append(prev->L,0);
		long base = BASE;
		while(index(B->L) != -1)
		{
			while(index(A->L) != -1)
			{
				long product = ((get(A->L)) * (get(B->L))) + carryOut;
				if(product >= base)
				{
					List Z = normalize(product,base);
					moveFront(Z);
					carryOut = get(Z);
					moveNext(Z);
					prepend(temp->L,get(Z));
					freeList(&Z);
				}
				else
				{
					prepend(temp->L,product);
					carryOut = 0;
					
				}
			movePrev(A->L);		
			}
			if(carryOut != 0) prepend(temp->L,carryOut);
			for(int i = 0; i<rowCount; i++) append(temp->L,0);
			rowCount++;
			// =========================
			add(P,temp,prev);
			freeList(&temp->L);
			temp->L = newList();
			freeList(&prev->L);
			prev->L = copyList(P->L);
			// =========================
			movePrev(B->L);
			moveBack(A->L);
			carryOut = 0;
		}
		freeBigInteger(&temp);
		freeBigInteger(&prev);
	}
	if(specialSkip == 2) swap(A,B);
	A->sign = originalSignA;
	B->sign = originalSignB;
	if(sign(A) != 0 && sign(B) != 0)
	{
		// Negative case
		if(sign(A) != sign(B)) P->sign = -1;
		// Positive case
		else if(sign(A) == sign(B)) P->sign = 1;
	}
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
	// Checking validity
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger Arithmetic Operations: calling prod() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	BigInteger P = newBigInteger();
	multiply(P,A,B);
	return P;
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
	// Checking validity
	if(N == NULL)
	{
		fprintf(stderr, "Other Operations: calling printBigInteger() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(sign(N) == -1)
	{
		fprintf(out, "-");
		fprintf(stdout, "-");
	}
	moveFront(N->L);
	int length = 0;
	while(index(N->L) != -1)
	{
		long value = get(N->L);
		if(value != 0)
		{
			int base = 1;
			if(length > 0)
			{
				for(int i = 0; i < POWER; i++)
				{
					if(value < base) fprintf(out, "0");
					base *= TEN;
				}
			}
			fprintf(out, "%ld",value);
			length++;
		}
		else if(value == 0 && length > 0)
		{
			int base = 1;
			for(int i = 0; i < POWER-1; i++)
			{
				if(value < base) fprintf(out, "0");
				base *= TEN;
			}
			fprintf(out, "%ld",value);
			fprintf(stdout, "%ld",value);
			length++;
		}
		moveNext(N->L);
	}
	if(length == 0) fprintf(out, "0");
	fprintf(out, "\n");
}

// Private functions ----------------------------------------------------------

// normalize()
// returns the normalized long value and edits the 'carryOut'
List normalize(long value, long base)
{

	List L = newList();
	long carryOut = 0;
	long temp = 0;
	long tempMultiplyer = 0;
	long multiplyer = 0;
	int power = TEN;
	while(value >= base)
	{
		if(multiplyer == 0)
		{
			multiplyer = base;
			while(value >= multiplyer)
			{
				multiplyer *= 10;
				tempMultiplyer++;
			}
			for(int i = 0; i < tempMultiplyer-1; i++) power *= TEN;
		}
		multiplyer /= 10;
		power /= 10;
		tempMultiplyer--;
		while(value >= multiplyer)
		{
			value -= multiplyer;
			temp++;
		}
		while(value < 0)
		{
			value += multiplyer;
			temp++;
		}
		carryOut += (temp * power);
		temp = 0;
	}
	append(L,carryOut);
	append(L,value);
	return L;
}

// generateBigInteger()
// Generates a BigInteger for testing 
// Input 'N' should be EMPTY!
void generate(BigInteger N,int s,long data_1, long data_2, long data_3)
{
	N->sign = s;
	append(N->L,data_1);
	append(N->L,data_2);
	append(N->L,data_3);
}

// printBigIntegerValues()
// Prints out the values in the BigInteger seperated by a space
void printBigIntegerValues(BigInteger N)
{
	if(sign(N) == -1) printf("-");
	moveFront(N->L);
	while(index(N->L) != -1)
	{
		printf("%ld ",get(N->L));
		moveNext(N->L);
	}
	printf("\n");
}

// setSign()
// Sets the sign of a BigInteger
void setSign(BigInteger N,int s)
{
	N->sign = s;
}

// generateSingle()
// Generates a BigInteger with one element for testing
void generateSingle(BigInteger N,int s,long data_1)
{
	N->sign = s;
	append(N->L,data_1);
}

// swap()
// swaps 2 BigIntegers and their signs
void swap(BigInteger A, BigInteger B)
{
	BigInteger temp = newBigInteger();
	temp->sign = sign(A);
	freeList(&temp->L);
	temp->L = copyList(A->L);
	A->sign = sign(B);
	freeList(&A->L);
	A->L = copyList(B->L);
	B->sign = sign(temp);
	freeList(&B->L);
	B->L = copyList(temp->L);
	freeBigInteger(&temp);
}