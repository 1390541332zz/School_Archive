/////////////////////////////////////////////////////////////////////
//  Filename     : instruction-mem.v
//  Module       : IMEM
//  Author       : L. Nazhand-Ali
//  Modified by  : C. Patterson
//  Description  : instruction memory
//   
//
//      This module models the MIPS text segement starting at 
//  address 0x00400024 (SPIM default for loaded code). Please note
//  that we only model the first 128 words of instruction memory.
//  Thus, valid addresses to load instructions are 0x00400024 to 0x00400220.
//
//     At the begining of simulation, this module reads a text file
//  called program.txt which contains the instructions to be executed
//  in the hex format. Note that 0x should be removed from the 
//  instructions, otherwise an error will occure when reading the file.
//  Copy your test cases to program.txt to simulate them.

module IMEM
  (
   address_in, 
   instruction_out
   );

   // Delay to do a memory read or write
   parameter memory_delay = 20;	
   
   input [31:0]  address_in;
   
   output [31:0] instruction_out;
   reg [31:0] 	 instruction_out;			
   
   reg [6:0] 	 word_address;
   
   // We allocate space for 128 instructions in our model
   reg [31:0] 	 mem_array[0:127];

   // Reading the instructions from the file into the array
   initial begin
      $readmemh("program.txt", mem_array, 0, 34);
   end
   
   always @(address_in)
     begin
	#memory_delay;
	
	word_address = (address_in - 32'h00400024) >> 2;
	
	if (address_in > 32'h00400220)
	   instruction_out = 32'bxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
	else
	   instruction_out = mem_array[word_address];
	
     end // always @(address_in)
   
endmodule // IMEM















