`include "constants.h"

module ddstop(
    input  wire        clk,
    input  wire        reset,
    input  wire [15:0] increment,
    input  wire        update,
    output wire [15:0] q,
    output wire        ready
);

//---------------------------------------------------------------------------//
/* verilator lint_off VARHIDDEN */

function [15:0] accumulator;
input [15:0]
    in_angle,
    in_angle_add;
reg [15:0] 
    mid_angle,
    out_angle;
begin
    mid_angle = in_angle + in_angle_add;
    out_angle = (mid_angle > (PI2 * 2)) ? mid_angle - (PI2 * 4)
                                        : mid_angle;
    accumulator = out_angle;
end
endfunction

/* verilator lint_on VARHIDDEN */
//---------------------------------------------------------------------------//

reg [15:0] 
    in_angle;
reg 
    update_csine;

cordicsine csine(
   .clk(clk),
   .reset(reset),
   .update(update_csine),
   .in_angle(in_angle),
   .ready(ready),
   .out_angle(q)
);

always @(posedge update) in_angle  <= accumulator(q, increment);
always @(posedge clk) update_csine <= update;

endmodule
