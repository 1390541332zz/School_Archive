////////////////////////////////////////////////////////////////
//  Filename     : mips-control.v
//  Module       : MIPS_CONTROL
//  Author       : L. Nazhand-Ali
//  Modified by  : C. Patterson
//  Description  : MIPS control module 
//   
//     You need to modify this module to complete your project.
//  The style of Verilog programming given in this module is 
//  called "Behavioral modeling". For each instruction that you
//  add to your datapath, you need to set the control signals to
//  the correct values. Use the implemented instructions 'addi' and
//  'lui' as your guide. Read the comments inside to see how to edit
//  this module.
//
//    To simplify the datapath, we are not using the two-level
//  control for ALU as discussed in the book. Instead, this module
//  directly computes the ALUCntrl signals. Therefore, we do not
//  have a separate ALU control unit.

module MIPS_CONTROL
  (
   op_in,
   func_in,
   
   branch_out, 
   regWrite_out, 
   regDst_out, 
   extCntrl_out, 
   ALUSrc_out, 
   ALUCntrl_out, 
   memWrite_out,
   memRead_out,
   memToReg_out, 
   jump_out
   );
   
   parameter control_delay = 6;	

   input [5:0]  op_in, func_in;
   
   output [3:0] ALUCntrl_out;
   reg [3:0] 	ALUCntrl_out;
   
   output 	branch_out, jump_out;				
   reg 		branch_out, jump_out;				
   
   output 	regWrite_out, regDst_out;
   reg 		regWrite_out, regDst_out;
   
   output 	extCntrl_out, ALUSrc_out;
   reg 		extCntrl_out, ALUSrc_out;
   
   output 	memWrite_out, memRead_out, memToReg_out;
   reg 		memWrite_out, memRead_out, memToReg_out;

   always@*
     begin
	#control_delay;

	// casex statement in Verilog is very similar to switch/case in 
	// C/C++. Only the formatting is slightly different as shown below.

	// The following case statement will look at opcode and func fields
	casex({op_in, func_in})

	  {6'h00, 6'h00}: // sll
	    begin       
	       regDst_out   = 1; //0 means RT  and 1 means RD
	       ALUSrc_out   = 0; //0 means REG and 1 means IMM
	       memToReg_out = 0; //0 means NO  and 1 means YES
	       regWrite_out = 1; //0 means NO  and 1 means YES
	       memWrite_out = 0; //0 means NO  and 1 means YES
	       memRead_out  = 0; //0 means NO  and 1 means YES
	       branch_out   = 0; //0 means NO  and 1 means YES
	       jump_out     = 0; //0 means NO  and 1 means YES
	       extCntrl_out = 0; //0 means Zero-extension and 1 means Sign-extension
	       ALUCntrl_out = 4'b1000; //Refer to table on page 316 of the book
	    end // case: {6'h00, 6'h00}

	  // For addi instruction, 
	  // opcode is 0x8 and func field is don't care
 	  {6'h08, 6'hxx}: // addi
	    begin
	       regDst_out   = 0;
	       ALUSrc_out   = 1;
	       memToReg_out = 0;
	       regWrite_out = 1;
	       memWrite_out = 0;
	       memRead_out  = 0;
	       branch_out   = 0;
	       jump_out     = 0;
	       extCntrl_out = 1;
	       ALUCntrl_out = 4'b0010;
	    end // case: {6'h08, 6'hxx}

	  {6'h0f, 6'hxx}: // lui
             begin
	       regDst_out   = 0;
	       ALUSrc_out   = 1;
	       memToReg_out = 0;
	       regWrite_out = 1;
	       memWrite_out = 0;
	       memRead_out  = 0;
	       branch_out   = 0;
	       jump_out     = 0;
	       extCntrl_out = 1'bx;
	       ALUCntrl_out = 4'b1111; // Besides the operations on page 301, our ALU implements lui with this special code
	    end // case: {6'h0f, 6'hxx}
	  
	  default:   //anything else
	    begin		
	       regDst_out   = 1'bx;
               ALUSrc_out   = 1'bx;
               memToReg_out = 1'bx;
               regWrite_out = 1'bx;
               memWrite_out = 1'bx;
               branch_out   = 1'bx;
               jump_out     = 1'bx;
               extCntrl_out = 1'bx;
               ALUCntrl_out = 4'bxxxx;
	    end // case: default
	  
	endcase // casex({op_in, func_in})
	
	
     end // always@ *
      
endmodule // MIPS_CONTROL



























