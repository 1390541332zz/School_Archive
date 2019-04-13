/*---------------------------------------------------------------------------*
 * Module: VGA Driver                                                        *
 * Purpose: Drives VGA Output Signal and Supplies Coordinates                *
 * Configuration: Supply the correct Clock and Display Parameters as         *
 *      outlined in the VESA Guidelines for Display Monitor Timing.          *
 * Last Edit: 2019-04-02                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module vga_driver #(
/*---------------------------------------------------------------------------*/
/*                            Module Templating                              */
/*---------------------------------------------------------------------------*/
    /* Display Properties */
    parameter vga_width   = 1024,
    parameter vga_height  = 768,
    parameter color_depth = 8,

    /* Horizontal Timing Properties */
    parameter h_front_cnt = 24,
    parameter h_sync_cnt  = 136,
    parameter h_back_cnt  = 144,
    parameter pixel_cnt   = 1,
    
    /* Vertical Timing Properties */
    parameter v_front_cnt = 3,
    parameter v_sync_cnt  = 6,
    parameter v_back_cnt  = 29,
    parameter frame_cnt   = 1,
    
    parameter h_addr_cnt  = pixel_cnt * vga_width,
    parameter v_addr_cnt  = frame_cnt * vga_height,
    
    /* Horizontal Timing Triggers */
    parameter h_addr_start  = 0,
    parameter h_front_start = h_addr_start  + h_addr_cnt,
    parameter h_sync_start  = h_front_start + h_front_cnt, 
    parameter h_back_start  = h_sync_start  + h_sync_cnt,
    parameter h_cnt         = h_back_start  + h_back_cnt,
    
    /* Vertical Timing Triggers */
    parameter v_addr_start  = 0,
    parameter v_front_start = v_addr_start  + v_addr_cnt,
    parameter v_sync_start  = v_front_start + v_front_cnt, 
    parameter v_back_start  = v_sync_start  + v_sync_cnt,
    parameter v_cnt         = v_back_start  + v_back_cnt
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire                           clk,             
    input  wire                           reset,             
    input  wire [(color_depth * 3) - 1:0] rgb_in,
    output wire [color_depth - 1:0]       vga_r_out,
    output wire [color_depth - 1:0]       vga_g_out,
    output wire [color_depth - 1:0]       vga_b_out,
    output wire                           vga_clk,
    output wire                           vga_blank_n,
    output wire                           vga_sync_n,
    output wire                           vga_hs,
    output wire                           vga_vs,
    output wire [log2(vga_width) - 1:0]   x_pixel,
    output wire [log2(vga_height) - 1:0]  y_pixel,
    output wire                           refresh
);


reg 
    back_last;
reg [log2(h_cnt) - 1:0]
    ctr_h;
reg [log2(v_cnt) - 1:0]
    ctr_v;
wire [log2(h_cnt) - 1:0]
    ctr_h_next;
wire [log2(v_cnt) - 1:0]
    ctr_v_next;
wire
    /* Horizontal Ticks */
    h_addr,
//  h_front,
    h_sync,
    h_back,

    /* Vertical Ticks */
    v_addr,
//  v_front,
    v_sync,
    v_back;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

assign h_addr      = (ctr_h >= h_addr_start ) && (ctr_h < h_front_start);
assign v_addr      = (ctr_v >= v_addr_start ) && (ctr_v < v_front_start);
//assign h_front   = (ctr_h >= h_front_start) && (ctr_h < h_sync_start );
//assign v_front   = (ctr_v >= v_front_start) && (ctr_v < v_sync_start );
assign h_sync      = (ctr_h >= h_sync_start ) && (ctr_h < h_back_start );
assign v_sync      = (ctr_v >= v_sync_start ) && (ctr_v < v_back_start );
assign h_back      = (ctr_h >= h_back_start ) && (ctr_h < h_cnt        );
assign v_back      = (ctr_v >= v_back_start ) && (ctr_v < v_cnt        );
assign vga_clk     = clk;
assign vga_blank_n = v_addr & h_addr;
assign vga_hs      = h_sync;
assign vga_vs      = v_sync;
assign vga_sync_n  = vga_hs ~^ vga_vs;

assign x_pixel     = ctr_h[log2(vga_width) - 1:0];
assign y_pixel     = ctr_v[log2(vga_height) - 1:0];

assign ctr_h_next  = ctr_h + 1;
assign ctr_v_next  = ctr_v;

assign {vga_r_out, 
        vga_g_out, 
        vga_b_out} = vga_blank_n ? rgb_in : 0;

assign refresh     = ~back_last & h_back & v_back;

always @(posedge clk) if (reset) begin
    ctr_h     <= 0;
    ctr_v     <= 0;
    back_last <= 0;
end else begin
    ctr_h     <= (ctr_h_next < h_cnt)     ? ctr_h_next 
                                          : 0;
    ctr_v     <= (ctr_h_next < h_cnt)     ? ctr_v_next
               : (ctr_v_next + 1 < v_cnt) ? ctr_v_next + 1
                                          : 0;
    back_last <= h_back & v_back;
end

endmodule
