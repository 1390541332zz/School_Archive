/*---------------------------------------------------------------------------*
 * Module: Ball Driver                                                       *
 * Purpose: Object Controller for the Bouncing Ball Animation                *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module ball_driver #(
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

wire [h_width - 1:0]
    h_pos_next,
    x_next;
wire [v_width - 1:0]
    v_pos_next,
    y_next;
reg 
    h_vec,
    v_vec;
wire
    h_vec_next,
    v_vec_next;
wire
    bounce_x,
    bounce_y;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

assign x_next     = (h_vec) ? h_pos + 1 : h_pos - 1;
assign y_next     = (v_vec) ? v_pos + 1 : v_pos - 1;

assign h_pos_next = (move) ? x_next : h_pos;
assign v_pos_next = (move) ? y_next : v_pos;

/* verilator lint_off WIDTH */
assign bounce_x   = (  (x_next <= ball_radius)
                    || (x_next >= (width - ball_radius)));
assign bounce_y   = (  (y_next <= ball_radius)
                    || (y_next >= (height - ball_radius)));
/* verilator lint_on WIDTH */

assign h_vec_next = (move && bounce_x) ? (~h_vec) : h_vec; 
assign v_vec_next = (move && bounce_y) ? (~v_vec) : v_vec; 

always @(posedge clk) begin
    h_pos <= (reset) ? init_x[h_width - 1 : 0] : h_pos_next;
    v_pos <= (reset) ? init_y[v_width - 1 : 0] : v_pos_next;
    h_vec <= (reset) ? init_vec_x[0]           : h_vec_next;
    v_vec <= (reset) ? init_vec_y[0]           : v_vec_next;
end

endmodule
