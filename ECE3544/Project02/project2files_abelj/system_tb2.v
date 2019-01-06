// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps 

///////////////////////////////////////////////////////////////////////////////
// Filename:    system_tb2.v
// Author:      Jacob Abel
// Date:        15 October 2018
// Version:     1
// Description: This module contains a test bench for a system utilising 
//              the HC85 Comparator, an 11-bit counter, and the 74FC 
//              10-bit register. This module is tuned to cause occasional
//              errors due to propogation delay.

module system_tb2();
    reg clk_en, ctr_en, ctr_clr;
    wire t_clk, o_lt, o_eq, o_gt;
    wire [10:0] cout;
    wire [9:0] q_out;
    clk #(10) CLK (clk_en, t_clk);
    counter_11bit U1(ctr_en, ctr_clr, t_clk, cout);
//          A,         B,         LT,      EQ,      GT
    hc85 U2(cout[3:0], cout[7:4], cout[8], cout[9], cout[10],
            o_lt, o_eq, o_gt);
    register_10bit U3(t_clk, {7'b0, o_lt, o_eq, o_gt}, q_out);

    initial begin
        ctr_en  <= 1;
        clk_en  <= 1;
        ctr_clr <= 0;
        #102350
        ctr_en  <= 0;
        clk_en  <= 0;
        ctr_clr <= 1;
        $stop; 
    end
endmodule

