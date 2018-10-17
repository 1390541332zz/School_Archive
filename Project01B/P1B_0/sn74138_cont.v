////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    sn74138_continuous.v
// Author:      Jason Thweatt
// Date:        24 September 2017
// Version:     1
// Description: This file contains a behavioral model for the 74138 3-to-8 decoder IC chip.
//              Specifically, it uses continuous assignment and dataflow operators.
//              We are using it to continue practicing with the Modelsim environment, AND
//              as a counterpoint to the method of structural modeling.

module sn74138_continuous(G1, G2a_n, G2b_n, C, B, A, Y_n);
   input        G1, G2a_n, G2b_n;	// Enable inputs: G1 is active-high, G2a and G2b are active-low.
   input        C, B, A;           	// Decoder inputs: C is the MSB. A is the LSB.
   output [7:0] Y_n;               	// Decoder outputs Y_n[7] to Y_n[0]. The outputs are active low.

   // Intermediate signals, declared as wires.
   wire   [7:0] dec_out;		// An intermediate decoder output   

   // Use the value of ins to assign the appropriate value to dec_out.
   // The value of ins should always be specified, so the unknown value should never be assigned.

   assign dec_out = ({C, B, A} == 3'b000) ? 8'b11111110 : 
                    ({C, B, A} == 3'b001) ? 8'b11111101 :
                    ({C, B, A} == 3'b010) ? 8'b11111011 :
                    ({C, B, A} == 3'b011) ? 8'b11110111 :
                    ({C, B, A} == 3'b100) ? 8'b11101111 :
                    ({C, B, A} == 3'b101) ? 8'b11011111 :
                    ({C, B, A} == 3'b110) ? 8'b10111111 :
                    ({C, B, A} == 3'b111) ? 8'b01111111 : 8'bx;

   assign Y_n = (G1 & ~G2a_n & ~G2b_n) ? dec_out : 8'b11111111;

endmodule
