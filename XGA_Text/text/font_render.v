/*---------------------------------------------------------------------------*
 * Module: Font Renderer                                                     *
 * Purpose: Draws the upcoming text frame layer from the screen buffer       *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module font_render #(
/*---------------------------------------------------------------------------*/
/*                            Module Templating                              */
/*---------------------------------------------------------------------------*/
    parameter width,
    parameter height,
    parameter text_th_w,
    parameter text_th_h,
    parameter char_width,
    parameter bkg_color,
    parameter text_color
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire                          clk,
    input  wire                          reset,        
    input  wire                          refresh,
    input  wire [log2(width ) - 1:0]     x_pixel,
    input  wire [log2(height) - 1:0]     y_pixel,
    input  wire [char_width - 1:0]       cur_char,
    output wire [(char_width * 4) - 1:0] rgba_out
);

wire [log2(text_th_w) - 1:0]
    x_font_pos;
wire [text_th_w - 1:0]
    font_slice;
wire [log2(text_th_h) - 1:0]
    y_font_pos;
wire [(char_width + log2(text_th_h)) - 2:0]
    font_addr;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

assign x_font_pos = x_pixel[log2(text_th_w) - 1:0];
assign y_font_pos = y_pixel[log2(text_th_h) - 1:0];

assign font_addr  = {cur_char[char_width - 2:0], y_font_pos};
assign rgba_out   = (font_slice[x_font_pos]) ? text_color : bkg_color;

/*---------------------------------------------------------------------------*/
/*                                Submodules                                 */
/*---------------------------------------------------------------------------*/

font_rom font (
    .clk(clk),
    .addr(font_addr),
    .data(font_slice)
);

endmodule
