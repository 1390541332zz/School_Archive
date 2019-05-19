/*---------------------------------------------------------------------------*
 * Module: XGA Graphics                                                      *
 * Purpose: Top Level Module for an XGA bouncing ball screensaver graphic    *
 * Last Edit: 2019-04-02                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module XGA_Graphics(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire       CLOCK_50,
    input  wire [3:0] KEY,
    output wire [9:0] LEDR,
    output wire [7:0] VGA_R,
    output wire [7:0] VGA_G,
    output wire [7:0] VGA_B,
    output wire       VGA_CLK,
    output wire       VGA_BLANK_N,
    output wire       VGA_SYNC_N,
    output wire       VGA_HS,
    output wire       VGA_VS
);

localparam 
    ball_radius = 16,
    width       = 1024, 
    height      = 768,
    color_depth = 8,
    mask_width  = ball_radius * 2;

localparam [(color_depth * 3) - 1:0]
    RED  = 24'hFF0000,
    BLUE = 24'h0000FF;

wire
    reset,
    refresh,
    clk_75;
wire [log2(width) - 1:0]
    x_pixel,
    h_pos;
wire [log2(height) - 1:0]
    y_pixel,
    v_pos;
wire [23:0]
    rgb;
reg 
    initial_reset;

/*---------------------------------------------------------------------------*/
/*                                Computation                                */
/*---------------------------------------------------------------------------*/

assign reset = ~KEY[0] || initial_reset;

initial begin
    initial_reset <= 1'b1;
end

always @(posedge clk_75) begin
    initial_reset <= 1'b0;
end

/*---------------------------------------------------------------------------*/
/*                                 Submodules                                */
/*---------------------------------------------------------------------------*/

altpll_75 pll(
    .refclk(CLOCK_50),
    .rst(1'b0),
    .outclk_0(clk_75),
    .locked(LEDR[0])
);

vga_driver #(
    .vga_width(width),
    .vga_height(height),
    .color_depth( 8),
    /* Horizontal Timing Properties */
    .h_front_cnt(24),
    .h_sync_cnt(136),
    .h_back_cnt(144),
    .pixel_cnt(   1),
    /* Vertical Timing Properties */
    .v_front_cnt( 3),
    .v_sync_cnt(  6),
    .v_back_cnt( 29),
    .frame_cnt(   1)
) xga (
    .clk(clk_75),        
    .reset(reset),        
    .rgb_in(rgb),
    .vga_r_out(VGA_R),
    .vga_g_out(VGA_G),
    .vga_b_out(VGA_B),
    .vga_clk(VGA_CLK),
    .vga_blank_n(VGA_BLANK_N),
    .vga_sync_n(VGA_SYNC_N),
    .vga_hs(VGA_HS),
    .vga_vs(VGA_VS),
    .x_pixel(x_pixel),
    .y_pixel(y_pixel),
    .refresh(refresh)
);

//assign refresh = (y_pixel == 760) && (x_pixel == 1020);

ball_render #(
    .width(width),
    .height(height),
    .color_depth(color_depth),
    .ball_radius(ball_radius),
    .bkg_color(BLUE),
    .ball_color(RED)
) render (
    .clk(clk_75),
    .reset(reset),        
    .move(refresh),
    .h_pos(h_pos),
    .x_pixel(x_pixel),
    .v_pos(v_pos),
    .y_pixel(y_pixel),
    .rgb(rgb)
);

ball_driver #(
    .width(width),
    .height(height),
    .init_x(width  / 2),
    .init_y(height / 2),
    .init_vec_x(1),
    .init_vec_y(1),
    .ball_radius(ball_radius)
) ball (
    .clk(clk_75),
    .reset(reset),        
    .move(refresh),
    .h_pos(h_pos),
    .v_pos(v_pos)
);

endmodule
