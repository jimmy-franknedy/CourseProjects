//Cole Malinowski
//smalinow@ucsc.edu
#include <stdint.h>
#include "Message.h"
#include "BattleBoats.h"
#include "Agent.h"
#include "Negotiation.h"
#include <stdio.h>
#include "Field.h"
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct {
    AgentState state;
    NegotiationData randA;
    NegotiationData randB;
    NegotiationData hashA;
    int counter;
    BB_Error errorCode;
} AgentInformation;
static AgentInformation AgentInfo;
static Message returnMessage;
static Field myField;
static Field otherField;
static NegotiationOutcome coinflip;
static GuessData shot;
static SquareStatus previousSquareFREA;
static uint8_t checkWin;
static Message ARmessage;

void ClearMessage(void);
void ResetButton(void);

void ClearMessage(void)
{
    returnMessage.param0 = 0;
    returnMessage.param1 = 0;
    returnMessage.param2 = 0;
    returnMessage.type = MESSAGE_NONE;
}

/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *      Initializing both fields
 *      Placing boats on your field
 *      Setting the start state of the Agent SM
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 * 
 * The agent can assume that stdlib's rand() function has been seeded properly, so it is not needed
 * to call srand() inside AgentInit().
 *  */
void AgentInit(void)
{
    FieldInit(&myField, &otherField); //init my field
    FieldAIPlaceAllBoats(&myField); //place my boats
    AgentInfo.state = AGENT_STATE_START; //set starting state
    AgentInfo.counter = 0;
    AgentInfo.randA = 0;
    AgentInfo.randB = 0;
    AgentInfo.hashA = 0;
    ClearMessage();
    //place boats on your field
    //set starting state of SM
}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 * 
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent. 
 * 
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible 
 * for generating the Message struct, not for encoding or sending it.
 */
//BB_EVENT_START_BUTTON, //1
//    BB_EVENT_RESET_BUTTON, //2
//    BB_EVENT_CHA_RECEIVED, //3
//    BB_EVENT_ACC_RECEIVED, //4
//    BB_EVENT_REV_RECEIVED, //5
//    BB_EVENT_SHO_RECEIVED, //6
//    BB_EVENT_RES_RECEIVED, //7
//    BB_EVENT_MESSAGE_SENT, //8
//    BB_EVENT_ERROR, //9

