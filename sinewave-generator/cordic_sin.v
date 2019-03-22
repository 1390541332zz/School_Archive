module cordic_sin(
    input  wire        clk,
    input  wire        reset,
    input  wire        update,
    input  wire [17:0] in_angle,
    output reg  [15:0] out_angle,
    output reg         ready
);

`include "constants.h"

//---------------------------------------------------------------------------//
/* verilator lint_off VARHIDDEN */

/*
 * fixed quadrant(fixed inangle) {
 *   // output: 0-3 for quadrant 0-3
 *   // we assume step-angle is smaller than pi
 *   // so that there are always at least two samples per period (alias-free)
 *   // hence the max input angle can be (2pi + pi)
 *   unsigned q = 0;
 * 
 *   // if inangle >2pi, subtract 2pi.
 *   // This brings inangle in the range 0 - pi and keeps the same quardrant
 *   if (inangle > 4*`PI2) 
 *     inangle = inangle - 4*`PI2;
 * 
 *   if (inangle > 3*`PI2)
 *     return 3;
 *   else if (inangle > 2*`PI2)
 *     return 2;
 *   else if (inangle > `PI2)
 *     return 1;
 * 
 *   return 0;
 * }
 */

function [17:0] quadrant(
    input [17:0] in_angle
);
reg [17:0] 
    mid_angle,
    out_quad;
