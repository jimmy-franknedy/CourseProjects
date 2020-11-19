#-------------------------------------------------------------------------
# Created by:  Franknedy, Jimmy
#              jfrankne
#              06 June 2019
#
# Assignment:  Lab 5: A Gambling Game
#              CMPE 012, Computer Systems and Assembly Language
#              UC Santa Cruz, Spring 2019
# 
# Description: ---
# 
# Notes:       ---
#-------------------------------------------------------------------------

jal end_game                       # this is to prevent the rest of
                                   # the code executing unexpectedly

#--------------------------------------------------------------------
# play_game
#
# This is the highest level subroutine.
#
# arguments:  $a0 - starting score
#             $a1 - address of array index 0 
#
# return:     n/a
#--------------------------------------------------------------------

.text
play_game: nop
 li	$t0 0
 li	$t1 0
 li	$t2 0
 li	$t3 0
 li	$t4 0
 li	$t5 0
 li	$t6 0
 li	$t7 0
 li	$t8 0
 li	$t9 0
 
    move $a0 $a1
    jal   get_array_size
    
    jal   welcome
    
    jal   prompt_options
    
    jal   take_turn
    
    jal   end_game
    
    jr    $ra

#--------------------------------------------------------------------
# welcome (given)
#
# Prints welcome message indicating valid indices.
# Do not modify this subroutine.
#
# arguments:  $a0 - array size in words
#
# return:     n/a
#--------------------------------------------------------------------
#
# REGISTER USE
# $t0: array size
# $a0: syscalls
# $v0: syscalls
#--------------------------------------------------------------------

.data
welcome_msg: .ascii "------------------------------"
             .ascii "\nWELCOME"
             .ascii "\n------------------------------"
             .ascii "\n\nIn this game, you will guess the index of the maximum value in an array."
             .asciiz "\nValid indices for this array are 0 - "

end_of_msg:  .asciiz ".\n\n"
             
.text
welcome: nop

    add   $t0  $zero  $a0         # save address of array

    addiu $v0  $zero  4           # print welcome message
    la    $a0  welcome_msg
    syscall
    
    addiu $v0  $zero  1           # print max array index
    sub   $a0  $t0    1
    syscall

    addiu $v0  $zero  4           # print period
    la    $a0  end_of_msg
    syscall
    
    jr $ra
    
#--------------------------------------------------------------------
# prompt_options (given)
#
# Prints user options to screen.
# Do not modify this subroutine. No error handling is required.
# 
# return:     $v0 - user selection
#--------------------------------------------------------------------
#
# REGISTER USE
# $v0, $a0: syscalls
# $t0:      temporarily save user input
#--------------------------------------------------------------------

.data
turn_options: .ascii  "------------------------------" 
              .ascii  "\nWhat would you like to do? Select a number 1 - 3"
              .ascii  "\n"
              .ascii  "\n1 - Make a bet"
              .ascii  "\n2 - Cheat! Show me the array"
              .asciiz "\n3 - Quit before I lose everything\n\n"
.text
prompt_options: nop

    addiu $v0  $zero  4           # print prompts
    la    $a0  turn_options       
    syscall

    addiu $v0  $zero  5           # get user input
    syscall
    
    add   $t0  $zero  $v0         # temporarily saves user input to $t0
    
    addiu $v0  $zero  11
    addiu $a0  $zero  0xA         # print blank line
    syscall

    add   $v0  $zero  $t0         # return player selection
    jr    $ra

#--------------------------------------------------------------------
# take_turn	
#
# All actions taken in one turn are executed from take_turn.
#
# This subroutine calls one of following sub-routines based on the
# player's selection:
#
# 1. make_bet
# 2. print_array
# 3. end_game
#
# After the appropriate option is executed, this subroutine will also
# check for conditions that will lead to winning or losing the game
# with the nested subroutine win_or_lose.
# 
# arguments:  $a0 - current score
#             $a1 - address of array index 0 
#             $a2 - size of array (this argument is optional)
#             $a3 - user selection from prompt_options
#
# return:     $v0 - updated score
#--------------------------------------------------------------------
#
# REGISTER USE
# 
#--------------------------------------------------------------------

