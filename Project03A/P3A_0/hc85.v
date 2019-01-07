///////////////////////////////////////////////////////////////////////////////
// Filename:    hc85.v
// Author:      Jacob Abel
// Date:        15 October 2018
// Version:     1
// Description: This module implements the HC85 High Speed CMOS Logic 4-bit 
// Magnitude Comparitor. 

module hc85(
    input [3:0] a_in, b_in,
    input  en,
    input  ia_lt_b, ia_eq_b, ia_gt_b,
    output oa_lt_b, oa_eq_b, oa_gt_b
);

    reg cmp_lt, cmp_gt, cmp_eq, cas_lt, cas_gt, cas_eq, lt, eq, gt;

    assign oa_lt_b = en ? lt : 1'b0;
    assign oa_eq_b = en ? eq : 1'b0;
    assign oa_gt_b = en ? gt : 1'b0;

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

