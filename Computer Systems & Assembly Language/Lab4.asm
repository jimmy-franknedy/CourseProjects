########################################################################################
# Created by: 	Franknedy, Jimmy
#		jfrankne
#             	15 May 2019
# 
# Assignment:	Lab4: Roman Numeral Conversion
#		CMPE 012, Computer Systems and Assembly Language
#		UC Santa Cruz, Spring 2019
#
# Description:	This program takes a Roman Numeral input and outputs the binary
#               representation.
#
# Notes:       	The program arugment section in this lab is used to retrieve
#		the user's input as a part of the program's functionality
########################################################################################
# 
#	Pseudocode:
#	
#	Potential Error Points to Avoid:
#	a.	M is an invalid character
#	b.	No more than 3 consecutive identical Roman Numerals
#	c.	Only 1 'I' 'X' 'C' can be used as the leading numeral in part of a subtraction	FOR SUBTRACTION
#		pair. [Not needed as already implemented by d,e,f]
#	d.	'I' can only be placed before V and X [ or 0x0000]					FOR SUBTRACTION
#	e.	'X' can only be placed before L and C [ or 0x0000]					FOR SUBTRACTION
#	f.	'C' can only be placed before D	       [ or 0x0000]					FOR SUBTRACTION
#	g.	'D' 'L' 'V' can only appear once							
#	
#	> Program prompts the user for a Roman Numeral Input
#
#	> Program accesses the user's input
#
#	> Program checks for possible errors [A, B, C, D, E, F, G] within the user's input	
#
#		> Program encounters an error
#			- Program will display an error message
#			- Program will return to the main prompt
#		
#		> Program encoutners no error
#			- Program takes the length of the Roman Numeral and stores in a reg (r)
#			- Program decodes the Roman Numerals (represented as Hex characters)
#			  to decimal
#				>> Loop
#				a. Program takes with the first Roman Numeral (i) 
#				b. Program converts (i) to a decimal representation		
#				c. Program adds (i) to the total running sum (s)
#				d. Program increments (i++)
#				e. Program compares (i) to (i++)
#					e.1: if (i) > (i++), then Program does (s) - (i++)
#					e.2: if (i) < (i++), then Program does (s) + (i++)
#				f. Program increments (i++)
#				g. Program decrements (r--)
#				h. Program compares length
#					h.1 if (r) is = 0, Program exits
#					h.2 if (r) is != 0, Program loops back to a.
#			- Program decodes the decimal representation to binary
#				>> Loop
#				* Program starts with a reg hold a 2 power (2P) *
#				a. Program takes (s)
#				b. Program takes (s) & (2P)
#					c.1 If (s) - (2P) then...
#						c.1.i 	'1' is inputted into a binary register (b)
#						c.1.ii 	(2P) gets divided by 2
#						c.1.iii	(b) gets shifted to the left by 4B
#					c.2 if (s) !- (2p) then..
#						c.1.i 	'0' is inputted into a binary register (b)
#						c.1.ii 	(2P) gets divided by 2
#						c.1.iii	(b) gets shifted to the left by 4B
#				d. Program checks to see if (s) is 0
#					d.1 If (s) = 0, then program exits
#					d.2 If (s) != 0, then program jumps back to a.
#			- Program outputs the base 2 representation of the Roman Numeral
#				>> Loop
#				* Program gets the length of (l) *
#				a. Program goes to (b)
#				b. Program goes to the first value of (b) called (k)
#				c. Program prints (k)
#				d. Program incremebts (k++)
#				e. Program decrements (l--)
#					f.1 If (l) = 0, Program terminates
#					f.2 If (l) != 0, Program jumps to a.
#			- Program Exits
#				li	$v0 10
#				syscall
#
########################################################################################
 .data
 
 #Various prompts for the program
 numeralArray:		.space 1000000
 promptRomanNumeral:	.asciiz	"You entered the Roman numerals: \n"
 promptBinaryRep:	.asciiz "The binary representation is: \n"
 promptBinary:		.asciiz "0b"
 promptInvalidArg:	.asciiz "Error: Invalid program argument."
 promptLine:		.asciiz "\n"
 zero:			.asciiz "0"
 one:			.asciiz "1"
 .text
 
 ########################################################################################
 # 
 #	Psuedocode:	This part of the program will check to see if the user's inputted
 #        	    	Roman Numerals are valid. If so the program will iterrate through
 #                 	each one of the bytes and run it through 'tests' to see if the
 #			character  (and it's pair are valid)
 #
 #    Register Use:	$t0	- 	the byte at the (i)th position of the Roman Numeral
 #			$t1	- 	the byye at the (i+1)th position of the Roman Numeral
 #			$t2	-	the byte at the (i+2)th position of the Roman Numeral
 #			$t3	-	the hex value of the byte in the (i)th position
 #			$t4	-	copy of the length of the user's Roman Numeral String
 #			$t5	-	the length of the user's Roman Numeral String
 #			$t6	-	the counter used to calculate sum/ diff of $t0 $t1 $t2
 #			$t7	-	the total sum counter; the global total
 #			$t8	-       the hex value of the byte in the (i+1)th position
 #			$t9	-	the tree branch counter; tells whether a method is used
 #
 ########################################################################################
 
 #Prints promptRomanNumeral
 li	$v0 4
 la	$a0 promptRomanNumeral
 syscall
 
 #Prints the user's Roman Numeral
 li	$v0  4
 lw	$a0 ($a1)
 syscall
 
 #Prints new line
 li	$v0 4
 la	$a0 promptLine
 syscall
 syscall
 
 #Loop through the Roman Numeral to check for and invalid inputs.
 
 #Start by loading the first bit (i) into $t0
 li	$v0 4
 lw	$a0 ($a1)
 lb	$t0 ($a0)
 
 #Branch to the next step when the program has done reading the Roman Numberal
 checkRomanNumberalBit:	nop

 #Check for rule a.	M is an invalid character & also if it is an actual Roman Numeral
 checkA:		nop
 beq	$t0 0x49 checkB
 beq	$t0 0x56 checkB
 beq	$t0 0x58 checkB
 beq	$t0 0x4C checkB
 beq	$t0 0x43 checkB
 beq	$t0 0x44 checkB
 b	invalidArg
 
 #Check for rule b.	No more than 3 consecutive identical Roman Numerals
 checkB:		nop
 #Load (i+1) (i+2) (i+3)
 addi	$a0 $a0 1
   	$t1 ($a0)
 beq	$t1 $zero skip_1
 
 addi	$a0 $a0 1
 lb	$t2 ($a0)
 beq	$t2 $zero skip_2
 
 addi	$a0 $a0 1
 lb	$t3 ($a0)
 beq	$t3 $zero skip_3
 
 subi	$a0 $a0 3
 j	compare_B
 
 #Conditions for when the next terms are 0
 skip_1:	nop
 subi	$a0 $a0 1
 j	checkC
 
 skip_2:	nop
 subi	$a0 $a0 2
 j	checkC
 
 skip_3:	nop
 subi	$a0 $a0 3
 j	checkC
 
 #Compare them; (i+3) exists
 compare_B:	nop
 beq $t0, $t1, b_error1
 bne $t0, $t1, checkC
 
 b_error1:	nop
 beq $t1, $t2, b_error2
 bne $t1, $t2, checkC
 
 b_error2:	nop
 beq $t2, $t3, invalidArg
 bne $t2, $t3, checkC
 
 #Check for rule c.	'I' can only be placed before V and X
 
 checkC:		nop
 
 #Clears Registers for next sub-program to use
 add	$t1 $zero $zero
 add	$t2 $zero $zero
 add	$t3 $zero $zero
 
 #Load the next byte (i+1)
 addi	$a0 $a0 1
 lb	$t1 ($a0)
 subi	$a0 $a0 1
 
 #Check if (i) = I
 bne	$t0 0x49 checkD
 
 #Converts the Roman Numeral Values to Decimal in order to correct comparison 
 
 #This converts the first (i) Roman Numeral into a readable decimal that can be compared!
 convert_i_c:
 beq	$t0 0x49 updateI_c
 beq	$t0 0x56 updateV_c
 beq	$t0 0x58 updateX_c
 beq	$t0 0x4C updateL_c
 beq	$t0 0x43 updateC_c
 beq	$t0 0x44 updateD_c
 
 #Program updates $t2 to be 1
 updateI_c:	nop
 add	$t2 $zero 1
 b	convert_ii_c

 #Program updates $t2 to be 2
 updateV_c:	nop
 add	$t2 $zero 2
 b	convert_ii_c
 
 #Program updates $t2 to be3
 updateX_c:	nop
 add	$t2 $zero 3
 b 	convert_ii_c
 
 #Program updates $t2 to be 4 
 updateL_c:	nop
 add	$t2 $zero 4
 b	convert_ii_c

 #Program updates $t2 to be 5
 updateC_c:	nop
 add	$t2 $zero 5
 b	convert_ii_c

 #Program updates $t2 to be 6
 updateD_c:	nop
 add	$t2 $zero 6
 b	convert_ii_c
 
 #This converts the second (i+1) Roman Numeral into a readable decimal that can be compared!
 convert_ii_c:	nop
 
 beq	$t1 0x49 updateI_ii_c2
 beq	$t1 0x56 updateV_ii_c2
 beq	$t1 0x58 updateX_ii_c2
 beq	$t1 0x4C updateL_ii_c2
 beq	$t1 0x43 updateC_ii_c2
 beq	$t1 0x44 updateD_ii_c2
 
 #Program updates $t3 to be 1
 updateI_ii_c2:	nop
 add	$t3 $zero 1
 b	continue_c2
 
 #Program updates $t3 to be 2 
 updateV_ii_c2:	nop
 add	$t3 $zero 2
 b	continue_c2
 
 #Program updates $t3 to be 3
 updateX_ii_c2:	nop
 add	$t3 $zero 3
 b 	continue_c2
 
 #Program updates $t3 to be 4
 updateL_ii_c2:	nop
 add	$t3 $zero 4
 b 	continue_c2

 #Program updates $t3 to be 5
 updateC_ii_c2:	nop
 add	$t3 $zero 5
 b	continue_c2
 
 #Program updates $t3 to be 6
 updateD_ii_c2:	nop
 add	$t3 $zero 6
 b	continue_c2
 
 #Final checkpoint to see if (i) is valid for rule C.
 continue_c2:	nop
 bgt	$t3 $t2 check_c
 ble	$t3 $t2 checkD
 
 check_c:	nop
 bge	$t5 1 check_c_prev
 b	cont_check_c
 
 check_c_prev:
 sub	$a0 $a0 1
 lb	$t4 ($a0)
 addi	$a0 $a0 1
 bne	$t0 $t4 cont_check_c
 b	invalidArg
 
 cont_check_c:	nop
 beq	$t1, 0x56, checkD	# V = 0x56
 beq	$t1, 0x58, checkD	# X = 0x58 
 b	invalidArg
 
 #Check for rule d.	'X' can only be placed before L and C 
 
 checkD:		nop
 
 #Clears Registers for next sub-program to use
 add	$t1 $zero $zero
 add	$t2 $zero $zero
 add	$t3 $zero $zero
 
 #Load the next byte (i+1)
 addi	$a0 $a0 1
 lb	$t1 ($a0)
 subi	$a0 $a0 1
 
 #Check if (i) = X
 bne	$t0 0x58 checkE
 
 #Converts the Roman Numeral Values to Decimal in order to correct comparison
 
 #This converts the first (i) Roman Numeral into a readable decimal that can be compared!
 convert_i:
 beq	$t0 0x49 updateI
 beq	$t0 0x56 updateV
 beq	$t0 0x58 updateX
 beq	$t0 0x4C updateL
 beq	$t0 0x43 updateC
 beq	$t0 0x44 updateD
 
 #Program updates $t2 to be 1
 updateI:	nop
 add	$t2 $zero 1
 b	convert_ii

 #Program updates $t2 to be 2
 updateV:	nop
 add	$t2 $zero 2
 b	convert_ii
 
 #Program updates $t2 to be 3
 updateX:	nop
 add	$t2 $zero 3
 b 	convert_ii
 
 #Program updates $t2 to be 4
 updateL:	nop
 add	$t2 $zero 4
 b	convert_ii
 
 #Program updates $t2 to be 5
 updateC:	nop
 add	$t2 $zero 5
 b	convert_ii

 #Program updates $t2 to be 6
 updateD:	nop
 add	$t2 $zero 6
 b	convert_ii
 
 #This converts the second (i+1) Roman Numeral into a readable decimal that can be compared!
 convert_ii:	nop
 
 beq	$t1 0x49 updateI_ii
 beq	$t1 0x56 updateV_ii
 beq	$t1 0x58 updateX_ii
 beq	$t1 0x4C updateL_ii
 beq	$t1 0x43 updateC_ii
 beq	$t1 0x44 updateD_ii
 
 #Program updates $t3 to be 1
 updateI_ii:	nop
 add	$t3 $zero 1
 b	continue
 
 #Program updates $t3 to be 2
 updateV_ii:	nop
 add	$t3 $zero 2
 b	continue
 
 #Program updates $t3 to be 3
 updateX_ii:	nop
 add	$t3 $zero 3
 b 	continue
 
 #Program updates $t3 to be 4
 updateL_ii:	nop
 add	$t3 $zero 4
 b 	continue

 #Program updates $t3 to be 5
 updateC_ii:	nop
 add	$t3 $zero 5
 b	continue
 
 #Program updates $t3 to be 6
 updateD_ii:	nop
 add	$t3 $zero 6
 b	continue
 
 #Final checkpoint to see of (i) passes D. rule
 continue:	nop
 bgt	$t3 $t2 check_d
 ble	$t3 $t2 checkE
 
 check_d:	nop
 bge	$t5 1 check_d_prev
 b	cont_check_d
 
 check_d_prev:
 sub	$a0 $a0 1
 lb	$t4 ($a0)
 addi	$a0 $a0 1
 bne	$t0 $t4 cont_check_d
 b	invalidArg
 
 cont_check_d:	nop
 beq	$t1, 0x4C, checkE	# L = 0x4C
 beq	$t1, 0x43, checkE	# C = 0x43
 b	invalidArg
 
 #Check for rule e.	'C' can only be placed before D
 
 checkE:		nop
 
 #Clears Registers for next sub-program to use
 add	$t1 $zero $zero
 add	$t2 $zero $zero
 add	$t3 $zero $zero
 
 #Load the next byte (i+1)
 addi	$a0 $a0 1
 lb	$t1 ($a0)
 subi	$a0 $a0 1
 
 #Check if (i) = C
 bne	$t0 0x43 checkF
 
 #Converts the Roman Numeral Values to Decimal in order to correct comparison 
 
 #This converts the first (i) Roman Numeral into a readable decimal that can be compared!
 convert_i_e:
 beq	$t0 0x49 updateI_e
 beq	$t0 0x56 updateV_e
 beq	$t0 0x58 updateX_e
 beq	$t0 0x4C updateL_e
 beq	$t0 0x43 updateC_e
 beq	$t0 0x44 updateD_e
 
 #Program updates $t2 to be 1
 updateI_e:	nop
 add	$t2 $zero 1
 b	convert_ii_e

 #Program updates $t2 to be 2
 updateV_e:	nop
 add	$t2 $zero 2
 b	convert_ii_e
 
 #Program updates $t2 to be 3
 updateX_e:	nop
 add	$t2 $zero 3
 b 	convert_ii_e
 
 #Program updates $t2 to be 4
 updateL_e:	nop
 add	$t2 $zero 4
 b	convert_ii_e
 
 #Program updates $t2 to be 5
 updateC_e:	nop
 add	$t2 $zero 5
 b	convert_ii_e

 #Program updates $t2 to be 6
 updateD_e:	nop
 add	$t2 $zero 6
 b	convert_ii_e
 
 #This converts the second (i+1) Roman Numeral into a readable decimal that can be compared!
 convert_ii_e:	nop
 
 beq	$t1 0x49 updateI_ii_e2
 beq	$t1 0x56 updateV_ii_e2
 beq	$t1 0x58 updateX_ii_e2
 beq	$t1 0x4C updateL_ii_e2
 beq	$t1 0x43 updateC_ii_e2
 beq	$t1 0x44 updateD_ii_e2
 
 #Program updates $t2 to be 1
 updateI_ii_e2:	nop
 add	$t3 $zero 1
 b	continue_e2
 
 #Program updates $t2 to be 2
 updateV_ii_e2:	nop
 add	$t3 $zero 2
 b	continue_e2
 
 #Program updates $t2 to be 3
 updateX_ii_e2:	nop
 add	$t3 $zero 3
 b 	continue_e2
 
 #Program updates $t2 to be 4
 updateL_ii_e2:	nop
 add	$t3 $zero 4
 b 	continue_e2
 
 #Program updates $t2 to be 5
 updateC_ii_e2:	nop
 add	$t3 $zero 5
 b	continue_e2
 
 #Program updates $t2 to be 6
 updateD_ii_e2:	nop
 add	$t3 $zero 6
 b	continue_e2
 
 #Final checkpoint to see if (i) passes E. test
 continue_e2:	nop
 bgt	$t3 $t2 check_e
 ble	$t3 $t2 checkF
 
 check_e:		nop
 bge	$t5 1 check_e_prev
 b	cont_check_e
 
 check_e_prev:
 sub	$a0 $a0 1
 lb	$t4 ($a0)
 addi	$a0 $a0 1
 bne	$t0 $t4 cont_check_e
 b	invalidArg
 
 cont_check_e:		nop
 beq	$t1, 0x44, checkF
 b	invalidArg
 
 #Check for rule f.	'D' 'L' 'V' can only appear once
 checkF:		nop
 
 #Clears Registers for next sub-program to use
 add	$t1 $zero $zero
 add	$t2 $zero $zero
 add	$t3 $zero $zero
 
 beq	$t0, 0x44, d_counter
 bne	$t0, 0x44, pass_f1
 
 #Counter to check how many times does D appears
 d_counter:		nop
 addi	$t8, $t8, 1
 beq	$t8, 2, invalidArg
 blt	$t8, 2, checkG	
 
 pass_f1:		nop
 beq	$t0, 0x4C, l_counter
 bne	$t0, 0x4C, pass_f2
 
 #Counter to check how many times does F appears
 l_counter:		nop
 addi	$t7, $t7, 1
 beq	$t7, 2, invalidArg
 blt	$t7, 2, checkG
 
 pass_f2:		nop
 beq	$t0, 0x56, v_counter
 bne	$t0, 0x56, checkG
 
 #Counter to check how many times does V appears
 v_counter:		nop
 addi	$t6, $t6, 1
 beq	$t6, 2, invalidArg
 blt	$t6, 2, checkG
 bne	$t0, 0x56, checkG
 
 #Check for invalid subration or minimals
 checkG:		nop		
 addi	$a0 $a0 1
 lb	$t1 ($a0)
 subi	$a0 $a0 1
 beq	$t0 0x56 double_check_G
 beq	$t0 0x4C double_check_G
 b	checkH
 
 double_check_G:		nop
 beq	$t1 0x58 invalidArg
 beq	$t1 0x43 invalidArg
 b	checkH
 
 #Checks for invalid subtraction in the case of Roman Numeral
 #ABC where A<B B>C and A=C which will prompt the user 
 #of an error	
 checkH:		nop
 addi	$t1 $zero 0
 addi	$t2 $zero 0
 
 #Loads (i+1)
 addi	$a0 $a0 1
 lb	$t1 ($a0)
 subi	$a0 $a0 1
 beqz	$t1 updateCheck
 
 #Loads (i+2)
 addi	$a0 $a0 2
 lb	$t2 ($a0)
 subi	$a0 $a0 2
 beqz	$t2 updateCheck
 
 #Loops through (i) (i+1) (i+2) and converts to decimal
 check_h_convert:	nop
 move	$t3 $t0	
 beq	$t0 0x49 h_convert_one
 beq	$t0 0x56 h_convert_five
 beq	$t0 0x58 h_convert_ten
 beq	$t0 0x4C h_convert_fifty
 beq	$t0 0x43 h_convert_hundred
 beq	$t0 0x44 h_convert_fivehundred
 
 #Program converts the value of $t0 into 1
 h_convert_one:		nop
 addi	$t0 $zero 1
 b	check_h_convert_1
 
 #Program converts the value of $t0 into 5
 h_convert_five:	nop
 addi	$t0 $zero 5
 b	check_h_convert_1
 
 #Program converts the value of $t0 into 10
 h_convert_ten:		nop
 addi	$t0 $zero 10
 b	check_h_convert_1
 
 #Program converts the value of $t0 into 50
 h_convert_fifty:	nop
 addi	$t0 $zero 50
 b	check_h_convert_1
 
 #Program converts the value of $t0 into 100
 h_convert_hundred:	nop
 addi	$t0 $zero 100
 b	check_h_convert_1
 
 #Program converts the value of $t0 into 500
 h_convert_fivehundred:	nop
 addi	$t0 $zero 500
 b	check_h_convert_1
 
 check_h_convert_1:	nop
 beq	$t1 0x49 h_convert_one_2
 beq	$t1 0x56 h_convert_five_2
 beq	$t1 0x58 h_convert_ten_2
 beq	$t1 0x4C h_convert_fifty_2
 beq	$t1 0x43 h_convert_hundred_2
 beq	$t1 0x44 h_convert_fivehundred_2
 
 #Program converts the value of $t1 into 1
 h_convert_one_2:		nop
 addi	$t1 $zero 1
 b	check_h_convert_2
 
 #Program converts the value of $t1 into 5
 h_convert_five_2:	nop
 addi	$t1 $zero 5
 b	check_h_convert_2
 
 #Program converts the value of $t1 into 10
 h_convert_ten_2:		nop
 addi	$t1 $zero 10
 b	check_h_convert_2
 
 #Program converts the value of $t1 into 50
 h_convert_fifty_2:	nop
 addi	$t1 $zero 50
 b	check_h_convert_2
 
 #Program converts the value of $t1 into 100
 h_convert_hundred_2:	nop
 addi	$t1 $zero 100
 b	check_h_convert_2
 
 #Program converts the value of $t1 into 500
 h_convert_fivehundred_2:	nop
 addi	$t1 $zero 500
 b	check_h_convert_2
 
 check_h_convert_2:	nop
 beq	$t2 0x49 h_convert_one_3
 beq	$t2 0x56 h_convert_five_3
 beq	$t2 0x58 h_convert_ten_3
 beq	$t2 0x4C h_convert_fifty_3
 beq	$t2 0x43 h_convert_hundred_3
 beq	$t2 0x44 h_convert_fivehundred_3
 
 #Program converts the value of $t3 into 1
 h_convert_one_3:		nop
 addi	$t2 $zero 1
 b	check_h_convert_3
 
 #Program converts the value of $t3 into 5
 h_convert_five_3:	nop
 addi	$t2 $zero 5
 b	check_h_convert_3
 
 #Program converts the value of $t3 into 10
 h_convert_ten_3:		nop
 addi	$t2 $zero 10
 b	check_h_convert_3
 
 #Program converts the value of $t3 into  50
 h_convert_fifty_3:	nop
 addi	$t2 $zero 50
 b	check_h_convert_3
 
 #Program converts the value of $t3 into 100
 h_convert_hundred_3:	nop
 addi	$t2 $zero 100
 b	check_h_convert_3
 
 #Program converts the value of $t3 into 500
 h_convert_fivehundred_3:	nop
 addi	$t2 $zero 500
 b	check_h_convert_3
 
 #Final checkpoint to see if (i) is valid for H.
 check_h_convert_3:	nop
 blt	$t0 $t1 check_H_cont
 b	updateCheck
 check_H_cont:		nop
 bgt	$t1 $t2 check_H_cont_2
 b	updateCheck
 check_H_cont_2:		nop
 beq	$t0 $t2 invalidArg
 move	$t0 $t3
 b	updateCheck
 
 #Update the loop
 updateCheck:		nop
 addi	$a0 $a0 1				#increments (i) to (i)++
 lb	$t0 ($a0)				#loads (i)++
 addi	$t5, $t5, 1				#increments counter
 addi	$t4, $t4, 1				#increments length of numeral
 beq	$t0, 0x00, clear_test
 bne	$t0, 0x00, checkRomanNumberalBit
 
 #Error Condition
 invalidArg:		nop
 li	$v0 4
 la	$a0 promptInvalidArg
 syscall
 #Prints new line
 li	$v0 4
 la	$a0 promptLine
 syscall
 li	$v0 10
 syscall
 
 #Clear Condition - The input has cleared all test values
 clear_test:		nop
 
 #Clear Register $t6 and $t7 and edit $t5 to fir
 add	$t6 $zero $zero
 add	$t7 $zero $zero
 
 #Load the first byte (i)
 li	$v0 4
 lw	$a0 ($a1) 
 lb	$t0 ($a0)
 
 #Load the second byte (i+1)
 addi	$a0 $a0 1
 lb	$t1 ($a0)
 
 #Loop to convert the Romam Numerals
 romanNumeral_loop:	nop
 beqz	$t5 binary_conversion
 
 #Establish the correct decimal values for (i)
 establish_i:	nop
 add	$t3 $t0 $zero
 beq	$t0 0x00 status_0
 beq	$t0 0x49 status_I
 beq	$t0 0x56 status_V
 beq	$t0 0x58 status_X
 beq	$t0 0x4C status_L
 beq	$t0 0x43 status_C
 beq	$t0 0x44 status_D
 
 status_0:	nop
 addi	$t0, $zero, 0
 b	establish_ii
 
 status_I:	nop
 addi	$t0, $zero, 1
 b	establish_ii

 status_V:	nop
 addi	$t0, $zero, 5
 b	establish_ii
 
 status_X:	nop
 addi	$t0, $zero, 10
 b	establish_ii
 
 status_L:	nop
 addi	$t0, $zero, 50
 b	establish_ii
 
 status_C:	nop
 addi	$t0, $zero, 100
 b	establish_ii
 
 status_D:	nop
 addi	$t0, $zero, 500
 b	establish_ii
 
 #Establish the correct decimal values for (i+1)
 establish_ii:	nop
 add	$t8 $t1 $zero
 beq	$t1 0x00 status_0_ii
 beq	$t1 0x49 status_I_ii
 beq	$t1 0x56 status_V_ii
 beq	$t1 0x58 status_X_ii
 beq	$t1 0x4C status_L_ii
 beq	$t1 0x43 status_C_ii
 beq	$t1 0x44 status_D_ii
 
 status_0_ii:	nop
 addi	$t1, $zero, 0
 b	loop_comparison
 
 status_I_ii:	nop
 addi	$t1, $zero, 1
 b	loop_comparison

 status_V_ii:	nop
 addi	$t1, $zero, 5
 b	loop_comparison
 
 status_X_ii:	nop
 addi	$t1, $zero, 10
 b	loop_comparison
 
 status_L_ii:	nop
 addi	$t1, $zero, 50
 b	loop_comparison
 
 status_C_ii:	nop
 addi	$t1, $zero, 100
 b	loop_comparison
 
 status_D_ii:	nop
 addi	$t1, $zero, 500
 b	loop_comparison
 
 #Loop begins						
 loop_comparison:	nop
 bge	$t0 $t1 add_check
 blt	$t0 $t1 sub_check

 add_check:		nop
 beqz	$t1 pairing
 
 #Load (i+2) into $t2
 addi	$a0 $a0 1
 lb	$t2 ($a0)
 subi	$a0 $a0 1
  
 #Check for pairing and see if (i) and (i+1) are valid to be subtracted from
 pairing:		nop
 beq	$t1 1 	check_one		# I can only be placed before V [5|56]  and X [10|58]
 beq	$t1 10	check_ten		# X can only be placed before L [50|4C] and C [100|43]
 beq	$t1 100	check_hundred		# C can only be placed before D	 [500|44]
 b	check_any
 
 check_one:		nop		#check_one
 beq	$t2 0x56 tree_V
 beq	$t2 0x58 tree_X
 b	check_any
 
 tree_V:		nop
 add	$t9 $t9 1 	#Tree Counter
 addi	$t2 $zero 5
 sub	$t6 $t2 $t1
 add	$t6 $t6 $t0
 add	$t7 $t7 $t6
 subi	$t5 $t5 1	#Testing
 addi	$a0 $a0 1	#Testing
 b	tree_cont
 
 tree_X:		nop
 add	$t9 $t9 1 	#Tree Counter
 addi	$t2 $zero 10
 sub	$t6 $t2 $t1
 bgt	$t9 1 skippp
 add	$t6 $t6 $t0
 skippp:	nop
 add	$t7 $t7 $t6
 subi	$t5 $t5 1	#Added works for CIX
 add	$a0 $a0 1	#Added works for CIX
 b	tree_cont
 
 check_ten:		nop
 beq	$t2 0x4C tree_L
 beq	$t2 0x43 tree_C
 b	check_any
 
 tree_L:		nop
 add	$t9 $t9 1 	#Tree Counter
 addi	$t2 $zero 50
 sub	$t6 $t2 $t1
 bgt	$t9 1 skipp
 add	$t6 $t6 $t0
 skipp:	nop
 add	$t7 $t7 $t6
 subi	$t5 $t5 1	#Testing
 addi	$a0 $a0 1	#Testing
 b	tree_cont
 
 tree_C:		nop
 add	$t9 $t9 1 	#Tree Counter
 addi	$t2 $zero 100
 sub	$t6 $t2 $t1
 bgt	$t9 1 skipppp
 add	$t6 $t6 $t0
 skipppp:	nop
 add	$t7 $t7 $t6
 subi	$t5 $t5 1	#Testing
 addi	$a0 $a0 1	#Testing
 b	tree_cont
 
 check_hundred:		nop		#check_hundred
 beq	$t2 0x44 tree_D
 b	check_any
 
 tree_D:		nop
 add	$t9 $t9 1 	#Tree Counter
 addi	$t2 $zero 500
 sub	$t6 $t2 $t1
 bgt	$t9 1 skip
 add	$t6 $t6 $t0
 skip:	nop
 add	$t7 $t7 $t6
 subi	$t5 $t5 1	#Testing
 addi	$a0 $a0 1	#Testing
 b	tree_cont
 
 check_any:		nop
 add	$t6 $zero $t0
 add	$t7 $t7 $t6
 lb	$t0 ($a0)
 beqz	$t0 tree_cont	
 addi 	$a0 $a0 1
 lb	$t1 ($a0)
 bgt	$t9 1 romanNumeral_loop
 b	tree_cont
 
 tree_cont:		nop
 subi	$t5 $t5 1
 bgt	$t9 1, tree_branch
 b	romanNumeral_loop
 
 tree_branch:		nop	#test #3
 addi	$a0 $a0 1
 lb	$t0 ($a0)
 beqz	$t0 romanNumeral_loop
 addi	$a0 $a0 1
 lb	$t1 ($a0)
 b	romanNumeral_loop
 
 sub_check:		nop
 bgtz	$t7 active_sum
 b	sub_check_cont
 
 active_sum:		nop
 sub	$t7 $t7 $t0

 sub_check_cont:	nop
 sub	$t6 $t1 $t0
 add	$t7 $t7 $t6
 add	$a0 $a0 1
 lb	$t0 ($a0)
 b	tree_cont
 
 #Final Condition - The program has finised calculating the Roman Numeral to hex.
 binary_conversion:	nop
 li	$v0 4
 la	$a0 promptBinaryRep
 syscall
 li	$v0 4
 la	$a0 promptBinary
 syscall
 move	$s0 $t7
 
 ########################################################################################
 # 
 #	Psuedocode:	This part of the program will run through the Roman Numeral and
 #			convert it into decimal and also binary. In order to do this the
 #			program has stored 2 copies of the Roman Numeral. The first copy
 #			will be used to convert the value into binary and in doing so, the program
 #        	    	will print out the binary values. The second copy is used to
 #                 	print the values out in decimal via a loop that utilizes the concept
 #			of base 10 digit places.
 #
 #    Register Use:	$t0	- 	copy of the Roman Numeral input in hex				
 #    (binary)		$t1	- 	length of the Roman Numeral input							
 #			$t2	-	loads the max bit of 2^14 = 16384
 #			$t3	-	loads the max count for the case of 2^0 to 2^7
 #			$t4	-	loads the min count for the case of 2^7 to 2&14
 #			$t5	-	Zero counter used to make sure an extra 0 is added
 #			$t6	-	counter load with 16. Uses this in order to countdown the bits
 #					in the binary valu
 #			$t7	-	clear
 #			$t8	-	clear
 #			$t9	-	clear
 #
 #
 #    Register Use:
 #    (decimal)		#t0	-	copy of the Roman Numeral input in hex
 #			#t1	-	1000000					#clear?
 #			$t2	-	100000					#clear?
 #			$t3	-	10000					#clear?
 #			$t4	-	1000					#clear?
 #			$t5	-	100
 #			$t6	-	10
 #			$t7	-	1
 #			$t8	-	decimal conversion
 #			$t9	-	subtraction counter
 #
 ########################################################################################
 
 #Clear register and set them up for the next subprogram that follows
 printBinary:	nop
 addi	$t3 $zero 0
 addi	$t6 $zero 0
 move	$t0 $t7
 move	$t1 $t4
 addi	$t7 $zero 0
 addi	$t4 $zero 0
 addi	$t2 $zero 16384
 addi	$t6 $zero 16		
 
 #Loop that prints the binary value
 displayBinary_loop:	nop
 beqz	$t6 convert_decimal_setup
 beqz	$t0 special
 bge	$t0 $t2 print1
 blt	$t0 $t2 print0
 
 #Conditions for printing a 1
 print1:	nop
 addi	$t5 $t5 1
 sub	$t0 $t0 $t2
 beqz	$t0 extra
 
 #Conditions for printing an extra space
 extra_cont:	nop
 div	$t2 $t2 2
 li	$v0 4
 la	$a0 one
 syscall
 subi	$t6 $t6 1
 b	displayBinary_loop
 
 #Conditions for printing a 0
 print0:	nop
 div	$t2 $t2 2
 beqz	$t5 skip_print0
 li	$v0 4
 la	$a0 zero
 syscall
 skip_print0:	nop
 subi	$t6 $t6 1
 b	displayBinary_loop
 
 #Special Condition for printing 1
 special:	nop		
 li	$v0 4
 la	$a0 zero
 syscall
 subi	$t6 $t6 1
 beqz	$t6 convert_decimal_setup
 b	special
 
 #Special conditions for decrementing the loop
 extra:		nop
 subi	$t6 $t6 1
 b	extra_cont
 
 #Converts the Roman Numeral value to decimal
 convert_decimal_setup:	nop
 addi	$t0 $s0 0
 li	$t1 10000000
 li	$t2 1000000
 li	$t3 100000
 li	$t4 1000
 li	$t5 100
 li	$t6 10
 li	$t7 1
 li	$t8 0
 
 #Condtions that are use to check what type of digit
 #place the program should do subtraction on
 convert_decimal:	nop
 beqz	$t0		save
 bge	$t0 1000000 	million
 bge	$t0 100000 	hundred_thousands
 bge	$t0 10000 	ten_thousands
 bge	$t0 1000 	thousands
 bge	$t0 100	 	hundreds
 bge	$t0 10  	tens
 bge	$t0 1	 	ones
 
 #Conditions for a millionth
 million:		nop
 sub	$t0 $t0 $t1
 add	$t8 $t8 1
 blt	$t0 $t1 shift
 b	convert_decimal
  
 #Conditions for a hundred thousandth 
 hundred_thousands:	nop
 sub	$t0 $t0 $t2
 add	$t8 $t8 1
 blt	$t0 $t2 shift
 b	convert_decimal
 
 #Conditions for a ten thousandth 
 ten_thousands:		nop	
 sub	$t0 $t0 $t3
 add	$t8 $t8 1
 blt	$t0 $t3 shift
 b	convert_decimal
 
 #Conditions for a thousandth
 thousands:		nop		
 sub	$t0 $t0 $t4			
 add	$t8 $t8 1
 blt	$t0 $t6 extra_b
 b	b_continue
 extra_b:		nop
 sll	$t8 $t8 4
 b_continue:		nop 
 blt	$t0 $t4 shift
 b	convert_decimal
 
 #Conditions for a hundred 
 hundreds:		nop
 sub	$t0 $t0 $t5
 add	$t8 $t8 1
 blt	$t0 $t6 extra_a
 b	a_continue
 extra_a:		nop
 sll	$t8 $t8 4
 blt	$t0 $t7 extra_extra_a
 b	a_continue
 extra_extra_a:		nop
 sll	$t8 $t8 4
 a_continue:		nop 
 blt	$t0 $t5 shift
 b	convert_decimal

 #Conditions for a tenth 
 tens:			nop
 sub	$t0 $t0 $t6
 add	$t8 $t8 1
 blt	$t0 $t7 extra_c
 b	c_continue	
 extra_c:		nop
 sll	$t8 $t8 4
 c_continue:		nop
 blt	$t0 $t6 shift
 b	convert_decimal

 #Conditions for a oneth   
 ones:			nop
 sub	$t0 $t0 $t7
 add	$t8 $t8 1
 blt	$t0 $t7 shift
 b	convert_decimal
  
 #Conditions to save shift the decimal to the next
 #digit place 
 shift:			nop
 sll	$t8 $t8 4	
 b	convert_decimal
 
 #Operation to save the final answer in $s0
 save:			nop
 srl	$t8 $t8 4
 move	$s0 $t8
 
 #Prints new line
 li	$v0 4
 la	$a0 promptLine
 syscall
 
 #Ends Program
 li	$v0 10
 syscall
