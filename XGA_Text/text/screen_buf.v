/*---------------------------------------------------------------------------*
 * Module: Screen Buffer                                                     *
 * Purpose: Stores the current screen frame and allows writes to the next    *
 *     upcoming frame                                                        *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module screen_buf #(
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

`define POS(X, Y) (((Y) << log2(width)) + (X))

/*---------------------------------------------------------------------------*/
/*                                Submodules                                 */
/*---------------------------------------------------------------------------*/
dual_port_ram_sync #(
    .ADDR_WIDTH(log2(height * width)),
    .DATA_WIDTH(char_width)
) buf_a (
    .clk(clk),
    .we(write_en),
    /* verilator lint_off WIDTH */
    .addr_a(`POS(x_w, y_w)),
    .addr_b(`POS(x_r, y_r)),
    /* verilator lint_on WIDTH */
    .din_a(c_in),
    /* verilator lint_off PINCONNECTEMPTY */
    .dout_a(),
    /* verilator lint_on PINCONNECTEMPTY */
    .dout_b(c_out)
);

endmodule
