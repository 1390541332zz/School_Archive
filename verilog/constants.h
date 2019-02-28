`ifndef DDSTOP_H
`define DDSTOP_H
localparam [17:0] FIX_SHIFT  = 18'd15;
localparam [31:0] __AG_CONST = $rtoi(1 / 1.6467602578655 * (2.0 ** FIX_SHIFT));
localparam [31:0] __PI2      = $rtoi($atan(1.0) * 2.0 * (2 ** FIX_SHIFT));
localparam [17:0] AG_CONST   = __AG_CONST[17:0];
localparam [17:0] PI2        = __PI2[17:0];
`endif
