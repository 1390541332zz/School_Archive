# u = $t0, v = $t1, ret = $t9 = end($t0)
# beq, bne, andi, or, addi, srl, sll, slt, sub
main:
binaryGCD:
    addi $t0, $zero, 12
    addi $t1, $zero, 780
    addi $t9, $t1, 0
    beq  $t0, $zero, bGCD_e
    addi $t9, $t0, 0
    beq  $t1, $zero, bGCD_e
    # shift = $t2
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
bGCD_e:
    addi $t0, $t9, 0
done:
    beq $t0, $t0, done
