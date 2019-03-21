module sin_gen(
    input         clk,
    input         reset,
    input  [15:0] increment,
    input         update,
    output [15:0] q
);

`include "constants.h"

//---------------------------------------------------------------------------//
/* verilator lint_off VARHIDDEN */

/*
 * fixed accumulator(fixed inangle, fixed inangleadd) {
 *   inangle = inangle + inangleadd;
 * 
 *   if (inangle > 4*PI2)
 *     inangle = inangle - 4*PI2;
 * 
 *   return inangle;
 * }
*/

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
    update_csin;

cordic_sin csin(
   .clk(clk),
   .reset(reset),
   .update(update_csin),
   .in_angle(in_angle),
   .out_angle(q)
);

always @(posedge clk) begin
    in_angle  <= (reset)  ? 0 
               : (update) ? accumulator(in_angle, {{2{increment[15]}}, increment})
                          : in_angle;
    update_csin <= update;
end
endmodule
