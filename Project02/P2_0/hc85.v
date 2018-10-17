// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps 
///////////////////////////////////////////////////////////////////////////////
// Filename:    hc85.v
// Author:      Jacob Abel
// Date:        15 October 2018
// Version:     1
// Description: This module implements the HC85 High Speed CMOS Logic 4-bit 
// Magnitude Comparitor. 

//module hc85(
//    input [3:0] a_in, b_in,
//    input  ia_lt_b, ia_eq_b, ia_gt_b,
//    output oa_lt_b, oa_eq_b, oa_gt_b
//);
module hc85(a_in, b_in, ia_lt_b, ia_eq_b, ia_gt_b, oa_lt_b, oa_eq_b, oa_gt_b);
    input [3:0] a_in, b_in;
    input ia_lt_b, ia_eq_b, ia_gt_b;
    output oa_lt_b, oa_eq_b, oa_gt_b;
    specify
        (a_in, b_in => oa_lt_b) = (16);
        (a_in, b_in => oa_gt_b) = (16);
        (a_in, b_in => oa_eq_b) = (14);
        (ia_lt_b, ia_eq_b, ia_gt_b => oa_lt_b) = (11);
        (ia_lt_b, ia_eq_b, ia_gt_b => oa_gt_b) = (11);
        (ia_gt_b => oa_eq_b) = (9);
    endspecify

    reg cmp_lt, cmp_gt, cmp_eq, cas_lt, cas_gt, cas_eq, lt, eq, gt;

    assign oa_lt_b = lt;
    assign oa_eq_b = eq;
    assign oa_gt_b = gt;

    always @(a_in or b_in) begin
        cmp_eq <= (a_in == b_in);
        cmp_gt <= (a_in >  b_in);
        cmp_lt <= (a_in <  b_in);
    end

    always @(ia_eq_b or ia_lt_b or ia_gt_b) begin
        cas_eq <= ia_eq_b;
        cas_gt <= ~(ia_lt_b || ia_eq_b);
        cas_lt <= ~(ia_gt_b || ia_eq_b);
    end

    always @(   cmp_eq or cmp_gt or cmp_lt 
             or cas_eq or cas_gt or cas_lt
            ) 
    begin
        eq <= (cmp_eq && cas_eq);
        gt <= (cmp_gt || (cmp_eq && cas_gt));
        lt <= (cmp_lt || (cmp_eq && cas_lt));
    end

endmodule

