// Mips 1.0 Disassembler

#![allow(non_snake_case)]

use std::env;
use std::io::BufReader;
use std::io::BufWriter;
use std::fs::File;
use std::string::String;

//use parse_obj;
//use export_asm;

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut ifn = args[1].clone();
    
    if !ifn.ends_with(".obj") {
        panic!("Invalid File Type: Expected .obj");
    }
    let ifilename = ifn.clone();
    let ilen = ifn.len() - 4;
    ifn.truncate(ilen);
    let ofilename = ifn.clone() + ".s";
    println!("ifile {:?} ofile{:?}", ifilename, ofilename);
    
    let ifile = File::open(ifilename).expect("Unable to read file");
    let mut ofile = File::create(ofilename).expect("Unable to write file");
    let mut reader = BufReader::new(ifile);
    let mut writer = BufWriter::new(ofile);
    //let asm = parse_obj(reader)?;
    //export_asm(asm)?;
}