.text
take_turn: nop

    subi   $sp   $sp  4		# push return addres to stack
    sw     $ra  ($sp)
    
    beq		$a3 1	prompt_make_bet
    beq		$a3 2	prompt_print_array
    beq		$a3 3	prompt_end_game
    
    prompt_make_bet:	nop

    # argument:		$a0 - current score
    #			$a1 - address of array index 0
    
    jal    	make_bet
    
    # argument:		$a0 - address of array index 0
    #			$a1 - index of maximum value in array
    move	$a0 $t9
    move	$a1 $t8
    
    jal  	win_or_lose
    
    lw	  $ra  ($sp)		 
    addi  $sp   $sp   4		# pop return address
    jr		$ra
    
    prompt_print_array:	nop
    
    # argument:		$a0 - address of array index 0
    move	$a0 $a1
    
    jal    	print_array
    
    lw	  $ra  ($sp)		 
    addi  $sp   $sp   4		# pop return address
    jr		$ra
    
    prompt_end_game:	nop
    jal		end_game

#--------------------------------------------------------------------
# make_bet
#
# Called from take_turn.
#
# Performs the following tasks:
#
# 1. Player is prompted for their bet along with their index guess.
# 2. Max value in array and index of max value is determined.
#    (find_max subroutine is called)
# 3. Player guess is compared to correct index.
# 4. Score is modified
# 5. If player guesses correctly, max value in array is either:
#    --> no extra credit: replaced by -1
#    --> extra credit:    removed from array
#  
# arguments:  $a0 - current score of user
#             $a1 - address of first element in array
#
# return:     $v0 - updated score
#--------------------------------------------------------------------
#
# REGISTER USE
# 
#--------------------------------------------------------------------


.data
bet_header:   .ascii  "------------------------------"
              .asciiz "\nMAKE A BET\n\n"
            
score_header: .ascii  "------------------------------"
              .asciiz "\nCURRENT SCORE\n\n"
                   
 promptZ:	.asciiz	"\n"
 promptA:	.asciiz "You currently have "
 promptA2:	.asciiz	" points.\n"
 promptC:	.asciiz "How many points would you like to bet? "
 promptD:	.asciiz "Valid indices for this array are 0 - "
 promptF:	.asciiz "Sorry, your bet exceeds your current worth.\n"
 promptG:	.asciiz "Which index do you believe contains the maximum value? "
 promptH:	.asciiz	"Your guess is incorrect! The maximum value is not in index "
 promptI:	.asciiz "You lost "
 promptI2:	.asciiz " points."
 promptJ:	.asciiz "Score! Index "
 promptJ2:	.asciiz " has the maximum value in the array.\n\n"
 promptJ3:	.asciiz "You earned "
 promptJ4:	.asciiz " points!\n"
 promptJ5:	.asciiz "This value has been removed from the array"

.text
make_bet: nop       
    
    subi   $sp   $sp  4		#Push the $ra
    sw     $ra  ($sp)
    
    move	$t9 $a1
    move	$t8 $a0
    
    addiu  $v0  $zero  4        # print header
    la     $a0  bet_header
    syscall
    
    move	$a1 $t9			# $t9 = address of index 0
    move	$a0 $t8			# $t8 = score
    move	$t7 $t7 		# $t6 = length of array
    
    # argument:		$a0 - current score
    #			$a1 - address of array index 0
    #			$a2 - size of array
    
    move	$a0 $t8
    move	$a1 $t9
    move	$a2 $t7
    
    jal		prompt_bet
    
    # argument:		$a0 - address of array index 0
    move	$a0 $t9
    jal		find_max
    
    # argument:		$a0 - player index guess
    #			$a1 - index of max element in the array
    move	$a0 $t6
    move	$a1 $t5
    jal		compare
    
    # argument:		$a0 - current score
    #			$a1 - player bet
    #			$a2 - boolean value from comparison
    move	$a0 $t8
    move	$a1 $t6
    move	$a2 $t4
    jal		mod_score
    
    # argument:		$a0 - address of array index 0
    #			$a1 - index of max element in array 
    #			$a2 - boolean value from comparison
    move	$a0 $t9
    move	$a1 $t5
    move	$a2 $t4
    jal		mod_array
    
    #return the update score to $v0
    
    lw     $ra  ($sp)			#Pop $ra
    addi   $sp   $sp  4
    
    jr     $ra


