/*---------------------------------------------------------------------------*
 * Module: Random Character Generator                                        *
 * Purpose: Generates a random character.                                    *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module character_gen(
/*---------------------------------------------------------------------------*/
/*                            Module Templating                              */
/*---------------------------------------------------------------------------*/
    parameter char_width,
    parameter char_min,
    parameter char_max
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire                      clk,
    input  wire                      reset,        
    output wire [char_width - 1:0]   c_out
);

localparam
    legal_char_width = log2(char_max - char_min),
    x1               = 1664525,
    x2               = 1013904223,
    x3               = (2 << 32) - 1;

wire [31:0] 
    rand_next;
reg [31:0]
    rand;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

assign rand_next = (x1 * rand + x2) & x3;
assign c_out     = rand[legal_char_width - 1:0] + char_min;

always @(posedge clk) begin
    rand = (reset) ? 0 : rand_next;
end

endmodule
