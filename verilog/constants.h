`ifndef DDSTOP_H
`define DDSTOP_H
localparam [15:0] FIX_SHIFT = 15;
localparam [15:0] AG_CONST  = shortint'($rtoi(1 / 1.6467602578655) << FIX_SHIFT);
localparam [15:0] PI2       = shortint'($rtoi($atan(1.0) * 2.0) << FIX_SHIFT);
`endif
