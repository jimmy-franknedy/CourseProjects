#include "Message.h"
#include <stdio.h>
#include <stdint.h>
#include "BattleBoats.h"
#include "BOARD.h"
#include "Ascii.h"

static char message1[] = "SHO,2,3"; //payloads
static char message2[] = "CHA,6";
//static char fullmess1[] = "SHO,2,3*55\n"; //full message string
//static char fullmess2[] = "CHA,6*50\n";
uint8_t checksum1;
uint8_t checksum2;
static BB_Event struct1;
static BB_Event struct2;
static BB_Event struct3;

int main(void)
{
    BOARD_Init();
    checksum1 = Message_CalculateChecksum(message1); //
    checksum2 = Message_CalculateChecksum(message2); //
    static char csstr1[] = "55"; //85 checksum in decimal
    static char csstr2[] = "50"; //80 checksum in decimal
    //printf("%x %x\n\n\n", checksum1, checksum2);

    //printf("\ntest 1: %d\ntest 2: %d", checksum1, checksum2);
    printf("Calculate Checksum test: \n");
    if (checksum1 == 85) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed Test 1\n");
    }
    if (checksum2 == 80) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed Test 2\n");
    }
    struct1.type = BB_EVENT_SHO_RECEIVED;
    struct1.param0 = 3;
    struct1.param1 = 2;

    struct2.type = BB_EVENT_CHA_RECEIVED;
    struct2.param0 = 16;

    int x = Message_ParseMessage(message1, csstr1, &struct1); // 
    int y = Message_ParseMessage(message2, csstr2, &struct2);
    //printf("\n%d %d %d\n", struct1.type, struct2.type, x);
    printf("Parse Message test: \n");
    if (x == STANDARD_ERROR || struct1.type != BB_EVENT_SHO_RECEIVED) {
        printf("Failed Test 1\n");
    } else {
        printf("Passed Test 1\n");
    }
    if (y == STANDARD_ERROR || struct2.type != BB_EVENT_CHA_RECEIVED) {
        printf("Failed Test 2\n");
    } else {
        printf("Passed Test 2\n\n\n");
    }
    printf("Message Encode test: \n");

    Message messagestruct1;
    //"SHO,2,3*55\n"; //full message string
    messagestruct1.param0 = 2;
    messagestruct1.param1 = 3;
    messagestruct1.param2 = 0;
    messagestruct1.type = MESSAGE_SHO;

    Message messagestruct2;
    //"CHA,6*50\n"; // full message string
    messagestruct2.param0 = 6;
    messagestruct2.param1 = 0;
    messagestruct2.param2 = 0;
    messagestruct2.type = MESSAGE_CHA;

    char empty1[100];
    char empty2[100];
    char mes2[] = "$CHA,6*50";
    char mes1[] = "$SHO,2,3*55";

    Message_Encode(empty1, messagestruct1);
    printf("\nExpected: %s\n", mes1);
    printf("Actual:   %s\n", empty1);
    Message_Encode(empty2, messagestruct2);
    printf("\n\nExpected: %s\n", mes2);
    printf("Actual:   %s\n", empty2);

    unsigned char decode1 = '$';
    unsigned char decode2 = 'S';
    unsigned char decode3 = 'H';
    unsigned char decode4 = 'O';
    unsigned char decode5 = ',';
    unsigned char decode6 = '2';
    unsigned char decode7 = ',';
    unsigned char decode8 = '3';
    unsigned char decode9 = '*';
    unsigned char decode10 = '5';
    unsigned char decode11 = '5';
    unsigned char decode12 = '\n';

    printf("\nMessage Decode Test:\n");
    Message_Decode(decode1, &struct3); // $
    Message_Decode(decode2, &struct3); // S
    Message_Decode(decode3, &struct3); // H
    Message_Decode(decode4, &struct3); // 0
    Message_Decode(decode5, &struct3); // ,
    Message_Decode(decode6, &struct3); // 2
    Message_Decode(decode7, &struct3); // ,
    Message_Decode(decode8, &struct3); // 3
    Message_Decode(decode9, &struct3); // *
    Message_Decode(decode10, &struct3); // 5
    Message_Decode(decode11, &struct3); // 5
    Message_Decode(decode12, &struct3); // \n
    printf("\nExpected: $6,2,3\n");
    printf("Actual:   $%d,%d,%d\n", struct3.type, struct3.param0, struct3.param1);
    while (1);
}
/**
 * Message_Decode reads one character at a time.  If it detects a full NMEA message,
 * it translates that message into a BB_Event struct, which can be passed to other 
 * services.
 * 
 * @param char_in - The next character in the NMEA0183 message to be decoded.
 * @param decoded_message - a pointer to a message struct, used to "return" a message
 *                          if char_in is the last character of a valid message, 
 *                              then decoded_message
 *                              should have the appropriate message type.
 *                              otherwise, it should have type NO_EVENT.
 * @return SUCCESS if no error was detected
 *         STANDARD_ERROR if an error was detected
 * 
 * note that ANY call to Message_Decode may modify decoded_message.
 */
//int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event);

