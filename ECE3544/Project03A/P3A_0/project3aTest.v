////////////////////////////////////////////////////////////////////////////////
// Filename: project3aTest.v
// Author:   Yu Guo
// Date:     13 October 2018
// Revision: 1
//
// This module is for ECE 3544 Project 3a.
// Do not modify the module declaration or ports in this file.
// It provides an example for a component that the designer can instantiate in
// the top-level module.

module project3aTest(hex_digit, hex_display);
   input  [1:0] hex_digit;
   output [6:0] hex_display;
   reg    [6:0] hex_display;

   always@(hex_digit) begin
      case(hex_digit)
         2'h0: hex_display = 7'b1000000; 
         2'h1: hex_display = 7'b1111001; 
			2'h2: hex_display = 7'b0100100; 
         2'h3: hex_display = 7'b0110000;
      endcase
   end

endmodule
