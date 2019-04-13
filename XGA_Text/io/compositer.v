/*---------------------------------------------------------------------------*
 * Module: Compositer                                                        *
 * Purpose: Compositor to merge multiple RGBA layers into a single RGB layer *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module compositor #(
    parameter color_depth,
    parameter num_of_layers
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input                                clk,
    input      [(color_depth * 4) - 1:0] rgba_in [num_of_layers - 1:0],
    output reg [(color_depth * 3) - 1:0] rgb_out
);


/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

genvar i;

always @(*) for (i = 0; i < num_of_layers; i = i + 1) begin:layer_select
    if (rgba_in[i][color_depth-1:0] == { color_depth {1'b1} }) begin
        rgb_out = rgba_in[i][(color_depth * 4) - 1 : color_depth - 1];
    end
end

endmodule
