///////////////////////////////////////////////////////////////////////////////
//  Filename     : ctr11_tb.v
//  Author       : Jacob Abel
//  Date         : 2018-10-15
//  Version      : 1
//  Description  :  This module serves as a simple testbench
//         for the counter_11bit module.  Two counters are 
//         instantiated and stimulated with a simple sequence.
//
//         There are no inputs or outputs to this module.
//
//         This module was adapted from the ctr_tb module. 

`timescale 1ns/100ps
module ctr11_tb ();

    // Declare local wires and regs
    reg    en_test;           // Locally-created "enable test" signal
    reg    clr_test;          // Locally-created "clear test" signal
    reg    clk_tb_enable;     // Locally-created clock-enable signal
    wire   tb_clk;            // Clock produced by the "clk" module
    wire [10:0] cout1, cout2; // Counter outputs for the two 11-bit counters

    // Intantiate two versions of the counter
    // The first one overrides the default values of the parameters with the "#(20, 30)"
    counter_11bit #(20, 30) M1 (en_test, clr_test, tb_clk, cout1);
    // The second one uses the default values 
    counter_11bit M2 (en_test, clr_test, tb_clk, cout2);

    // Instantiate the clock generator with a period of 100
    clk #(100) M3 (clk_tb_enable, tb_clk);

    // Sequence the ENABLE and CLR signals 
    initial
    begin
        en_test = 0;
        clr_test = 0;
        clk_tb_enable = 1;
        #10 clr_test = 1;
        #40 clr_test = 0;
        #50 en_test = 1;
        #400 en_test = 0;
        #200 en_test = 1;
        #300 clr_test = 1;
        #60 clr_test = 0;
    end


endmodule

