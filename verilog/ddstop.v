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

function accumulator(
    input wire [15:0] in_angle,
    input wire [15:0] in_angle_add;
);
    wire [15:0] mid_angle;
    wire [15:0] out_angle;
begin
    mid_angle = in_angle + in_angle_add;
    out_angle = (mid_angle > (PI2 * 2)) ? mid_angle - (PI2 * 4)
                                        : mid_angle;
    accumulator = out_angle;
end
endtask

//---------------------------------------------------------------------------//

reg [15:0] 
    in_angle;
reg 
    update_csine;

cordicsine csine(
   .clk(clk),
   .reset(reset),
   .update(update),
   .in_angle(in_angle),
   .ready(ready),
   .out_angle(q)
);

always @(posedge update) in_angle  = accumulator(q, increment);
always @(posedge clk) update_csine = update;

endmodule