#--------------------------------------------------------------------
# find_max
#
# Finds max element in array, returns index of the max value.
# Called from make_bet.
# 
# arguments:  $a0 - address of first element in array
#
# returns:    $v0 - index of the maximum element in the array
#             $v1 - value of the maximum element in the array
#--------------------------------------------------------------------
#
# REGISTER USE
# 
#--------------------------------------------------------------------

.text
 find_max: nop
 li	$t0 0
 li	$t1 0
 li	$t2 0
 li	$t7 0
 
 find_max_loop:	nop

 lw	$t0 ($a0)		#Loads the first value in the array
 beqz	$t0 find_max_exit	#If (i) is null the program exits
 bgt 	$t0 $t1 new_max		#Conditions if program encounters max
 ble	$t0 $t1 no_max		#Conditions if program encounters less than or equal to value
 
 new_max:	nop		#Max Condition
 move	$t1 $t0			#Set the "max" value to $t1
 move	$t3 $t2			#Set the index of the "max" to $t3
 
 no_max:	nop
 addi	$t2 $t2 1		#Increment to the next index (1)
 addi	$a0 $a0 4		#Increment to the next element in array (4)
 addi	$t7 $t7 1		#Increment length
 b	find_max_loop		#Return to loop
 
 find_max_exit:	nop		#Final Conditions before the program exits
 move	$v0 $t3			#Moves the index of max value to $v0
 move	$t5 $t3
 move	$v1 $t1			#Moves the element of the max value to $v1
 
 jr     $ra

#--------------------------------------------------------------------
# win_or_lose
#
# After turn is taken, checks to see if win or lose conditions
# have been met
# 
# arguments:  $a0 - address of the first element in array
#             $a1 - updated score
#
# return:     n/a
#--------------------------------------------------------------------
#
# REGISTER USE
# 
#--------------------------------------------------------------------

.data
win_msg:  .ascii   "------------------------------"
          .asciiz  "\nYOU'VE WON! HOORAY! :D\n\n"

lose_msg: .ascii   "------------------------------"
          .asciiz  "\nYOU'VE LOST! D:\n\n"

.text
win_or_lose: nop

blez	$t8 end_game

win_or_lose_loop:	nop
    lw   $t0($a0)
    beqz $t0 win_cond
    bne	  $t0 -1, not_win
    addi  $a0 $a0 4
    j	win_or_lose_loop
    
win_cond:		nop
    addiu  $v0  $zero  4
    la     $a0  win_msg
    syscall
    jal		end_game
    
    addiu  $v0  $zero  4
    la     $a0  lose_msg
    syscall
    jal		end_game
    
not_win:		nop
    jr     $ra

#--------------------------------------------------------------------
# print_array
#
# Print the array to the screen. Called from take_turn
# 
# arguments:  $a0 - address of the first element in array
#--------------------------------------------------------------------
#
# REGISTER USE
# $a0: syscalls
# $v0: syscalls
#--------------------------------------------------------------------

.data
cheat_header: .ascii  "------------------------------"
              .asciiz "\nCHEATER!\n\n"

.text
print_array: nop
    move	$t9 $a0		    # move $a0 to $t9 so program can print safely
    
    addiu  $v0  $zero  4           # print header
    la     $a0  cheat_header
    syscall
   
    move	$a0 $t9		    # move $t9 $a0 so program has address again
    addi	$t1 $zero 0
    
    print_array_loop:	nop
    lw		$t0 ($a0)
    beqz	$t0 print_array_loop_exit
   
    move	$t9 $a0			# save value of address
    
    li		$v0 1			# print the index
    la		$a0 ($t1)
    syscall
    
    li		$v0 11			# print semicolon
    la		$a0 0x3A
    syscall
    
    li		$v0 11 			# print space
    la		$a0 0x20
    syscall
    
    li		$v0 1			# print the value at the index (i)
    la		$a0 ($t0)
    syscall
    
    li		$v0 4			# print new line
    la		$a0 promptZ
    syscall
    
    move	$a0 $t9			# return the address value
    
    addi	$a0 $a0 4		# increment to the next (i) value
    addi	$t1 $t1 1
    j		print_array_loop
    
    print_array_loop_exit:	nop
    li		$v0 4			# print new line
    la		$a0 promptZ
    syscall
    
    jr     $ra

