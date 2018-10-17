// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps 
///////////////////////////////////////////////////////////////////////////////
// Filename:    register_10bit.v
// Author:      Jacob Abel
// Date:        15 October 2018
// Version:     1
// Description: This module contains an implemtation of the CY74 10-bit Register.


//module register_10bit(
//    input clk,
//    input  [9:0] d_in,
//    output [9:0] q_out
//);
module register_10bit(clk, d_in, q_out);
    input clk; 
    input [9:0] d_in;
    output[9:0] q_out;
    reg [9:0] d;

    assign q_out = d;

    always @(posedge clk) begin
        d = d_in;
    end
endmodule

