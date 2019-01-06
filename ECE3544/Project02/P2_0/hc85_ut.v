// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps 
///////////////////////////////////////////////////////////////////////////////
// Filename:    hc85_ut.v
// Author:      Jacob Abel
// Date:        15 October 2018
// Version:     1
// Description: This module implements the HC85 High Speed CMOS Logic 4-bit 
// Magnitude Comparitor. This module is untimed.

module hc85_ut(
    input [3:0] a_in, b_in,
    input  ia_lt_b, ia_eq_b, ia_gt_b,
    output oa_lt_b, oa_eq_b, oa_gt_b
);
    wire cmp_lt, cmp_gt, cmp_eq, cas_lt, cas_gt, cas_eq;

    assign cmp_eq = (a_in == b_in);
    assign cmp_gt = (a_in >  b_in);
    assign cmp_lt = (a_in <  b_in);

    assign cas_eq = ia_eq_b;
    assign cas_gt = ~(ia_lt_b || ia_eq_b);
    assign cas_lt = ~(ia_gt_b || ia_eq_b);

    assign oa_eq_b = (cmp_eq && cas_eq);
    assign oa_gt_b = (cmp_gt || (cmp_eq && cas_gt));
    assign oa_lt_b = (cmp_lt || (cmp_eq && cas_lt));

endmodule

