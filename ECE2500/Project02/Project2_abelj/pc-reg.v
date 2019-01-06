////////////////////////////////////////////////////////////////////
//  Filename     : pc-reg.v
//  Module       : PC_REG
//  Author       : L. Nazhand-Ali
//  Modified by  : C. Patterson
//  Description  : 32-bit PC register
//   
//
//     This is a 32-bit register that holds the value of PC.
//  It is also responsible to resetting the PC to 0x00400024
//  when the reset signal is 1.

module PC_REG
  (
   clk,
   reset, 
   PC_in, 
   PC_out
   );

   parameter pc_delay = 1;	
 
   output [31:0] PC_out;				
   reg [31:0] 	 PC_out;
   
   input [31:0]  PC_in;	
   input 	 clk;
   input 	 reset;

   always@(posedge clk or posedge reset)
     begin
	if (~reset)
	  PC_out = PC_in;
	else
	  PC_out = 32'h00400024;
     end
      
endmodule // PC_REG














