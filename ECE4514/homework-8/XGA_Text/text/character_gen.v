/*---------------------------------------------------------------------------*
 * Module: Random Character Generator                                        *
 * Purpose: Generates a random character.                                    *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module character_gen #(
/*---------------------------------------------------------------------------*/
/*                            Module Templating                              */
/*---------------------------------------------------------------------------*/
    parameter char_width,
    parameter num_of_chars
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire                      clk,
    input  wire                      reset, 
    output wire [char_width - 1:0]   c_out
);

localparam [63:0]
    x1        = 64'd1664525,
    x2        = 64'd10139041,
    xmod      = (64'd1 << 64'd32) - 64'd1,
    rand_seed = 64'd0;

wire [63:0] 
    rand_r_next;
reg [63:0]
    rand_r;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

assign rand_r_next = (x1 * rand_r + x2) & xmod;
assign c_out       = {1'b0, rand_r[char_width - 2:0]};

initial begin
    rand_r = rand_seed;
end

always @(posedge clk) begin
    rand_r = (reset) ? rand_seed : rand_r_next;
end

endmodule
