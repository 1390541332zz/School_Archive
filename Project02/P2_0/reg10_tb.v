// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps 

///////////////////////////////////////////////////////////////////////////////
// Filename:    reg10_tb.v
// Author:      Jacob Abel
// Date:        15 October 2018
// Version:     1
// Description: This file contains a test bench for the CY74 10-bit Register.

module reg10_tb();
    reg clk_en, ctr_en, ctr_clr;
    wire t_clk;
    wire [10:0] t_ctr;
    wire [9:0] q_out;
    clk #(100) CLK (clk_en, t_clk);
    counter_11bit CTR (ctr_en, ctr_clr, t_clk, t_ctr);
    register_10bit DUT0(t_clk, t_ctr, q_out);

    initial begin
        ctr_en  <= 1;
        clk_en  <= 1;
        ctr_clr <= 0;
        #204800
        ctr_clr <= 1;
        #100 
        ctr_clr <= 0;
        #2000
        ctr_en  <= 0;
        clk_en  <= 0;
        ctr_clr <= 1;
        $stop; 
    end
endmodule