Message AgentRun(BB_Event event)
{

    ARmessage.param0 = 0; //clearing the return message struct
    ARmessage.param1 = 0;
    ARmessage.param2 = 0;
    ARmessage.type = MESSAGE_NONE;
    switch (AgentInfo.state) {
    case AGENT_STATE_START:
        if (event.type == BB_EVENT_START_BUTTON) { // Generate randA and hash a
            AgentInfo.randA = rand(); // send CHA message
            AgentInfo.hashA = NegotiationHash(AgentInfo.randA);
            FieldInit(&myField, &otherField);
            ARmessage.type = MESSAGE_CHA;
            if (ARmessage.type != MESSAGE_CHA) {
                AgentInfo.errorCode = BB_ERROR_INVALID_MESSAGE_TYPE;
            }
            ARmessage.param0 = AgentInfo.hashA;
            ARmessage.param1 = '\n';
            ARmessage.param2 = 0;
            AgentInfo.state = AGENT_STATE_CHALLENGING;
            //printf("1\n");
            break;
        }
        if (event.type == BB_EVENT_CHA_RECEIVED) { //generate B and go t oaccepting
            AgentInfo.randB = rand();
            ARmessage.type = MESSAGE_ACC;
            if (ARmessage.type != MESSAGE_ACC) {
                AgentInfo.errorCode = BB_ERROR_INVALID_MESSAGE_TYPE;
            }
            ARmessage.param0 = AgentInfo.randB;
            ARmessage.param1 = 0;
            ARmessage.param2 = 0;
            FieldInit(&myField, &otherField);
            AgentInfo.state = AGENT_STATE_ACCEPTING;
            //printf("2\n");
            break;
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            ResetButton();
            break;
        }
        break;
    case AGENT_STATE_CHALLENGING:
        if (event.type == BB_EVENT_ACC_RECEIVED) { //coinflip to see who goes first
            ARmessage.type = MESSAGE_REV;
            if (ARmessage.type != MESSAGE_REV) {
                AgentInfo.errorCode = BB_ERROR_INVALID_MESSAGE_TYPE;
            }
            ARmessage.param0 = AgentInfo.randA;
            ARmessage.param1 = 0;
            ARmessage.param2 = 0;
            coinflip = NegotiateCoinFlip(AgentInfo.randA, AgentInfo.randB);
            if (coinflip == HEADS) {
                AgentInfo.state = AGENT_STATE_WAITING_TO_SEND;
            } else {
                AgentInfo.state = AGENT_STATE_DEFENDING;
            }
            // printf("3\n");
            break;
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            ResetButton();
            break;
        }
        break;
    case AGENT_STATE_ACCEPTING:
        if (event.type == BB_EVENT_REV_RECEIVED) {
            int cheat = NegotiationVerify(AgentInfo.randA, AgentInfo.hashA);
            if (cheat == FALSE) { //make sure there was no cheating
                AgentInfo.errorCode = BB_ERROR_BAD_CHECKSUM; //if there was cheating throw proper
                AgentInfo.state = AGENT_STATE_END_SCREEN; //error and go to end screen

            }
            if (cheat == TRUE) {
                if (coinflip == TAILS) {
                    shot = FieldAIDecideGuess(&otherField); //AI guess shot
                    ARmessage.type = MESSAGE_SHO;
                    if (ARmessage.type != MESSAGE_SHO) {
                        AgentInfo.errorCode = BB_ERROR_INVALID_MESSAGE_TYPE;
                    }
                    ARmessage.param0 = shot.row; //translate shot to message struct
                    ARmessage.param1 = shot.col;
                    ARmessage.param2 = 0;
                    AgentInfo.state = AGENT_STATE_ATTACKING;
                    printf("4\n");
                    break;
                }
                if (coinflip == HEADS) { //if heads go to defending state
                    AgentInfo.state = AGENT_STATE_DEFENDING;
                }
                printf("5\n");
            }
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            ResetButton();
            break;
        }
        break;
    case AGENT_STATE_ATTACKING:
        //printf("6\n");
        if (event.type == BB_EVENT_RES_RECEIVED) {
            FieldUpdateKnowledge(&otherField, &shot); //update field knowledge with given shot
            checkWin = FieldGetBoatStates(&otherField); //check to see if won
            if (checkWin == 0) {
                AgentInfo.state = AGENT_STATE_END_SCREEN;
            } else {
                AgentInfo.state = AGENT_STATE_DEFENDING; //if didnt win go to defending
            }
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            ResetButton();
            break;
        }
        break;
    case AGENT_STATE_DEFENDING:
        //printf("7\n");
        if (event.type == BB_EVENT_SHO_RECEIVED) {
            //update own field send res
            GuessData AIguess = FieldAIDecideGuess(&myField); //get AI guess of shot
            previousSquareFREA = FieldRegisterEnemyAttack(&myField, &AIguess); //check enemy attack
            FieldUpdateKnowledge(&myField, &AIguess); //update that attack

            checkWin = FieldGetBoatStates(&myField); //check if win/lose
            if (checkWin == 0) {
                AgentInfo.state = AGENT_STATE_END_SCREEN;
            } else {
                ARmessage.type = MESSAGE_RES; //if not win return the shot result
                if (ARmessage.type != MESSAGE_RES) {
                    AgentInfo.errorCode = BB_ERROR_INVALID_MESSAGE_TYPE;
                }
                ARmessage.param0 = AIguess.row;
                ARmessage.param1 = AIguess.col;
                ARmessage.param2 = AIguess.result;
                AgentInfo.state = AGENT_STATE_WAITING_TO_SEND;
                break;
            }
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            ResetButton();
            break;
        }
        break;
    case AGENT_STATE_WAITING_TO_SEND:
        //printf("8\n");
        if (event.type == BB_EVENT_MESSAGE_SENT) {
            AgentInfo.counter++; //count increment
            //decide guess send SHO
            GuessData AIguess2 = FieldAIDecideGuess(&otherField);
            ARmessage.type = MESSAGE_SHO;
            if (ARmessage.type != MESSAGE_SHO) {
                AgentInfo.errorCode = BB_ERROR_INVALID_MESSAGE_TYPE;
            }
            ARmessage.param0 = AIguess2.row;
            ARmessage.param1 = AIguess2.col;
            ARmessage.param2 = 0;
            AgentInfo.state = AGENT_STATE_ATTACKING;
            break;
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            ResetButton();
            break;
        }
        break;
    case AGENT_STATE_END_SCREEN:
        // printf("9\n");
        //display error
        switch (AgentInfo.errorCode) {
        case BB_SUCCESS:
            printf("\nSuccess\n");
            break;
        case BB_ERROR_BAD_CHECKSUM:
            printf("\nError: Bad Check Sum\n");
            break;
        case BB_ERROR_PAYLOAD_LEN_EXCEEDED:
            //AgentInfo.errorCode = BB_ERROR_PAYLOAD_LEN_EXCEEDED;
            //This is from lab9 mains code

            printf("\nError: Exceeded Max Payload Length\n");
            break;
        case BB_ERROR_CHECKSUM_LEN_EXCEEDED:
            //AgentInfo.errorCode = BB_ERROR_CHECKSUM_LEN_EXCEEDED;
            //This is from lab9 mains code
            printf("\nError: Exceeded Max Payload Length\n");
            break;
        case BB_ERROR_CHECKSUM_LEN_INSUFFICIENT:
            //AgentInfo.errorCode = BB_ERROR_CHECKSUM_LEN_INSUFFICIENT;
            //should be checked in lab9 main
            printf("\nError: Insufficient Check Sum Length\n");
            break;
        case BB_ERROR_INVALID_MESSAGE_TYPE:
            //AgentInfo.errorCode = BB_ERROR_INVALID_MESSAGE_TYPE;
            printf("\nError: Invalid Message Type\n");
            break;
        case BB_ERROR_MESSAGE_PARSE_FAILURE:
            //AgentInfo.errorCode = BB_ERROR_MESSAGE_PARSE_FAILURE;
            //should be checked in Lab09 main
            printf("\nError: Message Parse Failure\n");
            break;
        }
        break;
    }
    if (event.type == BB_EVENT_RESET_BUTTON) {
        ResetButton();
    }
    return ARmessage;

}

/** * 
 * @return Returns the current state that AgentGetState is in.  
 * 
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void)
{
    AgentState x = AgentInfo.state;
    return x;
}

/** * 
 * @param Force the agent into the state given by AgentState
 * 
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState)
{
    AgentInfo.state = newState;
}

void ResetButton(void)
{
    AgentInfo.counter = 0;
    AgentInfo.hashA = 0;
    AgentInfo.randA = 0;
    AgentInfo.randB = 0;
    FieldInit(&myField, &otherField);
    AgentInfo.state = AGENT_STATE_START;

}