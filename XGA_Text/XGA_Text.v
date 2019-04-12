/*---------------------------------------------------------------------------*
 * Module: XGA Text                                                          *
 * Purpose: Top Level Module for an XGA bouncing ball screensaver graphic    *
 *     with a randomised text background                                     *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module XGA_Text(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire       CLOCK_50,
    input  wire [3:0] KEY,
    output wire [7:0] VGA_R,
    output wire [7:0] VGA_G,
    output wire [7:0] VGA_B,
    output wire       VGA_CLK,
    output wire       VGA_BLANK_N,
    output wire       VGA_SYNC_N,
    output wire       VGA_HS,
    output wire       VGA_VS,
    input  wire [9:0] SW                                      
);

localparam 
    ball_en_default = 1'b0,
    num_of_layers   = 2,
    ball_radius     = 16,
    width           = 1024, 
    height          = 768,
    color_depth     = 8,
    mask_width      = ball_radius * 2;

localparam [(color_depth * 4) - 1:0]
    RED   = 24'hFF0000FF,
    GREEN = 24'h00FF00FF,
    BLACK = 24'h000000FF;

wire
    reset,
    fill_buffer,
    clear_buffer,
    toggle_ball,
    refresh,
    clk_75;
wire [log2(width) - 1:0]
    x_pixel,
    h_ball;
wire [log2(height) - 1:0]
    y_pixel,
    v_ball;
wire [(color_depth * 4) - 1:0]
    composite_rgb,
    text_rgb,
    ball_rgb;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

assign ball_en_next = ball_en ^ toggle_ball;

always @(posedge clk_75) begin
    ball_en <= (reset) ? ball_en_default : ball_en_next;
end

/*---------------------------------------------------------------------------*/
/*                            Control Submodules                             */
/*---------------------------------------------------------------------------*/

altpll_75 pll(
    .refclk(CLOCK_50),
    .rst(1'b0),
    .outclk_0(clk_75),
    .locked(LEDR[0])
);

keypressed key0(
    .clock(clk_75), 
    .reset(KEY[0]), 
    .enable_in(KEY[0]), 
    .enable_out(reset)
);
keypressed key1(
    .clock(clk_75), 
    .reset(KEY[0]), 
    .enable_in(KEY[1]), 
    .enable_out(fill_buffer)
);
keypressed key2(
    .clock(clk_75), 
    .reset(KEY[0]), 
    .enable_in(KEY[2]), 
    .enable_out(clear_buffer)
);
keypressed key3(
    .clock(clk_75), 
    .reset(KEY[0]), 
    .enable_in(KEY[3]), 
    .enable_out(toggle_ball)
);

/*---------------------------------------------------------------------------*/
/*                           Graphics Submodules                             */
/*---------------------------------------------------------------------------*/
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
    .rgb_in(composite_rgb),
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

//Top Layer is last in the array / first in the concatenation.
compositer #(
    .color_depth(color_depth),
    .num_of_layers(num_of_layers),
) comp (
    .clk(clk_75),
    .rgba_in('{
        ball_rgb, 
        text_rgb
    })
    .rgb_out(composite_rgb),
);

/*---------------------------------------------------------------------------*/
/*                          Text Logic Submodules                            */
/*---------------------------------------------------------------------------*/

font_render #(

) text_mask (

);

screen_buffer #(

) buffer (

);

character_gen #(

) char_gen (

);

/*---------------------------------------------------------------------------*/
/*                          Ball Logic Submodules                            */
/*---------------------------------------------------------------------------*/

ball_render #(
    .width(width),
    .height(height),
    .color_depth(color_depth),
    .ball_radius(ball_radius),
    .bkg_color(BLUE),
    .ball_color(RED)
) ball_mask (
    .clk(clk_75),
    .reset(reset),
    .visible(ball_en),
    .move(refresh),
    .h_pos(h_ball),
    .x_pixel(y_pixel),
    .v_pos(v_ball),
    .y_pixel(y_pixel),
    .rgb(ball_rgb)
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
    .h_pos(h_ball),
    .v_pos(v_ball)
);

endmodule
