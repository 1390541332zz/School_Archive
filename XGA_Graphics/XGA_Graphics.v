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

`define MASK_W ((mask_width ** 2) - 1)
`define MASK_POS(V, H) (((V) << log2(mask_width)) + (H))

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
wire [`MASK_W : 0] 
    mask;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/


/* verilator lint_off WIDTH */

function [`MASK_W : 0] ball_mask(
    input integer ball_rad
); 
reg [log2(width) : 0]
    x;
reg [log2(height) : 0]
    y;
reg [`MASK_W : 0]
    b_mask;
begin
    b_mask = 1;
    ball_mask = 0;
    ball_rad = (ball_rad << 1) + 1;
    for(y = 0; y < ball_rad; y = y + 1) begin
    for(x = 0; x < ball_rad; x = x + 1)
        if ((x ** 2 + y ** 2) <= (ball_rad ** 2)) begin
            ball_mask =  ball_mask | (b_mask << `MASK_POS(y >> 1, x >> 1));
        end else begin
            ball_mask = ball_mask;
        end
    end
end endfunction

/* verilator lint_on WIDTH */

assign reset = ~KEY[0];

assign mask = //ball_mask(ball_radius); 
    {
    32'b00000000000011111111000000000000,
    32'b00000000011111111111111000000000,
    32'b00000000111111111111111100000000,
    32'b00000011111111111111111111000000,
    32'b00000111111111111111111111100000,
    32'b00001111111111111111111111110000,
    32'b00011111111111111111111111111000,
    32'b00011111111111111111111111111000,
    32'b00111111111111111111111111111100,
    32'b01111111111111111111111111111110,
    32'b01111111111111111111111111111110,
    32'b01111111111111111111111111111110,
    32'b11111111111111111111111111111111,
    32'b11111111111111111111111111111111,
    32'b11111111111111111111111111111111,
    32'b11111111111111111111111111111111,
    32'b11111111111111111111111111111111,
    32'b11111111111111111111111111111111,
    32'b11111111111111111111111111111111,
    32'b11111111111111111111111111111111,
    32'b01111111111111111111111111111110,
    32'b01111111111111111111111111111110,
    32'b01111111111111111111111111111110,
    32'b00111111111111111111111111111100,
    32'b00011111111111111111111111111000,
    32'b00011111111111111111111111111000,
    32'b00001111111111111111111111110000,
    32'b00000111111111111111111111100000,
    32'b00000011111111111111111111000000,
    32'b00000000111111111111111100000000,
    32'b00000000011111111111111000000000,
    32'b00000000000011111111000000000000
};

assign rgb = mask[`MASK_POS(y_pixel - v_pos, x_pixel - h_pos)] ? RED : BLUE;

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

ball_gen #(
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
