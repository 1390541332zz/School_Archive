`include "constants.h"

module cordicsine(
    input  wire        clk,
    input  wire        reset,
    input  wire        update,
    input  wire [15:0] in_angle,
    output reg         ready,
    output reg  [15:0] out_angle
);

//---------------------------------------------------------------------------//
/* verilator lint_off VARHIDDEN */
function [15:0] quadrant;
input [15:0] 
    in_angle;
reg [15:0] 
    mid_angle,
    out_quad;
begin
    mid_angle = (in_angle > (PI2 * 4)) ? in_angle - (PI2 * 4)
                                       : in_angle;

    out_quad = (mid_angle > (PI2 * 3)) ? 3 
             : (mid_angle > (PI2 * 2)) ? 2
             : (mid_angle > (PI2 * 1)) ? 1
                                       : 0;
    quadrant = out_quad;
end
endfunction
//---------------------------------------------------------------------------//

function [15:0] angleadj;
input [15:0] 
    in_angle;
reg [15:0] 
    mid_angle,
    out_angle;
begin
    mid_angle = (in_angle > (PI2 * 4)) ? in_angle - (PI2 * 4)
                                       : in_angle;

    out_angle = (mid_angle > (PI2 * 3)) ? (PI2 * 4 - mid_angle)
              : (mid_angle > (PI2 * 2)) ? (mid_angle - PI2 * 2)
              : (mid_angle > (PI2 * 1)) ? (PI2 * 2 - mid_angle)
                                        : mid_angle;
    angleadj = out_angle;
end
endfunction

/* verilator lint_on VARHIDDEN */
//---------------------------------------------------------------------------//


reg [15:0]
    x, x_new, 
    y, y_new, 
    fix_angle, 
    target_angle, 
    cur_angle, new_angle;

localparam 
    S0      = 0, 
    INIT    = 1,
    COMPUTE = 2,
    DONE    = 3;

reg [1:0]
    state, state_next;
reg [4:0]
    ctr;

//---------------------------------------------------------------------------//

always @(posedge clk) case (ctr)
    5'h01: fix_angle <= shortint'($rtoi(0.7853981633974483 * (2 ** FIX_SHIFT))); 
    5'h02: fix_angle <= shortint'($rtoi(0.4636476090008061 * (2 ** FIX_SHIFT)));
    5'h03: fix_angle <= shortint'($rtoi(0.2449786631268641 * (2 ** FIX_SHIFT)));
    5'h04: fix_angle <= shortint'($rtoi(0.1243549945467614 * (2 ** FIX_SHIFT)));
    5'h05: fix_angle <= shortint'($rtoi(0.0624188099959574 * (2 ** FIX_SHIFT)));
    5'h06: fix_angle <= shortint'($rtoi(0.0312398334302683 * (2 ** FIX_SHIFT)));
    5'h07: fix_angle <= shortint'($rtoi(0.0156237286204768 * (2 ** FIX_SHIFT)));
    5'h08: fix_angle <= shortint'($rtoi(0.0078123410601011 * (2 ** FIX_SHIFT)));
    5'h09: fix_angle <= shortint'($rtoi(0.0039062301319670 * (2 ** FIX_SHIFT)));
    5'h0A: fix_angle <= shortint'($rtoi(0.0019531225164788 * (2 ** FIX_SHIFT)));
    5'h0B: fix_angle <= shortint'($rtoi(0.0009765621895593 * (2 ** FIX_SHIFT)));
    5'h0C: fix_angle <= shortint'($rtoi(0.0004882812111949 * (2 ** FIX_SHIFT)));
    5'h0D: fix_angle <= shortint'($rtoi(0.0002441406201494 * (2 ** FIX_SHIFT)));
    5'h0E: fix_angle <= shortint'($rtoi(0.0001220703118937 * (2 ** FIX_SHIFT)));
    5'h0F: fix_angle <= shortint'($rtoi(0.0000610351561742 * (2 ** FIX_SHIFT)));
    5'h10: fix_angle <= shortint'($rtoi(0.0000305175781155 * (2 ** FIX_SHIFT)));
    5'h11: fix_angle <= shortint'($rtoi(0.0000152587890613 * (2 ** FIX_SHIFT)));
    5'h12: fix_angle <= shortint'($rtoi(0.0000076293945311 * (2 ** FIX_SHIFT)));
    5'h13: fix_angle <= shortint'($rtoi(0.0000038146972656 * (2 ** FIX_SHIFT)));
    default: fix_angle <= 16'h0;
endcase

//---------------------------------------------------------------------------//

always @(posedge clk) begin
    if (reset) begin
        state <= S0;
    end else begin
        state     <= state_next;
        cur_angle <= new_angle;
        x         <= x_new;
        y         <= y_new;
    end
end

always @(*) begin
    ready        = 1'b1;
    target_angle = angleadj(in_angle);
    case (state)
    S0: begin
        state_next = (update) ? INIT : S0;
    end
    INIT: begin
        state_next = COMPUTE;
        new_angle  = 0;
        ready      = 1'b0;
        x_new      = AG_CONST;
        y_new      = 0;
        ctr        = 0;
    end
    COMPUTE: begin
        state_next = (ctr < 16) ? COMPUTE : DONE; 
        ready      = 1'b0;
        if (target_angle > cur_angle) begin
            x_new     = x - (y >> ctr);
            y_new     = y + (x >> ctr);
            new_angle = cur_angle + fix_angle; 
        end else begin
            x_new     = x + (y >> ctr);
            y_new     = y - (x >> ctr);
            new_angle = cur_angle - fix_angle; 
        end
        ctr = ctr + 1;
    end
    DONE: begin
        state_next = (update) ? INIT : DONE;
        out_angle  = (quadrant(in_angle) < 2) ? y : -y;
        y_new      = y;
    end
    endcase
end

endmodule
