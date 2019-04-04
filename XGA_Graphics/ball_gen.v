/*---------------------------------------------------------------------------*
 * Module: XGA Graphics                                                      *
 * Purpose: Top Level Module for an XGA bouncing ball screensaver graphic    *
 * Last Edit: 2019-04-02                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module ball_gen #(
/*---------------------------------------------------------------------------*/
/*                            Module Templating                              */
/*---------------------------------------------------------------------------*/
    parameter width,
    parameter height,
    parameter init_x,
    parameter init_y,
    parameter init_vec_x,
    parameter init_vec_y,
    parameter ball_radius
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire                     clk,
    input  wire                     reset,        
    input  wire                     move ,
    output reg [log2(width ) - 1:0] h_pos,
    output reg [log2(height) - 1:0] v_pos
);

localparam 
    h_width = log2(width),
    v_width = log2(height);
localparam [h_width - 1 : 0]
    x_init  = init_x[h_width - 1 : 0];
localparam [v_width - 1 : 0]
    y_init  = init_y[v_width - 1 : 0];

reg [h_width - 1:0]
    h_pos_next;
reg [v_width - 1:0]
    v_pos_next;
wire signed [h_width + 1:0]
    h_min,
    h_max;
wire signed [v_width + 1:0]
    v_min,
    v_max;
reg [1:0]
    h_vec,
    v_vec,
    h_vec_next,
    v_vec_next;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

/* verilator lint_off WIDTH */

assign h_min = $signed(h_pos) - $signed(ball_radius) + (h_vec * $signed(init_vec_x));
assign h_max = $signed(h_pos) + $signed(ball_radius) + (h_vec * $signed(init_vec_x));
assign v_min = $signed(v_pos) - $signed(ball_radius) + (v_vec * $signed(init_vec_y));
assign v_max = $signed(v_pos) + $signed(ball_radius) + (v_vec * $signed(init_vec_y));

always @(*) if (move & (h_min <= 0)) begin
    h_pos_next = 0;
    h_vec_next = 2'sh1;
end else if (move & (h_max >= (width - 1))) begin
    h_pos_next = width - 1;
    h_vec_next = -2'sh1;
end else if (move) begin
    h_pos_next = h_pos + (h_vec * $signed(init_vec_x));
    h_vec_next = h_vec;
end else begin
    h_pos_next = h_pos;
    h_vec_next = h_vec;
end

always @(*) if (move & (v_min <= 0)) begin
    v_pos_next = 0;
    v_vec_next = 2'sh1;
end else if (move & (v_max >= (height - 1))) begin
    v_pos_next = height - 1;
    v_vec_next = -2'sh1;
end else if (move) begin
    v_pos_next = v_pos + (v_vec * $signed(init_vec_y));
    v_vec_next = v_vec;
end else begin
    v_pos_next = v_pos;
    v_vec_next = v_vec;
end

/* verilator lint_on WIDTH */

always @(posedge clk) begin
    h_pos <= (reset) ? init_x[h_width - 1 : 0] : h_pos_next;
    v_pos <= (reset) ? init_y[v_width - 1 : 0] : v_pos_next;
    h_vec <= (reset) ? 2'sh1                   : h_vec_next;
    v_vec <= (reset) ? 2'sh1                   : v_vec_next;
end


endmodule
