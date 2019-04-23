/*---------------------------------------------------------------------------*
 * Module: Gameboy DMG                                                       *
 * Purpose: Top Level Module for an implementation of the original GameBoy   *
 *     DMG model for the DE1-SOC.                                            *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

import avalon_interface::*;

module gb_dmg(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/

    /* CLOCKS */
    input  bit         CLOCK_50,

    /* AUDIO */
    input  wire        AUD_DACLRCK,
    output wire        AUD_DACDAT,
    inout  wire        AUD_BCLK,
    inout  wire        I2C_SDAT,
    output wire        I2C_SCLK,

    /* VGA */
    output wire [7:0]  VGA_R,
    output wire [7:0]  VGA_G,
    output wire [7:0]  VGA_B,
    output wire        VGA_CLK,
    output wire        VGA_BLANK_N,
    output wire        VGA_SYNC_N,
    output wire        VGA_HS,
    output wire        VGA_VS,

    /* PS/2 */
    inout  wire        PS2_DAT,
    inout  wire        PS2_CLK,

    /* MICRO SD CARD */
    inout  wire        HPS_SD_CLK,
    inout  wire        HPS_SD_CMD,
    inout  wire        HPS_SD_DAT0,
    inout  wire        HPS_SD_DAT3,

    /* SDRAM */
    output wire [12:0] DRAM_ADDR,
    inout  wire [15:0] DRAM_DQ,
    output wire [1:0]  DRAM_BA,
    output wire [1:0]  DRAM_DQM,
    output wire        DRAM_RAS_N,
    output wire        DRAM_CAS_N,
    output wire        DRAM_CKE,
    output wire        DRAM_CLK,
    output wire        DRAM_WE_N,
    output wire        DRAM_CS_N,

    /* ONBOARD IO */
    input  bit  [1:0]  KEY,
    input  bit  [9:0]  SW,
    output bit  [1:0]  LEDR
);


logic
    hard_reset,
    hw_clk,
    sys_clk,
    vga_clk,
    dmg_double_clk,
    dmg_clk_,
    dmg_clk;

/*---------------------------------------------------------------------------*/
/*                                Interfaces                                 */
/*---------------------------------------------------------------------------*/

st_data   ps2_cmd    (sys_clk, hard_reset);
st_data   ps2_data   (sys_clk, hard_reset);
st_data   audio_left (sys_clk, hard_reset);
st_data   audio_right(sys_clk, hard_reset);
st_packet vga        (vga_clk, hard_reset);
mm_ebab   mm         ( mm_clk, hard_reset);

/*---------------------------------------------------------------------------*/
/*                               Computation                                 */
/*---------------------------------------------------------------------------*/

always_comb dmg_clk_ = ~dmg_clk;

always_ff @(posedge dmg_double_clk) begin
    dmg_clk <= (hard_reset) 1'b0 : dmg_clk_;
end

/*---------------------------------------------------------------------------*/
/*                                Submodules                                 */
/*---------------------------------------------------------------------------*/

