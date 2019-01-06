// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps 

///////////////////////////////////////////////////////////////////////////////
// Filename:    ECE3544project3a_tb.v
// Author:      Jacob Abel
// Date:        2 November 2018
// Version:     1
// Description: This file contains a test bench for the Project 3A Primary
// Module.

module ECE3544project3a_tb();
// Reduced Test
    reg eq_gt, eq_lt, eq_eq;
    reg [3:0] i;
    reg [3:0] i_a, i_b;
    reg en, i_lt, i_gt, i_eq;
    
    wire [13:0] icmp_a [3:0], icmp_b [3:0];
    wire [13:0] icmp_gt, icmp_lt, icmp_eq;
    wire [13:0] cmp_gt, cmp_lt, cmp_eq;
    wire eq;
    
    wire o_gt, o_lt, o_eq;

    hc85 DUT0(i_a, i_b, en, i_lt, i_eq, i_gt, o_lt, o_eq, o_gt);
    assign icmp_a[3] = 14'b10_11_11_11_111_111;
    assign icmp_b[3] = 14'b01_11_11_11_111_111;
    assign icmp_a[2] = 14'b00_10_11_11_111_111;
    assign icmp_b[2] = 14'b00_01_11_11_111_111;
    assign icmp_a[1] = 14'b00_00_10_11_111_111;
    assign icmp_b[1] = 14'b00_00_01_11_111_111;
    assign icmp_a[0] = 14'b00_00_00_10_111_111;
    assign icmp_b[0] = 14'b00_00_00_01_111_111;
    
    assign icmp_gt   = 14'b00_00_00_00_100_010;
    assign icmp_lt   = 14'b00_00_00_00_010_010;
    assign icmp_eq   = 14'b00_00_00_00_001_100;

    assign cmp_gt    = 14'b10_10_10_10_100_001;
    assign cmp_lt    = 14'b01_01_01_01_010_001;
    assign cmp_eq    = 14'b00_00_00_00_001_100;


// Evaluate Equivalence.
    assign eq = (eq_gt && eq_lt && eq_eq);
// Begin Test
    initial begin
        en <= 1;
        i_a  <= {icmp_a[3][i], icmp_a[2][i], icmp_a[1][i], icmp_a[0][i]};
        i_b  <= {icmp_b[3][i], icmp_b[2][i], icmp_b[1][i], icmp_b[0][i]};
        i_gt <= icmp_gt[i];
        i_lt <= icmp_lt[i];
        i_eq <= icmp_eq[i];
        #1; 
        for(i = 0; i < 14; i = i + 1) begin
            i_a  <= {icmp_a[3][i], icmp_a[2][i], icmp_a[1][i], icmp_a[0][i]};
            i_b  <= {icmp_b[3][i], icmp_b[2][i], icmp_b[1][i], icmp_b[0][i]};
            i_gt <= icmp_gt[i];
            i_lt <= icmp_lt[i];
            i_eq <= icmp_eq[i];
            #1;
            eq_gt = (o_gt ^~ cmp_gt[i]);
            eq_lt = (o_lt ^~ cmp_lt[i]);
            eq_eq = (o_eq ^~ cmp_eq[i]);
            #20;
        end
    end

// Exhaustive Test
    reg clk_en, ctr_en, ctr_clr;
    wire t_clk, o1_lt, o1_eq, o1_gt;
    wire [10:0] t_ctr;
    clk #(100) CLK (clk_en, t_clk);
    counter_11bit CTR (ctr_en, ctr_clr, t_clk, t_ctr);
//               A,          B,          LT,       EQ,        GT,
    hc85_ut DUT1(t_ctr[7:4], t_ctr[3:0], en, t_ctr[9], t_ctr[10], t_ctr[8],
                 o1_lt, o1_eq, o1_gt); 
// Begin Test
    initial begin
        ctr_en  <= 1;
        clk_en  <= 1;
        ctr_clr <= 0;
        #204700
        ctr_en  <= 0;
        clk_en  <= 0;
        ctr_clr <= 1;
        $stop; 
    end
endmodule

