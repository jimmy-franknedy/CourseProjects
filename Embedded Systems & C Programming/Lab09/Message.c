// Jimmy Franknedy
// jfrankne@ucsc.edu

#include "xc.h"
#include "Message.h"
#include "stdio.h"
#include <stdint.h>
#include "BattleBoats.h"
#include "BOARD.h"
#include <string.h>

#define RESULT_LENGTH 20
#define SPRINTF_ERROR -1
#define DOLLAR '$'
#define DOLLAR_STRING "$"
#define NEWLINE '\n'
#define COMMA ','
#define CHECKSUM_DELIMITER '*'
#define CHECKSUM_DELIMITER_STRING "*"
#define CHA "CHA"
#define CHA_COMPLETE ",%u"
#define ACC "ACC" 
#define ACC_COMPLETE ",%u"
#define REV "REV"
#define REV_COMPLETE ",%u"
#define SHO "SHO"
#define SHO_COMPLETE ",%d,%d"
#define RES "RES"
#define RES_COMPLETE ",%u,%u,%u"
#define VALUE4 4
#define VALUE3 3
#define VALUE2 2
#define VALUE1 1
#define NEG_VALUE1 -1
#define ASCII_TO_DEC_0 48
#define ASCII_TO_DEC_9 57
#define ASCII_A 65
#define ASCII_F 70
#define HEX_COMMA 44

typedef enum {
    WAITING_START_DELIMITER,
    RECORDING_PAYLOAD,
    RECORDING_CHECKSUM,
} STATEMODE;

typedef struct StateMachine {
    STATEMODE state;
    char bufferString[VALUE4];
    char createdString[MESSAGE_MAX_LEN];
    char payloadString[MESSAGE_MAX_PAYLOAD_LEN];
    char checksumString[MESSAGE_CHECKSUM_LEN];
    char messageID[VALUE3];
    int checkSumCount;
    int payloadCount;
    int messageLength;
    int reset;
    int pass;
} SM;

static int setParam = 0;
static int commaCount = 0;

/**
 * Given a payload string, calculate its checksum
 * 
 * @param payload       //the string whose checksum we wish to calculate
 * @return              //The resulting 8-bit checksum 
 */
uint8_t Message_CalculateChecksum(const char* payload)
{
    char DataValue;
    uint8_t CalculateCheckSum = 0;
    int checkDataValueLoop = 0;
    int payloadLength = strlen(payload);
    while (checkDataValueLoop < payloadLength && DataValue != CHECKSUM_DELIMITER) {
        DataValue = payload[checkDataValueLoop];
        if (DataValue != DOLLAR && DataValue != CHECKSUM_DELIMITER) {
            CalculateCheckSum ^= DataValue;
        }
        checkDataValueLoop++;
    }
    return CalculateCheckSum;
}

/**
 * Given a payload and its checksum, verify that the payload matches the checksum
 * 
 * @param payload       //the payload of a message
 * @param checksum      //the checksum (in string form) of  a message,
 *                          should be exactly 2 chars long, plus a null char
 * @param message_event //An event corresponding to the parsed message.
 *                      //If the message could be parsed successfully,
 *                          message_event's type will correspond to the message type and 
 *                          its parameters will match the message's data fields.
 *                      //If the message could not be parsed,
 *                          message_events type will be BB_EVENT_ERROR
 * 
 * @return STANDARD_ERROR if:
 *              CHECKED! the payload does not match the checksum
 *              CHECKED! the checksum string is not two characters long
 *              CHECKED! the message does not match any message template
 * 
 *          SUCCESS otherwise
 * 
 * Please note!  sscanf() has a couple compiler bugs that make it a very
 * unreliable tool for implementing this function. * 
 */
