/////////////////////////////////////////////////////////////////
//  Filename     : counter_11bit.v
//  Author       : Jacob Abel
//  Date         : 2018-10-15
//  Version      : 1
//  Description  : This module is a behavioral description of
//          a simple eleven-bit counter with enable and
//          asynchronous clear.
//
//          This module has three inputs and one output:
//              clk:    input  - system clock
//              clear:  input  - asynchronous clear (active high)
//              enable: input  - count advances when asserted high
//              cout:   output - 11-bit counter output
//
//          This module has two parameters:
//              CLRDEL - delay from clear asserted to output valid
//              CLKDEL - delay from clk rising to output valid
//
//
//         This module is not synthesizable.  It is intended
//         for modeling only and should not be used as a
//         template for synthesizable modules.
//
//         This module was adapted from the counter_4bit module. 
//

`timescale 1 ns/100 ps
module counter_11bit (enable, clear, clk, cout);
    parameter CLRDEL = 5;     // delay from clear asserted to output valid
    parameter CLKDEL = 10;    // delay from clk rising to output valid

    input       enable;       // count advances when asserted high
    input        clear;       // asynchronous clear (active high)
    input          clk;       // system clock
    output [10:0] cout;       // 11-bit counter output

    reg [10:0] cout;          // cout is a reg

    // Locally declared nets
    reg [10:0] count;         // local count holder register

    initial count = 0;

    // Build behavioral 11-bit up-counter with asynchronous clear
    always @(posedge clk or posedge clear)
    begin
        if (clear == 1) 
            begin
                count = 11'b0;
                cout = #CLRDEL count;
            end
        else if (clk == 1) 
            begin
                 if (enable == 1) 
                     begin
                         if (count == 11'h7FF) 
                             count = 0;
                         else
                             count = count + 11'd1;
                     end    
                cout =  #CLKDEL count;
            end
    end
endmodule