sys hardware_system (                                     /*=== QSys Hardware Interface =====*/
                                                          /*------- Clocks & Resets ---------*/
    .hard_reset_reset         ( hard_reset             ), /*       hard_reset.reset          */
    .clk_in_clk               ( hw_clk                 ), /*           clk_in.clk            */
    .sys_clk_clk              ( sys_clk                ), /*          sys_clk.clk            */
    .vga_clk_clk              ( vga_clk                ), /*          vga_clk.clk            */
    .dmg_double_clk_clk       ( dmg_double_clk         ), /*   dmg_double_clk.clk            */
    .pll_0_locked_export      ( /*--- Not In Use ---*/ ), /*     pll_0_locked.export         */
                                                          /*------ Hardware Interface -------*/
    .audio_cntrlr_out_BCLK    ( AUD_BCLK               ), /* audio_cntrlr_out.BCLK           */
    .audio_cntrlr_out_DACDAT  ( AUD_DACDAT             ), /*                 .DACDAT         */
    .audio_cntrlr_out_DACLRCK ( AUD_DACLRCK            ), /*                 .DACLRCK        */
    .audio_cfg_out_SDAT       ( I2C_SDAT               ), /*    audio_cfg_out.SDAT           */
    .audio_cfg_out_SCLK       ( I2C_SCLK               ), /*                 .SCLK           */
    .vga_out_CLK              ( VGA_CLK                ), /*          vga_out.CLK            */
    .vga_out_HS               ( VGA_HS                 ), /*                 .HS             */
    .vga_out_VS               ( VGA_VS                 ), /*                 .VS             */
    .vga_out_BLANK            ( VGA_BLANK              ), /*                 .BLANK          */
    .vga_out_SYNC             ( VGA_SYNC               ), /*                 .SYNC           */
    .vga_out_R                ( VGA_R                  ), /*                 .R              */
    .vga_out_G                ( VGA_G                  ), /*                 .G              */
    .vga_out_B                ( VGA_B                  ), /*                 .B              */
    .ps2_out_CLK              ( PS2_CLK                ), /*          ps2_out.CLK            */
    .ps2_out_DAT              ( PS2_DAT                ), /*                 .DAT            */
    .sd_out_b_SD_cmd          ( HPS_SD_CMD             ), /*           sd_out.b_SD_cmd       */
    .sd_out_b_SD_dat          ( HPS_SD_DAT0            ), /*                 .b_SD_dat       */
    .sd_out_b_SD_dat3         ( HPS_SD_DAT3            ), /*                 .b_SD_dat3      */
    .sd_out_o_SD_clock        ( HPS_SD_CLK             ), /*                 .o_SD_clock     */
    .sdram_out_addr           ( DRAM_ADDR              ), /*        sdram_out.addr           */
    .sdram_out_ba             ( DRAM_BA                ), /*                 .ba             */
    .sdram_out_cas_n          ( DRAM_CAS_N             ), /*                 .cas_n          */
    .sdram_out_cke            ( DRAM_CKE               ), /*                 .cke            */
    .sdram_out_cs_n           ( DRAM_CS_N              ), /*                 .cs_n           */
    .sdram_out_dq             ( DRAM_DQ                ), /*                 .dq             */
    .sdram_out_dqm            ( DRAM_DQM               ), /*                 .dqm            */
    .sdram_out_ras_n          ( DRAM_RAS_N             ), /*                 .ras_n          */
    .sdram_out_we_n           ( DRAM_WE_N              ), /*                 .we_n           */
    .sdram_clk_clk            ( DRAM_CLK               ), /*        sdram_clk.clk            */
                                                          /*---- Memory Mapped Interface ----*/
    .avalon_mm_in_address     ( mm.addr                ), /*     avalon_mm_in.address        */
    .avalon_mm_in_byte_enable ( mm.byte_en             ), /*                 .byte_enable    */
    .avalon_mm_in_read        ( mm.read_en             ), /*                 .read           */
    .avalon_mm_in_write       ( mm.write_en            ), /*                 .write          */
    .avalon_mm_in_write_data  ( mm.write_data          ), /*                 .write_data     */
    .avalon_mm_in_acknowledge ( mm.ack                 ), /*                 .acknowledge    */
    .avalon_mm_in_read_data   ( mm.read_data           ), /*                 .read_data      */
                                                          /*------- Stream Interface --------*/
    .ps2_cmd_in_data          ( ps2_cmd.data           ), /*       ps2_cmd_in.data           */
    .ps2_cmd_in_valid         ( ps2_cmd.valid          ), /*                 .valid          */
    .ps2_cmd_in_ready         ( ps2_cmd.ready          ), /*                 .ready          */
    .ps2_data_out_ready       ( ps2_data.ready         ), /*     ps2_data_out.ready          */
    .ps2_data_out_data        ( ps2_data.data          ), /*                 .data           */
    .ps2_data_out_valid       ( ps2_data.valid         ), /*                 .valid          */
    .audio_left_in_data       ( audio_left.data        ), /*    audio_left_in.data           */
    .audio_left_in_valid      ( audio_left.valid       ), /*                 .valid          */
    .audio_left_in_ready      ( audio_left.ready       ), /*                 .ready          */
    .audio_right_in_data      ( audio_right.data       ), /*   audio_right_in.data           */
    .audio_right_in_valid     ( audio_right.valid      ), /*                 .valid          */
    .audio_right_in_ready     ( audio_right.ready      ), /*                 .ready          */
    .audio_left_out_ready     ( /*--- Not In Use ---*/ ), /*   audio_left_out.ready          */
    .audio_left_out_data      ( /*--- Not In Use ---*/ ), /*                 .data           */
    .audio_left_out_valid     ( /*--- Not In Use ---*/ ), /*                 .valid          */
    .audio_right_out_ready    ( /*--- Not In Use ---*/ ), /*  audio_right_out.ready          */
    .audio_right_out_data     ( /*--- Not In Use ---*/ ), /*                 .data           */
    .audio_right_out_valid    ( /*--- Not In Use ---*/ ), /*                 .valid          */
    .vga_in_data              ( vga.data               ), /*           vga_in.data           */
    .vga_in_startofpacket     ( vga.startpacket        ), /*                 .startofpacket  */
    .vga_in_endofpacket       ( vga.endpacket          ), /*                 .endofpacket    */
    .vga_in_valid             ( vga.valid              ), /*                 .valid          */
    .vga_in_ready             ( vga.ready              ), /*                 .ready          */
);                                                        /*=================================*/


endmodule : gb_dmg
