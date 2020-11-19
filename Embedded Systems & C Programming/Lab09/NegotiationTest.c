// Jimmy Franknedy
// jfrankne@ucsc.edu

#include "xc.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>
#include "BOARD.h"
#include "Negotiation.h"

#define TOTAL_TEST 6
#define PERCENT 100

static int totalPassCounter = 0;
static float totalPassPercent = 0;
static int PassCounterNegotiationHash = 0;
static int PassCounterNegotiationVerify = 0;
static int PassCounterNegotiateCoinFlip = 0;

static NegotiationData Secret_1 = 411;
static NegotiationData Secret_2 = 91;
static NegotiationData Result_A = 22284;
static NegotiationData Result_B = 8281;
static NegotiationData Example_C = 15;
static NegotiationData Example_D = 80;
static NegotiationData Example_E = 79;

int main(void)
{
    BOARD_Init();
    OledInit();
    // Run the test harness
    printf("----------------------------------------\n");
    printf("Entering Negotiation.h Test Harness.\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing NegotiationHash()\n");
    NegotiationData Test_1 = NegotiationHash(Secret_1);
    if (Test_1 == Result_A) {
        PassCounterNegotiationHash++;
        printf("Passed V1\n");
    } else {
        printf("An error occurred in NegotiationHash\n");
    }
    NegotiationData Test_2 = NegotiationHash(Secret_2);
    if (Test_2 == Result_B) {
        PassCounterNegotiationHash++;
        printf("Passed V2\n");
    } else {
        printf("An error occurred in NegotiationHash\n");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing NegotiationVerify()\n");
    int Test_3 = NegotiationVerify(Secret_1, Result_A);
    if (Test_3 == TRUE) {
        PassCounterNegotiationVerify++;
        printf("Passed V1\n");
    } else {
        printf("An error occurred in NegotiationVerify\n");
    }
    int Test_4 = NegotiationVerify(Secret_2, Result_B);
    if (Test_4 == TRUE) {
        PassCounterNegotiationVerify++;
        printf("Passed V2\n");
    } else {
        printf("An error occurred in NegotiationVerify\n");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing NegotiateCoinFlip()\n");
    NegotiationOutcome Test_5 = NegotiateCoinFlip(Example_C, Example_D);
    if (Test_5 == TAILS) {
        PassCounterNegotiateCoinFlip++;
        printf("Passed V1\n");
    } else {
        printf("An error occurred in NegotiationCoinFlip\n");
    }
    NegotiationOutcome Test_6 = NegotiateCoinFlip(Example_C, Example_E);
    if (Test_6 == HEADS) {
        PassCounterNegotiateCoinFlip++;
        printf("Passed V2\n");
    } else {
        printf("An error occurred in NegotiationCoinFlip\n");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    printf("----------------------------------------\n");
    printf("Final Results:\n");
    printf("PASSED(%d/2): NegotiationHash()\n", PassCounterNegotiationHash);
    printf("PASSED(%d/2): NegotiationVerify()\n", PassCounterNegotiationVerify);
    printf("PASSED(%d/2): NegotiateCoinFlip()\n", PassCounterNegotiateCoinFlip);
    // Calculate the total percentage of the tests passed
    totalPassCounter = PassCounterNegotiateCoinFlip + PassCounterNegotiationHash +
            PassCounterNegotiationVerify;
    totalPassPercent = (double) totalPassCounter;
    totalPassPercent /= (double) TOTAL_TEST;
    totalPassPercent *= (double) PERCENT;
    printf("TOTAL (%d/6): %.2f%%\n", totalPassCounter, (double) totalPassPercent);
    printf("----------------------------------------\n");
    while (1);
}