#--------------------------------------------------------------------
# end_game (given)
#
# Exits the game. Invoked by user selection or if the player wins or
# loses.
#
# arguments:  $a0 - current score
#
# returns:    n/a
#--------------------------------------------------------------------
#
# REGISTER USE
# $a0: syscalls
# $v0: syscalls
#--------------------------------------------------------------------

.data
game_over_header: .ascii  "------------------------------"
                  .ascii  " GAME OVER"
                  .asciiz " ------------------------------"
.text
end_game: nop

    add   $s0  $zero  $a0              # save final score

    addiu $v0  $zero  4                # print game over header
    la    $a0  game_over_header
    syscall
    
    addiu $v0  $zero  11               # print new line
    addiu $a0  $zero  0xA
    syscall
    
    addiu $v0  $zero  10               # exit program cleanly
    syscall
    
#--------------------------------------------------------------------
# get_array_size (optional)
# 
# Determines number of 1-word elements in array.
#
# argument:   $a0 - address of array index 0
#
# returns:    $v0 - number of 1-word elements in array
#--------------------------------------------------------------------
 get_array_size:		nop
 lw	$t0 ($a0)
 
 get_array_size_loop:		nop
 beqz	$t0 continue_get_array_size	#Checks to see if the current (i) is a 0
 addi	$t1 $t1 1			#Adds 1 to the total counter in order to get the length the array
 addi	$a0 $a0 4			#Increments to the next (i+1) position in the array
 lw	$t0 ($a0)			#Loads the next byte into $t0 
 b	get_array_size_loop
 
 continue_get_array_size:	nop
 move	$t7 $t1		#Move the length of the size of the array to $t7
 move	$v0 $t1		#Move the length of the array into $v0 
 jr	$ra	
 
#--------------------------------------------------------------------
# prompt_bet (optional)
#
# Prompts user for bet amount and index guess. Called from make_bet.
# 
# arguments:  $a0 - current score
#             $a1 - address of array index 0
#             $a2 - array size in words
#
# returns:    $v0 - user bet
#             $v1 - user index guess
#--------------------------------------------------------------------
 prompt_bet:	nop
 
 move	$t8 $a0			#Save $t8
 
 prompt_bet_start:	nop
 li		$v0 4			#Prints "You currently have "
 la		$a0 promptA
 syscall
 
 li		$v0 1			#User points
 la		$a0 ($t8)
 syscall
    
 li		$v0 4			#Prints " points.\n"
 la		$a0 promptA2
 syscall
  
 li		$v0 4			#Prints out "How many points would you like to bet? "
 la		$a0 promptC		
 syscall
   
 li		$v0 5			#Program will read the number and store it in $v0
 la		$a0 promptC		
 syscall
 
 move		$t6 $v0			#Saves the value of the user's bet to $t6
 
 li		$v0 4			#Prints new line
 la		$a0 promptZ
 syscall
 
 
 ble		$t6 $t8 valid_bet
 bgt		$t6 $t8 invalid_bet
 
 valid_bet:		nop		#Condition of the bet value is valid
 
 li		$v0 4			#Prints out "Valid indices for this array are 0 - "
 la		$a0 promptD
 syscall
 
 li		$v0 1			#Prints the max length of index
 la		$a0 ($t7)
 syscall
 
 li		$v0 11			#Prints period
 la		$a0 0x2E
 syscall	
    
 li		$v0 4			#Prints a new line
 la		$a0 promptZ
 syscall		
    
 li		$v0 4			#Prints out "Which index do you believe contains the maximum value? "
 la		$a0 promptG		
 syscall
 
 li		$v0 5			#Prompts the user to input their guess of the array index  
 la		$a0 promptG		
 syscall
    
 move	$v1 $v0				#Moves the user's guess to $v1
 move	$t0 $v0				#Moves the user's gues to $t0
 
 jr	$ra
  
 invalid_bet:	nop			#Condition of the bet value is vinalid
 li		$v0 4			#Prints out "Sorry, your bet exceeds your current worth.\n"
 la		$a0 promptF
 syscall
 
 li		$v0 4
 la		$a0 promptZ
 syscall
 
 j		prompt_bet_start	#Program returns to the beginning of the open prompt
 
