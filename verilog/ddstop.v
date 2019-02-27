module ddstop(
    input  wire        clk,
    input  wire        reset,
    input  wire [15:0] increment,
    input  wire        update,
    output wire [15:0] q,
    output wire        ready
);

`include "constants.h"

//---------------------------------------------------------------------------//
/* verilator lint_off VARHIDDEN */

function [17:0] accumulator;
input [17:0]
    in_angle,
    in_angle_add;
reg [17:0] 
    mid_angle,
    out_angle;
begin
    mid_angle = in_angle + in_angle_add;
    out_angle = (mid_angle > (PI2 * 4)) ? mid_angle - (PI2 * 4)
                                        : mid_angle;
    accumulator = out_angle;
end
endfunction

/* verilator lint_on VARHIDDEN */
//---------------------------------------------------------------------------//

reg [17:0] 
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

always @(posedge clk) begin
    in_angle  <= (reset)  ? 0 
               : (update) ? accumulator(in_angle, {{2{increment[15]}}, increment})
                          : in_angle;
    update_csine <= update;
end
endmodule