int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event)
{
    // Validate that the CheckSum has length of MESSAGE_CHECKSUM_LEN
    int CheckSumStringLength = strlen(checksum_string);
    if (CheckSumStringLength != MESSAGE_CHECKSUM_LEN) {
        return STANDARD_ERROR;
    }
    //Check if the MessageID is valid
    char MessageIDSingleCheck[1];
    char MessageIDCheck[VALUE2];
    int SingleCheck = 0;
    memset(MessageIDCheck, 0, sizeof (MessageIDCheck));
    while (SingleCheck != VALUE3) {
        MessageIDSingleCheck[0] = payload[SingleCheck];
        strcat(MessageIDCheck, MessageIDSingleCheck);
        SingleCheck++;
    }
    if (!strcmp(MessageIDCheck, CHA) ||
            !strcmp(MessageIDCheck, ACC) ||
            !strcmp(MessageIDCheck, REV) ||
            !strcmp(MessageIDCheck, SHO) ||
            !strcmp(MessageIDCheck, RES)) {
        int CommaCount = 0;
        while (MessageIDSingleCheck[0] != NULL && MessageIDSingleCheck[0] != CHECKSUM_DELIMITER) {
            MessageIDSingleCheck[0] = payload[SingleCheck];
            if (MessageIDSingleCheck[0] == COMMA) {
                CommaCount++;
            }
            SingleCheck++;
        }
        int ValidMessage = 0;
        char ResultString[RESULT_LENGTH];
        if (!strcmp(MessageIDCheck, CHA) && CommaCount == VALUE1) {
            sprintf(ResultString, "%s%s", MessageIDCheck, CHA_COMPLETE);
            ValidMessage = 1;
        } else if (!strcmp(MessageIDCheck, ACC) && CommaCount == VALUE1) {
            sprintf(ResultString, "%s%s", MessageIDCheck, ACC_COMPLETE);
            ValidMessage = 1;
        } else if (!strcmp(MessageIDCheck, REV) && CommaCount == VALUE1) {
            sprintf(ResultString, "%s%s", MessageIDCheck, REV_COMPLETE);
            ValidMessage = 1;
        } else if (!strcmp(MessageIDCheck, SHO) && CommaCount == VALUE2) {
            sprintf(ResultString, "%s%s", MessageIDCheck, SHO_COMPLETE);
            ValidMessage = 1;
        } else if (!strcmp(MessageIDCheck, RES) && CommaCount == VALUE3) {
            sprintf(ResultString, "%s%s", MessageIDCheck, RES_COMPLETE);
            ValidMessage = 1;
        } else {
            return STANDARD_ERROR;
        }
        if (ValidMessage == 1) {
            if (!strcmp(ResultString, PAYLOAD_TEMPLATE_CHA) ||
                    !strcmp(ResultString, PAYLOAD_TEMPLATE_ACC) ||
                    !strcmp(ResultString, PAYLOAD_TEMPLATE_REV) ||
                    !strcmp(ResultString, PAYLOAD_TEMPLATE_SHO) ||
                    !strcmp(ResultString, PAYLOAD_TEMPLATE_RES)) {
                // If the Message is a valid Message Type; validate CheckSum matches the payload
                char CalculatedCheckSum[MESSAGE_CHECKSUM_LEN];
                int checkString = sprintf(CalculatedCheckSum, "%X", Message_CalculateChecksum(payload));
                if (checkString == SPRINTF_ERROR) {
                    return STANDARD_ERROR;
                } else {
                    int CheckString = strcmp(CalculatedCheckSum, checksum_string);
                    if (!CheckString) {
                        return SUCCESS;
                    }
                }
            }
        }
    }
    return STANDARD_ERROR;
}

/**
 * Encodes the coordinate data for a guess into the string `message`. This string must be big
 * enough to contain all of the necessary data. The format is specified in PAYLOAD_TEMPLATE_COO,
 * which is then wrapped within the message as defined by MESSAGE_TEMPLATE. 
 * 
 * The final length of this
 * message is then returned. There is no failure mode for this function as there is no checking
 * for NULL pointers.
 * 
 * @param message            The character array used for storing the output. 
 *                              Must be long enough to store the entire string,
 *                              see MESSAGE_MAX_LEN.
 * @param message_to_encode  A message to encode
 * @return                   The length of the string stored into 'message_string'.
                             Return 0 if message type is MESSAGE_NONE.
 */
