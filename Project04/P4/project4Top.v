//////////////////////////////////////////////////////////////////
// Filename: project4Top.v
// Author:   Tom Martin
// Date:     7 November 2017
// Revision: 1
//
// This is the top-level module for ECE 3544 Project 4.

module project4Top(CLOCK_50, KEY, SW, LED, HEX5, HEX4, HEX3, HEX2, HEX1, HEX0);
	input        CLOCK_50;
	input  [3:0] KEY;
	input  [9:0] SW;
	output [9:0] LED;
	output [6:0] HEX5, HEX4, HEX3, HEX2, HEX1, HEX0;
	wire   [6:0] H1_o, H0_o, M1_o, M0_o, S1_o, S0_o;
    wire   [3:0] H1, H0, M1, M0, S1, S0;
    wire  KEY3, KEY2, KEY1;
    wire  reset, adjust, toggle, mode;
    wire [5:0] HEX_flash, HEX_en; 
    reg [24:0] ctr_1hz;
    reg CLK_1HZ;

    assign {mode, toggle, adjust, reset} = {KEY3, KEY2, KEY1, KEY[0]};

    assign HEX5 = (~(HEX_flash[5] && CLK_1HZ) || HEX_en[5]) ? H1_o : 6'h3F; 
    assign HEX4 = (~(HEX_flash[4] && CLK_1HZ) || HEX_en[4]) ? H0_o : 6'h3F; 
    assign HEX3 = (~(HEX_flash[3] && CLK_1HZ) || HEX_en[3]) ? M1_o : 6'h3F; 
    assign HEX2 = (~(HEX_flash[2] && CLK_1HZ) || HEX_en[2]) ? M0_o : 6'h3F; 
    assign HEX1 = (~(HEX_flash[1] && CLK_1HZ) || HEX_en[1]) ? S1_o : 6'h3F; 
    assign HEX0 = (~(HEX_flash[0] && CLK_1HZ) || HEX_en[0]) ? S0_o : 6'h3F; 

    proc7segdecoder H1_dec(H1, H1_o); 
    proc7segdecoder H0_dec(H0, H0_o); 
    proc7segdecoder M1_dec(M1, M1_o); 
    proc7segdecoder M0_dec(M0, M0_o); 
    proc7segdecoder S1_dec(S1, S1_o); 
    proc7segdecoder S0_dec(S0, S0_o); 

    keypressed K1(CLOCK_50, KEY[0], KEY[1], KEY1);
    keypressed K2(CLOCK_50, KEY[0], KEY[2], KEY2);
    keypressed K3(CLOCK_50, KEY[0], KEY[3], KEY3);

    primaryControl PC(
        CLOCK_50, CLK_1HZ,
	    mode, toggle, adjust, reset,
        HEX_en, HEX_flash,
	    H1, H0, M1, M0, S1, S0
    );

    //===================//
    // CLK_1HZ Generator //
    //===================//
    always @(posedge CLOCK_50) begin
        if (reset) begin
            ctr_1hz <= 25'b0;
            CLK_1HZ <= 1'b0;
        end
        else if (ctr_1hz == 25'h17D7840) begin
            CLK_1HZ <= ~CLK_1HZ;
        end
        else begin
            CLK_1HZ <= CLK_1HZ;
            ctr_1hz <= ctr_1hz + 25'b1;
        end
    end
endmodule
