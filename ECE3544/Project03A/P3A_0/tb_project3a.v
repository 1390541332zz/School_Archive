////////////////////////////////////////////////////////////////////////////////
// Filename:    tb_project3a.v
// Author:      Yu Guo
// Date:        13 October 2018
// Version:     1
// Description: This is the test bench for the Project 3A primary module. 

`timescale 1 ns/100 ps

module tb_project3a();
    reg eq_gt, eq_lt, eq_eq;
    reg [3:0] i;
    reg [3:0] i_a, i_b;
    reg en, i_lt, i_gt, i_eq;
    reg [9:0] eq_led;
    
    wire [13:0] icmp_a [3:0], icmp_b [3:0];
    wire [13:0] icmp_gt, icmp_lt, icmp_eq;
    wire [13:0] cmp_gt, cmp_lt, cmp_eq;
    wire [6:0]  digit0, digit1;
    wire [9:0]  o_led;
    wire eq;
    
    wire [6:0] o_a, o_b, o_gt, o_lt, o_eq;

    ECE3544project3a DUT0({1'b0, en, i_a, i_b}, o_led, o_eq, o_lt, o_gt, o_b, o_a);

    assign icmp_a[3] = 8'b10_11_11_11;
    assign icmp_b[3] = 8'b01_11_11_11;
    assign icmp_a[2] = 8'b00_10_11_11;
    assign icmp_b[2] = 8'b00_01_11_11;
    assign icmp_a[1] = 8'b00_00_10_11;
    assign icmp_b[1] = 8'b00_00_01_11;
    assign icmp_a[0] = 8'b00_00_00_10;
    assign icmp_b[0] = 8'b00_00_00_01;
    
    assign icmp_gt   = 8'b00_00_00_00;
    assign icmp_lt   = 8'b00_00_00_00;
    assign icmp_eq   = 8'b00_00_00_00;

    assign cmp_gt    = 8'b10_10_10_10;
    assign cmp_lt    = 8'b01_01_01_01;
    assign cmp_eq    = 8'b00_00_00_00;

    assign digit0 = 7'b1000000; 
    assign digit1 = 7'b1111001; 

// Evaluate Equivalence.
    assign eq = (eq_gt && eq_lt && eq_eq && (& eq_led));
// Begin Test
    initial begin
        en <= 1;
        i_a  <= {icmp_a[3][i], icmp_a[2][i], icmp_a[1][i], icmp_a[0][i]};
        i_b  <= {icmp_b[3][i], icmp_b[2][i], icmp_b[1][i], icmp_b[0][i]};
        i_gt <= icmp_gt[i];
        i_lt <= icmp_lt[i];
        i_eq <= icmp_eq[i];
        #1; 
        for(i = 0; i < 7; i = i + 1) begin
            i_a  <= {icmp_a[3][i], icmp_a[2][i], icmp_a[1][i], icmp_a[0][i]};
            i_b  <= {icmp_b[3][i], icmp_b[2][i], icmp_b[1][i], icmp_b[0][i]};
            i_gt <= icmp_gt[i];
            i_lt <= icmp_lt[i];
            i_eq <= icmp_eq[i];
            #1;
            eq_led = (o_led ^~ {1'b0, en, i_a, i_b});
            eq_gt = (o_gt ^~ (cmp_gt[i] ? digit1 : digit0));
            eq_lt = (o_lt ^~ (cmp_lt[i] ? digit1 : digit0));
            eq_eq = (o_eq ^~ (cmp_eq[i] ? digit1 : digit0));
            #20;
        end
        en = 0;
        #1;
        eq_gt <= (o_gt ^~ digit0);
        eq_lt <= (o_lt ^~ digit0);
        eq_eq <= (o_eq ^~ digit0);
        #20;
    end
endmodule
