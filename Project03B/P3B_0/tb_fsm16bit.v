////////////////////////////////////////////////////////////////////////////////
// Filename:    tb_fsm16bit.v
// Author:      Jason Thweatt
// Date:        10/15/2013
// Version:     1
// Description: FSM testbench.

`timescale 1 ns/100 ps

module tb_fsm16bit();
    reg         clk_en, clock, reset, enable, check, mode, direction;
    reg  [3:0]  value;
    reg  [15:0] o_expected;
    wire [15:0] outputValue;
    wire [15:0] eq_o;
    wire eq;
// Instantiate counter.

    fsm16bit dut1(clock, reset, enable, check, mode, direction, value, outputValue);    

// Test the counter functionality here.
// You should set up a 50 MHz clock, along with the various control and input signals.

assign eq_o = o_expected ^~ outputValue;
assign eq   = & eq_o;

initial begin
    clock      <= 1'b0;
    clk_en     <= 1'b1;
    reset      <= 1'b0;
    enable     <= 1'b0;
    check      <= 1'b0;
    mode       <= 1'b0;
    direction  <= 1'b0;
    value      <= 4'h3;
    o_expected <= 16'hxxxx;
    #10 o_expected = 16'h0000;
    #1  reset = 1'b1;
    #19 o_expected = 16'h0000;
    #20 o_expected = 16'h0000;
    #1  enable = 1'b1;
    #19 o_expected = 16'h6453;
    #20 o_expected = 16'h6453;
    #1  check = 1'b1;
    #19 o_expected = 16'h6450;
    #1  direction = 1'b1;
    #19 o_expected = 16'h6453;
    #1  value = 4'h5;
    #19 o_expected = 16'h6458;
    #1  direction = 1'b0;
    #19 o_expected = 16'h6453;
    #1  mode = 1'b1;
    #19 o_expected = 16'hB229;
    #1  direction = 1'b1;
    #19 o_expected = 16'h6453;
    #1  reset = 1'b0;
        o_expected = 16'h0000;
    #20 clk_en = 1'b0;
end

always begin
    #10 clock = (~clock) & clk_en;
end
endmodule
