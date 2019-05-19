/*---------------------------------------------------------------------------*
 * Module: Ball Renderer                                                     *
 * Purpose: Frame Painter for the Bouncing Ball Animation                    *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module ball_render #(
/*---------------------------------------------------------------------------*/
/*                            Module Templating                              */
/*---------------------------------------------------------------------------*/
    parameter                             width,
    parameter                             height,
    parameter                             color_depth,
    parameter                             ball_radius,
    parameter [(color_depth * 4) - 1 : 0] bkg_color,
    parameter [(color_depth * 4) - 1 : 0] ball_color
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire                             clk,
    input  wire                             reset,        
    input  wire                             ball_en,        
    input  wire                             move,
    input  wire [log2(width ) - 1:0]        h_pos, x_pixel,
    input  wire [log2(height) - 1:0]        v_pos, y_pixel,
    output wire [(color_depth * 4) - 1 : 0] rgba_out
);

localparam 
    mask_width = ball_radius * 2;

wire [log2(width) - 1 : 0]
    x_min,
    x_max;
wire [log2(height) - 1 : 0]
    y_min,
    y_max;
wire [log2(mask_width) - 1 : 0] 
    mask_x,
    mask_y;
wire [mask_width - 1 : 0] 
    mask;
wire
    in_bounds;


/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

/* verilator lint_off WIDTH */
assign x_min = h_pos - ball_radius;
assign x_max = h_pos + ball_radius;
assign y_min = v_pos - ball_radius;
assign y_max = v_pos + ball_radius;

assign in_bounds = (  (x_pixel >= x_min) && (x_pixel <= x_max)  
                   && (y_pixel >= y_min) && (y_pixel <= y_max));

assign mask_x = (in_bounds) ? (x_pixel - x_min) : { log2(mask_width) {1'b0} };
assign mask_y = (in_bounds) ? (y_pixel - y_min) : { log2(mask_width) {1'b0} };
/* verilator lint_on  WIDTH */

assign rgba_out = (mask[mask_x] && in_bounds && ball_en) ? ball_color 
                                                         : bkg_color;

always @(*) case (mask_y)
    5'h00: mask = 32'b00000000000011111111000000000000;
    5'h01: mask = 32'b00000000011111111111111000000000;
    5'h02: mask = 32'b00000000111111111111111100000000;
    5'h03: mask = 32'b00000011111111111111111111000000;
    5'h04: mask = 32'b00000111111111111111111111100000;
    5'h05: mask = 32'b00001111111111111111111111110000;
    5'h06: mask = 32'b00011111111111111111111111111000;
    5'h07: mask = 32'b00011111111111111111111111111000;
    5'h08: mask = 32'b00111111111111111111111111111100;
    5'h09: mask = 32'b01111111111111111111111111111110;
    5'h0a: mask = 32'b01111111111111111111111111111110;
    5'h0b: mask = 32'b01111111111111111111111111111110;
    5'h0c: mask = 32'b11111111111111111111111111111111;
    5'h0d: mask = 32'b11111111111111111111111111111111;
    5'h0e: mask = 32'b11111111111111111111111111111111;
    5'h0f: mask = 32'b11111111111111111111111111111111;
    5'h10: mask = 32'b11111111111111111111111111111111;
    5'h11: mask = 32'b11111111111111111111111111111111;
    5'h12: mask = 32'b11111111111111111111111111111111;
    5'h13: mask = 32'b11111111111111111111111111111111;
    5'h14: mask = 32'b01111111111111111111111111111110;
    5'h15: mask = 32'b01111111111111111111111111111110;
    5'h16: mask = 32'b01111111111111111111111111111110;
    5'h17: mask = 32'b00111111111111111111111111111100;
    5'h18: mask = 32'b00011111111111111111111111111000;
    5'h19: mask = 32'b00011111111111111111111111111000;
    5'h1a: mask = 32'b00001111111111111111111111110000;
    5'h1b: mask = 32'b00000111111111111111111111100000;
    5'h1c: mask = 32'b00000011111111111111111111000000;
    5'h1d: mask = 32'b00000000111111111111111100000000;
    5'h1e: mask = 32'b00000000011111111111111000000000;
    5'h1f: mask = 32'b00000000000011111111000000000000;
endcase

endmodule
