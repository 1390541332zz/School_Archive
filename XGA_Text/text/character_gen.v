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

localparam
    x1 = 1664525,
    x2 = 1013904223,
    x3 = (2 << 32) - 1;

wire [31:0] 
    rand_r_next;
reg [31:0]
    rand_r;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

assign rand_r_next = (x1 * rand_r + x2) & x3;
assign c_out       = rand_r[char_width - 1:0] & (2 << log2(num_of_chars));

always @(posedge clk) begin
    rand_r = (reset) ? 0 : rand_r_next;
end

endmodule
