/*---------------------------------------------------------------------------*
 * Module: Screen Buffer                                                     *
 * Purpose: Stores the current screen frame and allows writes to the next    *
 *     upcoming frame                                                        *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module screen_buff(
/*---------------------------------------------------------------------------*/
/*                            Module Templating                              */
/*---------------------------------------------------------------------------*/
    parameter width,
    parameter height,
    parameter char_width
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire                      clk,
    input  wire                      reset,        
    input  wire                      refresh,
    input  wire                      write_en,
    input  wire [log2(width ) - 1:0] x_w,
    input  wire [log2(height) - 1:0] y_w,
    input  wire [log2(width ) - 1:0] x_r,
    input  wire [log2(height) - 1:0] y_r,
    input  wire [char_width - 1:0]   c_in,
    output wire [char_width - 1:0]   c_out
);

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

endmodule
