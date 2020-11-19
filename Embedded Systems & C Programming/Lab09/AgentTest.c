// Jimmy Franknedy
// jfrankne@ucsc.edu

#include "xc.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>
#include "BOARD.h"
#include "Field.h"
#include "BattleBoats.h"
#include "Negotiation.h"
#include "Message.h"
#include "Agent.h"
//#include "Agent.c"

#define TOTAL_TEST 3
#define PERCENT 100

static int totalPassCounter = 0;
static float totalPassPercent = 0;
static int PassCounterAgentInit = 0;
static int PassCounterAgentRun = 0;
static int PassCounterAgentGetState = 0;
static int PassCounterAgentSetState = 0;

int main(void)
{
    BOARD_Init();
    // Create a struct for Agent.c

    typedef struct{
        AgentState state;
        Field myField;
        Field otherField;
        NegotiationData randA;
        NegotiationData randB;
        NegotiationData hashA;
        int counter;
    } AgentInformation;
    static AgentInformation AgentInfo;
//    
    // Create a module-level instance of that struct.
    
    // Create the SM used for the struct.
//    switch (AgentInfo.state) {
//    case AGENT_STATE_START:
//        break;
//    case AGENT_STATE_CHALLENGING:
//        break;
//    case AGENT_STATE_ACCEPTING:
//        break;
//    case AGENT_STATE_ATTACKING:
//        break;
//    case AGENT_STATE_DEFENDING:
//        break;
//    case AGENT_STATE_WAITING_TO_SEND:
//        break;
//    case AGENT_STATE_END_SCREEN:
//        break;
//    case AGENT_STATE_SETUP_BOATS:
//        break;
//    }
    // Run the test harness
    printf("--------------------------------\n");
    printf("Entering Agent.h Test Harness.\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing AgentInit()\n");
    AgentInit();
    if (AgentInfo.state == AGENT_STATE_START) {
        PassCounterAgentInit++;
    } else {
        printf("An error occurred in AgentInit()\n");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing AgentRun()\n");
    BB_Event Test_1;
    Test_1.type = BB_EVENT_START_BUTTON;
    Message Result1 = AgentRun(Test_1);
    if (Result1.type != MESSAGE_NONE) {
        PassCounterAgentRun++;
    } else {
        printf("An error occurred in AgentRun() 1\n");
    }
    BB_Event Test_2;
    Test_2.type = BB_EVENT_NO_EVENT;
    Message Result2 = AgentRun(Test_2);
    if (Result2.type == MESSAGE_NONE) {
        PassCounterAgentRun++;
    } else {
        printf("An error occurred in AgentRun() 2\n");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    printf("\nTesting AgentGet/SetState()\n");
    AgentSetState(AGENT_STATE_START);
    AgentState getstateTest1 = AgentGetState();
    if (getstateTest1 == AGENT_STATE_START){
        printf("Passed Test 1\n");
    }
    else{
        printf("Failed Test 1\n");
    }
    AgentSetState(AGENT_STATE_ATTACKING);
    AgentState getstateTest2 = AgentGetState();
    if (getstateTest2 == AGENT_STATE_ATTACKING){
        printf("Passed Test 2\n");
    }
    else{
        printf("Failed Test 2\n");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
//    printf("Testing AgentSetState()\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////
    printf("\n--------------------------------\n");
    printf("Final Results:\n");
    printf("PASSED(%d/1): AgentInit()\n", PassCounterAgentInit);
    printf("PASSED(%d/2): AgentRun()\n", PassCounterAgentRun);
//    printf("PASSED(%d/2): AgentGetState()\n", PassCounterAgentGetState);
//    printf("PASSED(%d/2): AgentSetState()\n", PassCounterAgentSetState);
    // Calculate the total percentage of the tests passed
    totalPassCounter = PassCounterAgentInit + PassCounterAgentGetState +
            PassCounterAgentRun + PassCounterAgentSetState;
    totalPassPercent = (double) totalPassCounter;
    totalPassPercent /= TOTAL_TEST;
    totalPassPercent *= PERCENT;
    printf("TOTAL (%d/%d): %.2f%%\n", totalPassCounter, TOTAL_TEST, (double) totalPassPercent);
    printf("--------------------------------\n");
    while (1);
}