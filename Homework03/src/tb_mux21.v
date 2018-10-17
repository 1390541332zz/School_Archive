// Time Unit = 1 ns (#10 = 10 ns)
// simulation Precision = 100 ps
`timescale 1ns/100ps
///////////////////////////////////////////////////////////////////////////////
// Filename:    tb_mux21.v
// Author:      Jacob Abel
// Date:        5 October 2018
// Version:     1
// Description: This file contains a testbench for the 2-to-1 mux.

module tb_mux21();
    reg e, s0, s1;
    reg result;
    wire Y, Y_equiv;

    mux21 DUT0(e, s0, s1, Y);
    assign Y_equiv = Y ^~ result;

    initial begin
        {e, s0, s1, result} = 4'b0000;
        #20;
        {e, s0, s1, result} = 4'b0010;
        #20;
        {e, s0, s1, result} = 4'b0101;
        #20;
        {e, s0, s1, result} = 4'b0111;
        #20;
        {e, s0, s1, result} = 4'b1000;
        #20;
        {e, s0, s1, result} = 4'b1011;
        #20;
        {e, s0, s1, result} = 4'b1100;
        #20;
        {e, s0, s1, result} = 4'b1111;
        #20;
    end

endmodule
