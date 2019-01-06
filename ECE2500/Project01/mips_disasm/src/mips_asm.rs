// MIPS 1.0 Assembly Internal Representation

struct asm {
    //The rest of the data sections pending
    instructions: Vec<instr>,
    labels: HashMap<String, isize>,
};

struct instr_r {
    rs: reg,
    rt: reg,
    rd: reg,
    sh: u8,
};

struct instr_i_s {
    rs: reg,
    rt: reg,
    imm: i16,
};

struct instr_i_u {
    rs: reg,
    rt: reg,
    imm: u16,
};

struct instr_j {
    addr: i32,
};

enum instr {
    op_r(op_r),
    op_r_s(op_r_s),
    op_j(op_j),
    op_j_r(op_j_r),
    op_i_s(op_i_s),
    op_i_u(op_i_u),
    syscall(instr_r),
    nop
}

enum op_r {
        add(instr_r  ),
        sub(instr_r  ),
       addu(instr_r  ),
       subu(instr_r  ),
       mult(instr_r  ),
        div(instr_r  ),
      multu(instr_r  ),
       divu(instr_r  ),
       mfhi(instr_r  ),
       mflo(instr_r  ),
        and(instr_r  ),
         or(instr_r  ),
        nor(instr_r  ),
        xor(instr_r  ),
        slt(instr_r  ),
       sltu(instr_r  ),
        mov(instr_r  )
}

enum op_r_s {
        sll(instr_r  ),
        srl(instr_r  ),
        sra(instr_r  ),
       sllv(instr_r  ),
       srlv(instr_r  ),
       srav(instr_r  )
};

enum op_j_r {
         jr(instr_r  ),
       jalr(instr_r  )
}

enum op_j {
          j(instr_j  ),
        jal(instr_j  )
}

enum op_i_s {
       addi(instr_i_s),
       slti(instr_i_s),
        beq(instr_i_s),
        bne(instr_i_s),
         lb(instr_i_s),
        lbu(instr_i_s),
         lh(instr_i_s),
        lhu(instr_i_s),
         lw(instr_i_s),
         ll(instr_i_s),
         sc(instr_i_s),
        bge(instr_i_s),
        bgt(instr_i_s),
        ble(instr_i_s),
        blt(instr_i_s)
}

enum op_i_u {
      addiu(instr_i_u),
       andi(instr_i_u),
        ori(instr_i_u),
       xori(instr_i_u),
      sltiu(instr_i_u),
        lui(instr_i_u),
         sb(instr_i_u),
         sh(instr_i_u),
         sw(instr_i_u),
         la(instr_i_u),
         li(instr_i_u)
}

enum reg {
    zero,
    at,
    v0, v1,
    a0, a1, a2, a3,
    t0, t1, t2, t3, t4, t5, t6, t7,
    s0, s1, s2, s3, s4, s5, s6, s7,
    t8, t9,
    k0, k1,
    gp,
    sp, fp, ra
}