#--------------------------------------------------------------------
# compare (optional)
#
# Compares user guess with index of largest element in array. Called
# from make_bet.
#
# arguments:  $a0 - player index guess
#             $a1 - index of the maximum element in the array
#
# return:     $v0 - 1 = correct guess, 0 = incorrect guess
#--------------------------------------------------------------------
 compare:	nop
 beq		$a0 $a1 correct_guess
 bne		$a0 $a1 incorrect_guess
 
 correct_guess:		nop
 li		$v0 1
 j		compare_finish
 
 incorrect_guess:	nop
 li		$v0 0
 
 compare_finish:	nop
 move		$t4 $v0
 jr		$ra

#--------------------------------------------------------------------
# mod_score (optional)
#
# Modifies score based on outcome of comparison between user guess
# correct answer. Returns score += bet for correct guess. Returns
# score -= bet for incorrect guess. Called from make_bet.
# 
# arguments:  $a0 - current score
#             $a1 - player's bet
#             $a2 - boolean value from comparison
#
# return:     $v0 - updated score
#--------------------------------------------------------------------
 mod_score:	nop
 beq		$a2 1 true_guess
 bne		$a2 1 false_guess
 
 true_guess:	nop			# C O R R E C T G U E S S = T R U E
 
 li		$v0 4			#Prints out "Score! Index "
 la		$a0 promptJ
 syscall
   		
 li		$v0 1			#Prints out max index
 la		$a0 ($t5)
 syscall
    
 li		$v0 4			#Prints out prompt " has the maximum value in the array.\n\n"
 la		$a0 promptJ2
 syscall
    
 li		$v0 4			#Prints out "You earned "
 la		$a0 promptJ3
 syscall
 
 li		$v0 1			#Prints out bet value
 la		$a0 ($t6)   
 syscall
    
 li		$v0 4			#Prints out " points!\n"
 la		$a0 promptJ4
 syscall
 
 #Update Current Score			#Adds Score
 add		$t8 $t8 $6
 move		$v0 $t8
 jr		$ra
 
 false_guess:	nop			# I N C O R R E C T G U E S S = F A L S E 
    
 li		$v0 4			#Prints out "Your guess is incorrect! The maximum value is not in index "
 la		$a0 promptH
 syscall
    
 li		$v0 1			#Prints out the user's guess index input
 la		$a0 ($t0)
 syscall
    	
 li		$v0 4			#Prints a new line
 la		$a0 promptZ
 syscall
   
 li		$v0 4			#Prints out "You lost "
 la		$a0 promptI
 syscall
    
 li		$v0 1			#Prints the bet_value because that's what the user gambled upon
 la		$a0 ($t6)		#and ultimately that's what is going to be subtracted from the current score
 syscall
    
 li		$v0 4			#Prints " points."
 la		$a0 promptI2
 syscall
 
 sub		$t8 $t8 $t6		#Subracts Score
 move		$v0 $t8
 jr		$ra

#--------------------------------------------------------------------
# mod_array (optional)
#
# Replaces largest element in array with -1 if player guessed correctly.
# Called from make_bet.
#
# If extra credit implemented, the largest element in the array is
# removed and array shrinks by 1 element. Index of largest element
# is replaced by another element in the array.
# 
# arguments:  $a0 - address of array index 0
#             $a1 - index of the maximum element in the array
#	      $a2 - boolean value from comparison 		
#
# return:     n/a
#--------------------------------------------------------------------
 mod_array:	nop
 
 beq	$a2 1 mod_array_true
 jr	$ra
 
 mod_array_true:	nop
 add	$a0 $a0 $a1		#Go to the index of the max value
 lw	$a0 -1			#Load a -1 into it
 jr	$ra			# jr $ra out