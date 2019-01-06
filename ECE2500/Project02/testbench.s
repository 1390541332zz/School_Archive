main:
    li $a0, 12
    li $a1, 780
    move $s0, $ra
    jal  binaryGCD
    move $s1, $v0
    move $ra, $s0
    li $a0, 780
    li $a1, 12
    move $s0, $ra
    jal  binaryGCD
    move $s2, $v0
    move $ra, $s0
    li $a0, 2048
    li $a1, 16384
    move $s0, $ra
    jal  binaryGCD
    move $s3, $v0
    move $ra, $s0
    li $a0, 500005199
    li $a1, 709
    move $s0, $ra
    jal  binaryGCD
    move $s4, $v0
    move $ra, $s0
    li $a0, 554400
    li $a1, 655200
    move $s0, $ra
    jal  binaryGCD
    move $s5, $v0
    move $ra, $s0
    li $a0, 1048576
    li $a1, 131072
    move $s0, $ra
    jal  binaryGCD
    move $s6, $v0
    move $ra, $s0
    li $a0, 0
    li $a1, 12345
    move $s0, $ra
    jal  binaryGCD
    move $s7, $v0
    move $ra, $s0
    ori  $v0, $zero, 10
    syscall
# u = $a0, v = $a1, ret = $v0
# beq, bne, andi, or, addi, srl, sll, slt, sub
binaryGCD:
    addi $v0, $a1, 0
    beq  $a0, $zero, bGCD_e
    addi $v0, $a0, 0
    beq  $a1, $zero, bGCD_e
    # u_mut = $t0, v_mut = $t1, shift = $t2
    addi $t0, $a0, 0
    addi $t1, $a1, 0
    addi $t2, $zero, 0
bGCD_for:
    # cond = $t3
    or   $t3, $t0, $t1
    andi $t3, $t3, 1
    bne  $t3, $zero, bGCD_for_e
    srl  $t0, $t0, 1 
    srl  $t1, $t1, 1
    addi $t2, $t2, 1
    beq  $zero, $zero, bGCD_for
bGCD_for_e:
bGCD_while0:
    # cond = $t3
    andi $t3, $t0, 1
    bne  $t0, $zero, bGCD_while0_e
    srl  $t0, $t0, 1
    beq  $zero, $zero, bGCD_while0
bGCD_while0_e:
bGCD_do:
bGCD_while1:
    # cond = $t3
    andi $t3, $t1, 1
    bne  $t3, $zero, bGCD_while1_e
    srl  $t1, $t1, 1
    beq  $zero, $zero, bGCD_while1
bGCD_while1_e:
    # cond = $t3
    slt  $t3, $t1, $t0
    beq  $t3, $zero, bGCD_if_e
    #swap = $t4
    addi $t4, $t0, 0
    addi $t0, $t1, 0
    addi $t1, $t4, 0
bGCD_if_e:
    sub  $t1, $t1, $t0
    bne  $t1, $zero, bGCD_do
#bGCD_do_e:
bGCD_sll:
    beq  $t2, $zero, bGCD_sll_e
    sll  $t0, $t0, 1
    addi $t2, $t2, -1
    beq  $zero, $zero, bGCD_sll
bGCD_sll_e:
    addi $v0, $t0, 0
bGCD_e:
    jr $ra
