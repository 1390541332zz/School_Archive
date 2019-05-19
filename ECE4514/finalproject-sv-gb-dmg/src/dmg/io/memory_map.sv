/*---------------------------------------------------------------------------*
 * Module: Gameboy DMG Internal Memory Map                                   *
 * Purpose: Routes all requests on the data bus to their proper location.    *
 *     ROM and RAM are outside the DMG however internal RAM and IO Registers *
 *     are within the DMG.                                                   *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

module gb_mem_map(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  bit        clk, 
    input  bit        init_mode,
    input  bit [ 5:0] rom_bank,
    input  bit [ 3:0] ram_bank,
    input  bit [ 7:0] addr_gb,
    output bit [16:0] addr_real
);

/*---------------------------------------------------------------------------*/
/*                               Computation                                 */
/*---------------------------------------------------------------------------*/

assign addr_real = ((addr_gb <  8'h0100) && init_mode) ? addr_gb + 16'h0701_0000
                 : ( addr_gb <  8'h4000 )              ? addr_gb + 16'h0400_0000
                 : ( addr_gb <  8'h8000 )              ? addr_gb + 16'h0400_4000 + 16'h4000 * rom_bank
                 : ( addr_gb <  8'hA000 )              ? addr_gb + 16'h0000_8000
                 : ( addr_gb <  8'hC000 )              ? addr_gb + 16'h0000_A000 + 16'h2000 * ram_bank
                 : ( addr_gb <  8'hD000 )              ? addr_gb + 16'h0001_0000
                 : ( addr_gb <  8'hE000 )              ? addr_gb + 16'h0001_1000
                 : ( addr_gb <  8'hFE00 )              ? addr_gb + 16'h0001_0000
                 : ( addr_gb <  8'hFEA0 )              ? addr_gb + 16'h0001_2000
                 : ( addr_gb <  8'hFF00 )              ? addr_gb + 16'hFFFF_FFFF
                 : ( addr_gb <  8'hFF80 )              ? addr_gb + 16'hFFFF_FFFE
                 : ( addr_gb <  8'hFFFF )              ? addr_gb + 16'hFFFF_FFFF
                  /* addr_gb == 8'hFFF */              : addr_gb + 16'hFFFF_FFFE;

endmodule : gb_mem_map
