# 	ECE 2500
#	Functions	
#
#	main() calls a function mul3(a,b,c) 

# Start of the text segment:
	.text		
main:	
	# initialize three numbers to be multiplied
	# we use $a0, $a1, $a2 to pass function arguments to mul3()
	addi $a0, $zero, 2
	addi $a1, $zero, 3
	addi $a2, $zero, 4

	# now that the input is ready, jump to mul3()
	# jal will ensure that $ra is updated with the address
	# of the instruction after jal, where mul3() will return
	jal MUL3 	# call MUL3()

	# mul3() stores the result in $v0
	# copy it in some other register 
	add $s0, $zero, $v0

	# viola! we are done! return back!
	li $v0, 10
	syscall			# exit the program via system call

#end of main

MUL3:
	# the caller passes the three input arguments
	# in $a0, $a1, and $a2 registers

	mul $t0, $a0, $a1	# in MUL3()
	mul $t0, $t0, $a2

	# prepare the output in $v0 for the caller
	add $v0, $zero, $t0

	# the return address in main is stored in $ra
	jr $ra

#end of add

#end of program
