# 	ECE 2500
#	Functions	
#
#	main() calls a function mul6(a,b,c,d,e,f) 

# Start of the text segment:
	.text		
main:	
	# initialize six numbers to be multiplied
	addi $t0, $zero, 2
	addi $t1, $zero, 3
	addi $t2, $zero, 4
	addi $t3, $zero, 5
	addi $t4, $zero, 6
	addi $t5, $zero, 7

    addi $sp, $sp, -24 #Alloc 6 Blocks
    sw   $t0,  20($sp)
    sw   $t1,  16($sp)
    sw   $t2,  12($sp)
    sw   $t3,   8($sp)
    sw   $t4,   4($sp)
    sw   $t5,   0($sp)

	jal MUL6 	# call MUL3()
    addi $sp, $sp, 24 #Dealloc 6 Blocks

	# mul6() stores the result in $v0
	# copy it in some other register 
	add $s0, $zero, $v0

	li $v0, 10
	syscall			# exit the program via system call

#end of main

MUL6:
    sw   $t0, 20($sp)
    sw   $t1, 16($sp)
    sw   $t2, 12($sp)
    sw   $t3,  8($sp)
    sw   $t4,  4($sp)
    sw   $t5,  0($sp)

	mul $t0, $t0, $t1	# in MUL3()
	mul $t0, $t0, $t2
	mul $t0, $t0, $t3
	mul $t0, $t0, $t4
	mul $t0, $t0, $t5

	# prepare the output in $v0 for the caller
	add $v0, $zero, $t0

	# the return address in main is stored in $ra
	jr $ra

#end of add

#end of program
