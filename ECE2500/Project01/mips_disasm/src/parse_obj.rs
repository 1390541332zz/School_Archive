// MIPS 1.0 Object file parser

#[macro_use]
extern crate nom;

use std::io;
use mips_asm;


fn parse_obj(is: BufReader) -> Result<mips_asm::asm>
{
    p_obj(is);
}

named!(p_obj, seperated_list_complete!(p_instr, eol!()));

named!(p_instr, do_parse!(
    hex: fold_many_n_m!(4, 4, fold_many_n_m!(2, 2, complete!(hex_digit), 
        Vec::new(), | mut acc: Vec<u8>, item| {
            acc.push(match item {
                '0' .. '9' => Into<u8> item - 48
                'A' .. 'F' => Into<u8> item - 55 
                'a' .. 'f' => Into<u8> item - 87
            });
            acc
        }), Vec::new(), |mut acc: Vec<u8>, item| {
            acc.push((item[0] << 4) | item[1]);
            acc
        }
    ) >>
    (alt_complete!(hex,
        p_instr_nop | p_instr_r | p_instr_j | p_instr_i
    ))
));

named!(p_instr_nop, do_parse!(
    instr: verify!(take_bits!(u32, 32), |x| x == 0) >>
    (instr::nop)
));

named!(p_instr_r, do_parse!(
    verify!(take_bits!(u8, 6), |x| x == 0) >>
    rs: p_reg >>
    rt: p_reg >>
    rd: p_reg >>
    sh: take_bits!(u8, 5)? >>
    alt!(
         value!(instr::sll(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x00))
       | value!(instr::srl(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x02))
       | value!(instr::sra(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x03))
       | value!(instr::sllv(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x04))
       | value!(instr::srlv(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x06))
       | value!(instr::srav(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x07))
       | value!(instr::jr(rs, rt, rd, sh)     , tag_bits!(u8, 6, 0x08))
       | value!(instr::jalr(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x09))
    // | value!(instr::movz(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x0a))
    // | value!(instr::movn(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x0b))
       | value!(instr::syscall(rs, rt, rd, sh), tag_bits!(u8, 6, 0x0c))
    // | value!(instr::break(rs, rt, rd, sh)  , tag_bits!(u8, 6, 0x0d))
    // | value!(instr::sync(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x0f))
       | value!(instr::mfti(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x10))
       | value!(instr::mthi(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x11))
       | value!(instr::mflo(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x12))
       | value!(instr::mtlo(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x13))
       | value!(instr::mult(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x18))
       | value!(instr::multu(rs, rt, rd, sh)  , tag_bits!(u8, 6, 0x19))
       | value!(instr::div(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x1a))
       | value!(instr::divu(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x1b))
       | value!(instr::add(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x20))
       | value!(instr::addu(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x21))
       | value!(instr::sub(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x22))
       | value!(instr::subu(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x23))
       | value!(instr::and(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x24))
       | value!(instr::or(rs, rt, rd, sh)     , tag_bits!(u8, 6, 0x25))
       | value!(instr::xor(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x26))
       | value!(instr::nor(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x27))
       | value!(instr::slt(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x2a))
       | value!(instr::sltu(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x2b))
    // | value!(instr::tge(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x30))
    // | value!(instr::tgeu(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x31))
    // | value!(instr::tlt(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x32))
    // | value!(instr::tltu(rs, rt, rd, sh)   , tag_bits!(u8, 6, 0x33))
    // | value!(instr::teq(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x34))
    // | value!(instr::tne(rs, rt, rd, sh)    , tag_bits!(u8, 6, 0x36))         
    )
));

named!(p_instr_j, alt!(
     value!(instr::j(take_bits!(u32, 26)), tag_bits!(u8, 6, 0x02))
   | value!(instr::jal(take_bits!(u32, 26)), tag_bits!(u8, 6, 0x03))
));

named!(p_instr_i, do_parse!(
    op: take_bits!(u8, 6) >>
    rs: p_reg >>
    rt: p_reg >>
    sh: take_bits!(u8, 16)? >>
    (instr)
);

named!(p_reg, alt!(
    value!(reg::zero, tag_bits!(u8, 5,  0))
  | value!(reg::at  , tag_bits!(u8, 5,  1))
  | value!(reg::v0  , tag_bits!(u8, 5,  2))
  | value!(reg::v1  , tag_bits!(u8, 5,  3))
  | value!(reg::a0  , tag_bits!(u8, 5,  4))
  | value!(reg::a1  , tag_bits!(u8, 5,  5))
  | value!(reg::a2  , tag_bits!(u8, 5,  6))
  | value!(reg::a3  , tag_bits!(u8, 5,  7))
  | value!(reg::t0  , tag_bits!(u8, 5,  8))
  | value!(reg::t1  , tag_bits!(u8, 5,  9))
  | value!(reg::t2  , tag_bits!(u8, 5, 10))
  | value!(reg::t3  , tag_bits!(u8, 5, 11))
  | value!(reg::t4  , tag_bits!(u8, 5, 12))
  | value!(reg::t5  , tag_bits!(u8, 5, 13))
  | value!(reg::t6  , tag_bits!(u8, 5, 14))
  | value!(reg::t7  , tag_bits!(u8, 5, 15))
  | value!(reg::s0  , tag_bits!(u8, 5, 16))
  | value!(reg::s1  , tag_bits!(u8, 5, 17))
  | value!(reg::s2  , tag_bits!(u8, 5, 18))
  | value!(reg::s3  , tag_bits!(u8, 5, 19))
  | value!(reg::s4  , tag_bits!(u8, 5, 20))
  | value!(reg::s5  , tag_bits!(u8, 5, 21))
  | value!(reg::s6  , tag_bits!(u8, 5, 22))
  | value!(reg::s7  , tag_bits!(u8, 5, 23))
  | value!(reg::t8  , tag_bits!(u8, 5, 24))
  | value!(reg::t9  , tag_bits!(u8, 5, 25))
  | value!(reg::k0  , tag_bits!(u8, 5, 26))
  | value!(reg::k1  , tag_bits!(u8, 5, 27))
  | value!(reg::gp  , tag_bits!(u8, 5, 28))
  | value!(reg::sp  , tag_bits!(u8, 5, 29))
  | value!(reg::fp  , tag_bits!(u8, 5, 30))
  | value!(reg::ra  , tag_bits!(u8, 5, 31))
));