int Message_Encode(char *message_string, Message message_to_encode)
{
    char buffer[MESSAGE_MAX_LEN] = DOLLAR_STRING;
    switch (message_to_encode.type) {
    case MESSAGE_NONE:
        return 0;
        break;
    case MESSAGE_CHA:
        sprintf(message_string, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);
        break;
    case MESSAGE_ACC:
        sprintf(message_string, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);
        break;
    case MESSAGE_REV:
        sprintf(message_string, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);
        break;
    case MESSAGE_SHO:
        sprintf(message_string, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, message_to_encode.param1);
        break;
    case MESSAGE_RES:
        sprintf(message_string, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, message_to_encode.param1, message_to_encode.param2);
        break;
    default:
        return 0;
    }
    // Add the dollar sign and clear the message_string in order to rewrite it!
    strcat(buffer, message_string);
    sprintf(message_string, "%s%s", buffer, CHECKSUM_DELIMITER_STRING);
    // Get the payload
    uint8_t GetPayload = Message_CalculateChecksum(message_string);
    // Add the payload to the string
    sprintf(message_string, "%s%X", message_string, GetPayload);
    // Get the length of the string!
    int resultLength = strlen(message_string);
    // Clear buffer
    memset(buffer, 0, sizeof (buffer));
    return resultLength;
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
int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event)
{
    // Initialize the struct.
    static SM MessageDecode = {
        .state = WAITING_START_DELIMITER,
        .messageLength = 0,
        .checkSumCount = 0,
        .reset = 0,
        .pass = 0,
    };

    switch (MessageDecode.state) {
        ////////////////////////////////////////////////////////////////////////////////////////////
    case WAITING_START_DELIMITER:
        // Resets the string data in struct here, if needed.
        if (MessageDecode.reset == 1) {
            // Reset the length counters
            MessageDecode.messageLength = 0;
            MessageDecode.checkSumCount = 0;
            MessageDecode.payloadCount = 0;
            // Reset the string arrays.
            memset(MessageDecode.checksumString, 0, sizeof (MessageDecode.checksumString));
            memset(MessageDecode.createdString, 0, sizeof (MessageDecode.createdString));
            memset(MessageDecode.payloadString, 0, sizeof (MessageDecode.payloadString));
            memset(MessageDecode.bufferString, 0, sizeof (MessageDecode.bufferString));
            memset(MessageDecode.messageID, 0, sizeof (MessageDecode.messageID));
            // Having the arrays reset, if the char_in is a dollar sign, then the program is ready
            // to read in the following inputs, without having to worry about clearing the strings.
            MessageDecode.reset = 0;
            commaCount = 0;
            setParam = 0;
        }
        if (char_in == DOLLAR) {
            MessageDecode.state = RECORDING_PAYLOAD;
            // Since '$' is apart of the string we must increment to the next length.
            MessageDecode.createdString[MessageDecode.messageLength] = char_in;
            MessageDecode.messageLength++;
            MessageDecode.pass = 1;
        }
        break;
        //////////////////////////////////////////////////////////////////////////////////////////// 
    case RECORDING_PAYLOAD:
        // Set the code to record parameters
        // If the char_in is an invalid char: reset the SM (which would also reset the struct data)
        if (char_in == NEWLINE ||
                char_in == DOLLAR ||
                MessageDecode.messageLength == MESSAGE_MAX_LEN) {
            MessageDecode.reset = 1;
            MessageDecode.state = WAITING_START_DELIMITER;
            // Returns error as documented.
            return STANDARD_ERROR;
            // If the char_in is a valid character: add char_in to the string.
        } else if (char_in != NEWLINE &&
                char_in != DOLLAR &&
                char_in != CHECKSUM_DELIMITER &&
                MessageDecode.messageLength != MESSAGE_MAX_LEN &&
                MessageDecode.payloadCount != MESSAGE_MAX_PAYLOAD_LEN) {
            // Passes valid checkpoint
            MessageDecode.pass = 1;
            // Add char_in to the string and manually increment the length of the string.
            MessageDecode.createdString[MessageDecode.messageLength] = char_in;
            // Add char_in specifically into the custom payload string
            MessageDecode.payloadString[MessageDecode.payloadCount] = char_in;
            MessageDecode.messageLength++;
            MessageDecode.payloadCount++;
            if (setParam == 1) {
                int charConvertToDecimal = (int) char_in;
                charConvertToDecimal -= ASCII_TO_DEC_0;
                switch (commaCount) {
                case 1:
                    decoded_message_event->param0 = charConvertToDecimal;
                    break;
                case 2:
                    decoded_message_event->param1 = charConvertToDecimal;
                    break;
                case 3:
                    decoded_message_event->param2 = charConvertToDecimal;
                    break;
                }
                setParam = 0;
                charConvertToDecimal = 0;
            }
            if (char_in == COMMA) {
                commaCount++;
                setParam = 1;
            }
        } else if (char_in == CHECKSUM_DELIMITER) {
            // If char_in is the CHECKSUM_DELIMITER then change the SM and increment length
            MessageDecode.createdString[MessageDecode.messageLength] = char_in;
            MessageDecode.messageLength++;
            MessageDecode.state = RECORDING_CHECKSUM;
            // Passes valid checkpoint
            MessageDecode.pass = 1;
        } else {
            MessageDecode.reset = 1;
            MessageDecode.state = WAITING_START_DELIMITER;
            return STANDARD_ERROR;
        }
        break;
        ////////////////////////////////////////////////////////////////////////////////////////////
    case RECORDING_CHECKSUM:
        if (MessageDecode.messageLength <= MESSAGE_MAX_LEN &&
                MessageDecode.checkSumCount <= MESSAGE_CHECKSUM_LEN) {
            if ((char_in >= ASCII_TO_DEC_0 && char_in <= ASCII_TO_DEC_9) ||
                    (char_in >= ASCII_A && char_in <= ASCII_F)) {
                // Passes a valid checkpoint
                MessageDecode.pass = 1;
                // Add char_in into the whole string and increment total message length.
                MessageDecode.createdString[MessageDecode.messageLength] = char_in;
                MessageDecode.messageLength++;
                // Add char_in into the dedicated string and increment the checksum count.
                MessageDecode.checksumString[MessageDecode.checkSumCount] = char_in;
                MessageDecode.checkSumCount++;
            } else if (char_in == NEWLINE) {
                // Passes a valid checkpoint
                MessageDecode.pass = 1;
                int CheckDecode = Message_ParseMessage(MessageDecode.payloadString,
                        MessageDecode.checksumString, decoded_message_event);
                if (CheckDecode) {
                    // Generate the corresponding BB_Event based on the Message ID!
                    int IDLoop;
                    for (IDLoop = 1; IDLoop < VALUE4; IDLoop++) {
                        sprintf(MessageDecode.bufferString, "%c", MessageDecode.createdString[IDLoop]);
                        strcat(MessageDecode.messageID, MessageDecode.bufferString);
                    }
                    if (!strcmp(MessageDecode.messageID, CHA)) {
                        decoded_message_event->type = BB_EVENT_CHA_RECEIVED;
                    } else if (!strcmp(MessageDecode.messageID, ACC)) {
                        decoded_message_event->type = BB_EVENT_ACC_RECEIVED;
                    } else if (!strcmp(MessageDecode.messageID, REV)) {
                        decoded_message_event->type = BB_EVENT_REV_RECEIVED;
                    } else if (!strcmp(MessageDecode.messageID, SHO)) {
                        decoded_message_event->type = BB_EVENT_SHO_RECEIVED;
                    } else if (!strcmp(MessageDecode.messageID, RES)) {
                        decoded_message_event->type = BB_EVENT_RES_RECEIVED;
                    }
                    int length = strlen(MessageDecode.checksumString);
                    MessageDecode.checksumString[length - VALUE3] = 0;
                    // Reset SM.
                    MessageDecode.reset = 1;
                    MessageDecode.state = WAITING_START_DELIMITER;
                    return SUCCESS;
                }
            }
        } else {
            // Resets the state machine here
            MessageDecode.reset = 1;
            MessageDecode.state = WAITING_START_DELIMITER;
            // Return an error as documented.
            return STANDARD_ERROR;
        }
        break;
        ////////////////////////////////////////////////////////////////////////////////////////////
    default:
        // By default, return an error, reset the struct and SM.
        MessageDecode.state = WAITING_START_DELIMITER;
        return STANDARD_ERROR;
        ////////////////////////////////////////////////////////////////////////////////////////////
    }
    if (MessageDecode.pass) {
        MessageDecode.pass = 0;
        return SUCCESS;
    } else {
        MessageDecode.pass = 0;
        MessageDecode.reset = 1;
        MessageDecode.state = WAITING_START_DELIMITER;
        // Since the char_in was invalid then the whole string is invalid
        // So set BB_EVENT_NO_EVENT & clear struct values
        decoded_message_event->type = BB_EVENT_NO_EVENT;
        decoded_message_event->param0 = 0;
        decoded_message_event->param1 = 0;
        decoded_message_event->param2 = 0;
        return STANDARD_ERROR;
    }
}