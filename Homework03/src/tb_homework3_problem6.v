// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps
///////////////////////////////////////////////////////////////////////////////
// Filename:    tb_homework3_problem6.v
// Author:      Jacob Abel
// Date:        5 October 2018
// Version:     1
// Description: This file contains a testbench for the hw3p6 F() module.

module tb_homework3_problem6();
    reg [4:0] count;
    wire [3:0] abcd;
    //                       5432109876543210
    reg [15:0] results = 16'b1100101010100111;
    reg result;
    wire f, f_equiv;

    assign abcd = count[3:0]; 
    homework3_problem6 DUT0(abcd[0], abcd[1], abcd[2], abcd[3], f);
    assign f_equiv = f ~^ result;

    initial begin
        result = 0;
        for(count = 0; count < 16; count = count + 1) begin
            result = results[abcd];
            #20;
        end
    end

endmodule

