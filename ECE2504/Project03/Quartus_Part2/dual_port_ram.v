////////////////////////////////////////////////////////////////////////////////////////////////////
// File: dual_port_ram.v
//
// ******************************************
// YOU ARE NOT PERMITTED TO MODIFY THIS FILE.
// ******************************************
//
// Description: This is a model of a simple synchronous dual-port RAM for the Simple Computer of
//              Chapter 9. The dual_port_ram module implements the register file.
//
// Created: 06/2012, Xin Xin, Virginia Tech
////////////////////////////////////////////////////////////////////////////////////////////////////

module dual_port_ram
(
   input [15:0] data,
   input [2:0] DA,
   input [2:0] AA,
   input [2:0] BA,
   input we, clk,
   input rst,
   output [15:0] a, b, r0, r1, r2, r3, r4, r5, r6, r7
);

   // Declare the RAM unit.
   reg [15:0] ram[7:0];

   always@(posedge clk) begin
      if(rst == 1'b1) begin
			ram[0] = 0;
			ram[1] = 0;
			ram[2] = 0;
			ram[3] = 0;
			ram[4] = 0;
			ram[5] = 0;
			ram[6] = 0;
			ram[7] = 0;
		end
      // Write
      else if(we)
			ram[DA] <= data;
      //addr_reg <= DA;
   end

   // Continuous assignment implies read returns NEW data.
   // This is the natural behavior of the TriMatrix memory blocks in Single Port mode.
   assign a = ram[AA];
   assign b = ram[BA];

	assign r0 = ram[0];
	assign r1 = ram[1];
	assign r2 = ram[2];
	assign r3 = ram[3];
	assign r4 = ram[4];
	assign r5 = ram[5];
	assign r6 = ram[6];
	assign r7 = ram[7];

endmodule
