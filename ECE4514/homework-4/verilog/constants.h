`ifndef DDSTOP_H
`define DDSTOP_H
/* verilator lint_off WIDTH */
localparam [17:0] FIX_SHIFT  = 18'd15;
localparam [31:0] __AG_CONST = $rtoi(1 / 1.6467602578655 * (2.0 ** FIX_SHIFT));
localparam [31:0] __PI2      = $rtoi($atan(1.0) * 2.0 * (2 ** FIX_SHIFT));
localparam [17:0] AG_CONST   = __AG_CONST[17:0];
localparam [17:0] PI2        = __PI2[17:0];
localparam [31:0] 
    ANGLE_00 = $rtoi(0.7853981633974483 * (2 ** FIX_SHIFT)),
    ANGLE_01 = $rtoi(0.4636476090008061 * (2 ** FIX_SHIFT)),
    ANGLE_02 = $rtoi(0.2449786631268641 * (2 ** FIX_SHIFT)),
    ANGLE_03 = $rtoi(0.1243549945467614 * (2 ** FIX_SHIFT)),
    ANGLE_04 = $rtoi(0.0624188099959574 * (2 ** FIX_SHIFT)),
    ANGLE_05 = $rtoi(0.0312398334302683 * (2 ** FIX_SHIFT)),
    ANGLE_06 = $rtoi(0.0156237286204768 * (2 ** FIX_SHIFT)),
    ANGLE_07 = $rtoi(0.0078123410601011 * (2 ** FIX_SHIFT)),
    ANGLE_08 = $rtoi(0.0039062301319670 * (2 ** FIX_SHIFT)),
    ANGLE_09 = $rtoi(0.0019531225164788 * (2 ** FIX_SHIFT)),
    ANGLE_0A = $rtoi(0.0009765621895593 * (2 ** FIX_SHIFT)),
    ANGLE_0B = $rtoi(0.0004882812111949 * (2 ** FIX_SHIFT)),
    ANGLE_0C = $rtoi(0.0002441406201494 * (2 ** FIX_SHIFT)),
    ANGLE_0D = $rtoi(0.0001220703118937 * (2 ** FIX_SHIFT)),
    ANGLE_0E = $rtoi(0.0000610351561742 * (2 ** FIX_SHIFT)),
    ANGLE_0F = $rtoi(0.0000305175781155 * (2 ** FIX_SHIFT)),
    ANGLE_10 = $rtoi(0.0000152587890613 * (2 ** FIX_SHIFT)),
    ANGLE_11 = $rtoi(0.0000076293945311 * (2 ** FIX_SHIFT)),
    ANGLE_12 = $rtoi(0.0000038146972656 * (2 ** FIX_SHIFT));
/* verilator lint_on WIDTH */
`endif