begin
    mid_angle = (in_angle > (`PI2 * 18'h4)) ? in_angle - (`PI2 * 18'h4)
                                            : in_angle;

    out_quad = (mid_angle > (`PI2 * 18'h3)) ? 18'h3 
             : (mid_angle > (`PI2 * 18'h2)) ? 18'h2
             : (mid_angle > (`PI2 * 18'h1)) ? 18'h1
                                            : 18'h0;
    quadrant = out_quad;
end
endfunction
//---------------------------------------------------------------------------//

/*
 * fixed angleadj(fixed inangle) {
 * 
 *   // input angle is 0 .. 3pi
 *   // output angle in first quadrant such that
 *   // abs(sin(inangle)) = sin(outangle)
 * 
 *   // if inangle >2pi, subtract 2pi.
 *   // This brings inangle in the range 0 - pi and keeps the same quardrant
 *   if (inangle > 4*`PI2) 
 *     inangle = inangle - 4*`PI2;
 * 
 *   if (inangle > 3*`PI2)
 *     return (4*`PI2 - inangle);
 *   else if (inangle > 2*`PI2)
 *     return (inangle - 2*`PI2);
 *   else if (inangle > `PI2)
 *     return (2*`PI2 - inangle);
 * 
 *   return inangle;
 * }
 */

function [17:0] angleadj(
    input [17:0] in_angle
);
reg [17:0] 
    mid_angle,
    out_angle;
begin
    mid_angle = (in_angle > (`PI2 * 18'h4)) ? in_angle - (`PI2 * 18'h4)
                                            : in_angle;

    out_angle = (mid_angle > (`PI2 * 18'h3)) ? (`PI2 * 18'h4 - mid_angle)
              : (mid_angle > (`PI2 * 18'h2)) ? (mid_angle - `PI2 * 18'h2)
              : (mid_angle > (`PI2 * 18'h1)) ? (`PI2 * 18'h2 - mid_angle)
                                             : mid_angle;
    angleadj = out_angle;
end
endfunction

/* verilator lint_on VARHIDDEN */
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
/* verilator lint_off VARHIDDEN */

function [17:0] fix_angle(
    input [4:0] ctr
);
case (ctr)
    5'h00: fix_angle = 18'h6487; 
    5'h01: fix_angle = 18'h3b58;
    5'h02: fix_angle = 18'h1f5b;
    5'h03: fix_angle = 18'hfea ;
    5'h04: fix_angle = 18'h7fd ;
    5'h05: fix_angle = 18'h3ff ;
    5'h06: fix_angle = 18'h1ff ;
    5'h07: fix_angle = 18'hff  ;
    5'h08: fix_angle = 18'h7f  ;
    5'h09: fix_angle = 18'h3f  ;
    5'h0A: fix_angle = 18'h1f  ;
    5'h0B: fix_angle = 18'hf   ;
    5'h0C: fix_angle = 18'h7   ;
    5'h0D: fix_angle = 18'h3   ;
    5'h0E: fix_angle = 18'h1   ;
    5'h0F: fix_angle = 18'h0   ;
    5'h10: fix_angle = 18'h0   ;
    5'h11: fix_angle = 18'h0   ;
    5'h12: fix_angle = 18'h0   ;
    default: fix_angle = 18'h0;
endcase
endfunction
/* verilator lint_on VARHIDDEN */
//---------------------------------------------------------------------------//

reg signed [17:0]
    x, x_new, 
    y, y_new, 
/* verilator lint_off UNUSED */
    y_trunc, 
/* verilator lint_on UNUSED */
    target_angle, 
    cur_angle, new_angle;

localparam 
    S0      = 2'h0, 
    INIT    = 2'h1,
    COMPUTE = 2'h2,
    DONE    = 2'h3;

reg [1:0]
    state, state_next;
reg [4:0]
    ctr, ctr_next;


/*
 * fixed cordicsin(fixed inangle) {
 *   fixed X, Y, TargetAngle, CurrAngle;
 *   unsigned Step;
 * 
 *   X=FIXED(AG_CONST);  // AG_CONST * cos(0)
 *   Y=0;                // AG_CONST * sin(0)
 *   
 *   TargetAngle = angleadj(inangle);
 *   CurrAngle=0;
 *   for(Step=0; Step < 16; Step++) {
 *     fixed NewX;
 *     if (TargetAngle > CurrAngle) {
 *       NewX       =  X - (Y >> Step);
 *       Y          = (X >> Step) + Y;
 *       X          = NewX;
 *       CurrAngle += Angles[Step];
 *     } else {
 *       NewX       = X + (Y >> Step);
 *       Y          = -(X >> Step) + Y;
 *       X          = NewX;
 *       CurrAngle -= Angles[Step];
 *     }
 *   }
 * 
 *   if (quadrant(inangle) < 2) 
 *     return  Y;
 *   else
 *     return -Y;
 * }
 */

always @(posedge clk) begin
    if (reset) begin
        state <= S0;
    end else begin
        state     <= state_next;
        cur_angle <= new_angle;
        ctr       <= ctr_next;
        x         <= x_new;
        y         <= y_new;
    end
end

always @(*) begin
    target_angle = angleadj(in_angle);
    ctr_next     = ctr;
    new_angle    = cur_angle;
    x_new        = x;
    y_new        = y;
    y_trunc      = 18'b0;
    out_angle    = 16'b0;
    ready        = 1'b0;
    case (state)
    S0: begin
        state_next = (update) ? INIT : S0;
        ctr_next   = 5'b0;
    end
    INIT: begin
        state_next = COMPUTE;
        new_angle  = 18'b0;
        x_new      = `AG_CONST;
        y_new      = 18'b0;
        ctr_next   = 5'b0;
    end
    COMPUTE: begin
        state_next = (ctr < 5'h10) ? COMPUTE : DONE; 
        if ($signed(target_angle) > $signed(cur_angle)) begin
            x_new     = x - (y >>> ctr);
            y_new     = y + (x >>> ctr);
            new_angle = cur_angle + fix_angle(ctr); 
        end else begin
            x_new     = x + (y >>> ctr);
            y_new     = y - (x >>> ctr);
            new_angle = cur_angle - fix_angle(ctr); 
        end
        //$display("%t: (%x)", $time, (quadrant(in_angle) < 2) ?  {y[17], y[15:1]} 
        //                                                     : -{y[17], y[15:1]});
        ctr_next = ctr + 5'h1;
    end
    DONE: begin
        state_next = (update) ? INIT : DONE;
        y_trunc    = (quadrant(in_angle) < 2) ? ( y) >>> 1
                                              : (-y) >>> 1;
        out_angle  = y_trunc[15:0];
        y_new      = y;
        ready      = 1'b1;
    end
    endcase
end

endmodule
