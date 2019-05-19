/*---------------------------------------------------------------------------*
 * Module: Gameboy DMG                                                       *
 * Purpose: Core Module for an implementation of the original GameBoy DMG.   *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

import gb_intf::cntrlr_data;

module gb(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input clk,
    st_data.source display_out,
    input cntrlr_data    cntrlr_in
//    gb_mbc_intf.master mbc
);

bit 
    init_mode;
bit []

/*---------------------------------------------------------------------------*/
/*                                Submodules                                 */
/*---------------------------------------------------------------------------*/

dualport_ram #(
    .DATA_SIZE(128),
    .DATA_WIDTH(8)
) cpu_ram (
   .clk    (clk  ),
   .we     (     ),
   .addr_a (     ),
   .addr_b (     ),
   .din_a  (     ),
   .dout_a (     ),
   .dout_b (     )
);

gb_mem_map mm (
    .clk       (clk      ), 
    .init_mode (init_mode),
    .rom_bank  (         ),
    .ram_bank  (         ),
    .addr_gb   (         ),
    .addr_real (         )
);

gb_alu alu ();

endmodule : gb
