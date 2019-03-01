module cordicsine(
    input  wire        clk,
    input  wire        reset,
    input  wire        update,
    input  wire [17:0] in_angle,
    output reg         ready,
    output reg  [15:0] out_angle
);

`include "constants.h"

//localparam [31:0] 
//    ANGLE_00 = $rtoi(0.7853981633974483 * (2 ** FIX_SHIFT)),
//    ANGLE_01 = $rtoi(0.4636476090008061 * (2 ** FIX_SHIFT)),
//    ANGLE_02 = $rtoi(0.2449786631268641 * (2 ** FIX_SHIFT)),
//    ANGLE_03 = $rtoi(0.1243549945467614 * (2 ** FIX_SHIFT)),
//    ANGLE_04 = $rtoi(0.0624188099959574 * (2 ** FIX_SHIFT)),
//    ANGLE_05 = $rtoi(0.0312398334302683 * (2 ** FIX_SHIFT)),
//    ANGLE_06 = $rtoi(0.0156237286204768 * (2 ** FIX_SHIFT)),
//    ANGLE_07 = $rtoi(0.0078123410601011 * (2 ** FIX_SHIFT)),
//    ANGLE_08 = $rtoi(0.0039062301319670 * (2 ** FIX_SHIFT)),
//    ANGLE_09 = $rtoi(0.0019531225164788 * (2 ** FIX_SHIFT)),
//    ANGLE_0A = $rtoi(0.0009765621895593 * (2 ** FIX_SHIFT)),
//    ANGLE_0B = $rtoi(0.0004882812111949 * (2 ** FIX_SHIFT)),
//    ANGLE_0C = $rtoi(0.0002441406201494 * (2 ** FIX_SHIFT)),
//    ANGLE_0D = $rtoi(0.0001220703118937 * (2 ** FIX_SHIFT)),
//    ANGLE_0E = $rtoi(0.0000610351561742 * (2 ** FIX_SHIFT)),
//    ANGLE_0F = $rtoi(0.0000305175781155 * (2 ** FIX_SHIFT)),
//    ANGLE_10 = $rtoi(0.0000152587890613 * (2 ** FIX_SHIFT)),
//    ANGLE_11 = $rtoi(0.0000076293945311 * (2 ** FIX_SHIFT)),
//    ANGLE_12 = $rtoi(0.0000038146972656 * (2 ** FIX_SHIFT));

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
 *   if (inangle > 4*PI2) 
 *     inangle = inangle - 4*PI2;
 * 
 *   if (inangle > 3*PI2)
 *     return 3;
 *   else if (inangle > 2*PI2)
 *     return 2;
 *   else if (inangle > PI2)
 *     return 1;
 * 
 *   return 0;
 * }
 */

function [17:0] quadrant;
input [17:0] 
    in_angle;
reg [17:0] 
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

/*
 * fixed angleadj(fixed inangle) {
 * 
 *   // input angle is 0 .. 3pi
 *   // output angle in first quadrant such that
 *   // abs(sin(inangle)) = sin(outangle)
 * 
 *   // if inangle >2pi, subtract 2pi.
 *   // This brings inangle in the range 0 - pi and keeps the same quardrant
 *   if (inangle > 4*PI2) 
 *     inangle = inangle - 4*PI2;
 * 
 *   if (inangle > 3*PI2)
 *     return (4*PI2 - inangle);
 *   else if (inangle > 2*PI2)
 *     return (inangle - 2*PI2);
 *   else if (inangle > PI2)
 *     return (2*PI2 - inangle);
 * 
 *   return inangle;
 * }
 */

function [17:0] angleadj;
input [17:0] 
    in_angle;
reg [17:0] 
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


reg [17:0]
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
    ctr, ctr_next;

//---------------------------------------------------------------------------//

always @(posedge clk) case (ctr_next)
    5'h00: fix_angle <= 18'h6487; // ANGLE_00[17:0]; 
    5'h01: fix_angle <= 18'h3b58; // ANGLE_01[17:0];
    5'h02: fix_angle <= 18'h1f5b; // ANGLE_02[17:0];
    5'h03: fix_angle <= 18'hfea ; // ANGLE_03[17:0];
    5'h04: fix_angle <= 18'h7fd ; // ANGLE_04[17:0];
    5'h05: fix_angle <= 18'h3ff ; // ANGLE_05[17:0];
    5'h06: fix_angle <= 18'h1ff ; // ANGLE_06[17:0];
    5'h07: fix_angle <= 18'hff  ; // ANGLE_07[17:0];
    5'h08: fix_angle <= 18'h7f  ; // ANGLE_08[17:0];
    5'h09: fix_angle <= 18'h3f  ; // ANGLE_09[17:0];
    5'h0A: fix_angle <= 18'h1f  ; // ANGLE_0A[17:0];
    5'h0B: fix_angle <= 18'hf   ; // ANGLE_0B[17:0];
    5'h0C: fix_angle <= 18'h7   ; // ANGLE_0C[17:0];
    5'h0D: fix_angle <= 18'h3   ; // ANGLE_0D[17:0];
    5'h0E: fix_angle <= 18'h1   ; // ANGLE_0E[17:0];
    5'h0F: fix_angle <= 18'h0   ; // ANGLE_0F[17:0];
    5'h10: fix_angle <= 18'h0   ; // ANGLE_10[17:0];
    5'h11: fix_angle <= 18'h0   ; // ANGLE_11[17:0];
    5'h12: fix_angle <= 18'h0   ; // ANGLE_12[17:0];
    default: fix_angle <= 18'h0;
endcase

//---------------------------------------------------------------------------//

/*
 * fixed cordicsine(fixed inangle) {
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
    ready        = 1'b0;
    target_angle = angleadj(in_angle);
    case (state)
    S0: begin
        state_next = (update) ? INIT : S0;
        ctr_next   = 0;
    end
    INIT: begin
        state_next = COMPUTE;
        new_angle  = 0;
        x_new      = AG_CONST;
        y_new      = 0;
        ctr_next   = 0;
    end
    COMPUTE: begin
        state_next = (ctr < 5'h10) ? COMPUTE : DONE; 
        if (target_angle > cur_angle) begin
            x_new     = x - (y >>> ctr);
            y_new     = y + (x >>> ctr);
            new_angle = cur_angle + fix_angle; 
        end else begin
            x_new     = x + (y >>> ctr);
            y_new     = y - (x >>> ctr);
            new_angle = cur_angle - fix_angle; 
        end
        //$display("%t: (%x)", $time, (quadrant(in_angle) < 2) ?  {y[17], y[15:1]} 
        //                                                     : -{y[17], y[15:1]});
        ctr_next = ctr + 1;
    end
    DONE: begin
        ready      = 1'b1;
        state_next = (update) ? INIT : DONE;
        out_angle  = (quadrant(in_angle) < 2) ?  {y[17], y[15:1]} 
                                              : -{y[17], y[15:1]};
        y_new      = y;
    end
    endcase
end

endmodule
