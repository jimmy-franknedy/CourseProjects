########################################################################################
# Created by: 	Franknedy, Jimmy
#		jfrankne
#             	7 May 2019
# 
# Assignment:	Lab3: MIPS!
#		CMPE 012, Computer Systems and Assembly Language
#		UC Santa Cruz, Spring 2019
#
# Description:	This program takes an integer input and outputs the integer's factorial
#
# Notes:       	This program is intended to be run from the MARS IDE.
########################################################################################
# 
#	Pseudocode:	
#	- Provide the user the main prompt
#	> Check to see if the user's input is valid
#		>	0 <= Input <= 10
#	> User's input is valid
#		> Move input into $t0
#		> Save original input in $t7
#		> Decrement $t7 by 1 and store in $t6
#		> Loop
#			> Multiply $t6 and $t7
#			> Decrement $t7 by 1
#			> If $t7 = 0 jump to 'finish'
#			> If $t7 != 0 jump back to 'loop'
# 	> User's input is invalid
#		> Displays the Invalid Prompt
# 		> Returns the user to the main prompt
# 	> Finish
#		> Print the user's input
#		> Print the '!'
#		> Print space
#		> Print the '='
#		> Print space
#		> Print the final factorial
#	> End 
#
########################################################################################

.data
#Prompt the user to input a number value
promptNumber:	.asciiz "Enter an integer between 0 and 10: "

#Prompts the user that their input is invalid
promptInvalid:	.asciiz "Invalid Entry! \n"

.text
 #Prompt the user to input a number
 start:	nop
 li	$v0, 4
 la	$a0, promptNumber
 syscall
 
 #User inputs a value
 li	$v0, 5
 syscall
 
 #Moves the value of $v0 into $t0
 move	$t0, $v0
 
 #Check if the input is less than or equal to 0x10
 bgt	$t0, 0xa, invalid
 ble	$t0, 0xa, valid_1 
 
 #Check to see if the input is greater than 0
 valid_1:	nop
 bge 	$t0, $zero, valid_setup
 b	invalid
 
 #Directs the user if the value is less than or equal to 10
 valid_setup:	nop
 
 #Save the user's input into another register
 add	$t7, $zero, $t0
 
 #Special condition if the user input is 0
 beq	$t0, 0x0, cond_zero
 bne	$t0, 0x0, cond_reg
 
 cond_zero:	nop
 add	$t0, $t0, 1
 
 cond_reg:	nop
 #Create the register to store the product of the factorials
 add	$t6, $zero, 1
 mul	$t6, $t6, $t0
 subi	$t0, $t0, 1
 
 valid:		nop
 #Multiplying Loop
 beq	$t0, $zero, finish
 mul	$t6, $t6, $t0
 subi	$t0, $t0, 1
 j valid
 
 #Directs the user if the value is greater than 10
 invalid:	nop
 
 #Print the invalid message
 li	$v0, 4
 la	$a0, promptInvalid
 syscall
 
 #Returns to prompt the user to input a value
 j	start
 
 finish:	nop
 #Print the user's number
 li	$v0, 1
 la	$a0, ($t7)
 syscall
 
 #Print the exclaimation mark
 li	$v0, 11
 la	$a0, 0x21
 syscall
 
 #Print a space 
 li	$v0, 11
 la	$a0, 0x20
 syscall
   
 #Print the equal sign
 li	$v0, 11
 la	$a0, 0x3D
 syscall
 
 #Print a space
 li	$v0, 11
 la	$a0, 0x20
 syscall
  
 #Print the final factorial
 li	$v0, 1
 la	$a0, ($t6)
 syscall
 
########################################################################################
#
#	REGISTER USAGE
#
#	$t0	-	hold the value of the user's integer input
#	$t6	-	holds the user's input -1, used to do the factorial calculation
#	$t7	-	holds the value of the user's integer so it can be used in the
#			final prompt that shows the user their input and its factorial.
#
########################################################################################
