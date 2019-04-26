/*---------------------------------------------------------------------------*
 * Module: Gameboy DMG                                                       *
 * Purpose: Top Level Module for an implementation of the original GameBoy   *
 *     DMG model for the DE1-SOC.                                            *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

import gb_intf::cntrlr_data;

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
    output bit  [1:0]  LEDR
);

logic
    pll_lock,
    hard_reset_n,
    sys_reset,
    sys_reset_n,
    dmg_reset,
    dmg_reset_n,
    audio_reset,
    audio_reset_n,
    vga_reset,
    vga_reset_n,
    hw_clk,
    sys_clk,
    vga_clk,
    audio_clk,
    dmg_double_clk,
    dmg_clk, dmg_clk_;
cntrlr_data
    cntrlr_input;

/*---------------------------------------------------------------------------*/
/*                                Interfaces                                 */
/*---------------------------------------------------------------------------*/

/* PS/2 */
st_data #(
    .data_width(8)
) ps2_cmd (
    .clk(dmg_clk),
    .reset(dmg_reset)
);
st_data #(
    .data_width(8)
) ps2_data (
    .clk(dmg_clk),
    .reset(dmg_reset)
);

/* Audio */
st_data #(
    .data_width(8)
) audio_l_dac (
    .clk(dmg_clk),
    .reset(dmg_reset_n)
);
st_data #(
    .data_width(8)
) audio_r_dac (
    .clk(dmg_clk),
    .reset(dmg_reset_n)
);

/* Audio In (Unused) */
//st_data #(
//    .data_width(8)
//) audio_l_adc (
//    .clk(audio_clk),
//    .reset(audio_reset)
//);
//st_data #(
//    .data_width(8)
//) audio_r_adc (
//    .clk(audio_clk),
//    .reset(audio_reset)
//);

/* Display */
st_data #(
    .data_width(320)
) display_in (
    .clk(dmg_clk),
    .reset(dmg_reset_n)
);
st_data #(
    .data_width(320)
) display_o (
    .clk(vga_clk),
    .reset(vga_reset_n)
);
st_packet #(
    .data_width(24)
) vga (
    .clk(vga_clk),
    .reset(vga_reset)
);

/* Memory Mapped Bus */
mm_ebab #(
    .data_width(16),
    .addr_width(27)
) mm (
    .clk(sys_clk),
    .reset(sys_reset)
);

/*---------------------------------------------------------------------------*/
/*                               Computation                                 */
/*---------------------------------------------------------------------------*/

assign hw_clk   = CLOCK_50;
assign dmg_clk_ = ~dmg_clk;

always_ff @(posedge dmg_double_clk) begin
    dmg_clk <= (!hard_reset_n) ? 1'b0 : dmg_clk_;
end

//always_ff @(posedge audio_clk) begin
//    audio_l_adc.ready <= 1'b1;
//    audio_r_adc.ready <= 1'b1;
//end

/*---------------------------------------------------------------------------*/
/*                                Submodules                                 */
/*---------------------------------------------------------------------------*/

display dmg_to_vga (
    .vga(vga.source),
    .dmg(display_o.sink)
);

controller ps2_cntrlr (
    .cmd(ps2_cmd.source),
    .data(ps2_data.sink),
    .cntrlr(cntrlr_input)
);

mm_cntrlr mm_master (
    .mm(mm.master)
);

gb dmg(
    .display_out(display_in.source),
    .cntrlr_in(cntrlr_input)
);

sys hardware_system (                                       /*=== QSys Hardware Interface ====*/
                                                            /*------- Clocks & Resets --------*/
    .reset_in_reset_n         ( hard_reset_n             ), /*         reset_in.reset_n       */
    .sys_reset_reset          ( sys_reset                ), /*        sys_reset.reset         */
    .sys_reset_n_reset_n      ( sys_reset_n              ), /*      sys_reset_n.reset_n       */
    .vga_reset_reset          ( vga_reset                ), /*        vga_reset.reset         */
    .vga_reset_n_reset_n      ( vga_reset_n              ), /*      vga_reset_n.reset_n       */
    .dmg_reset_reset          ( dmg_reset                ), /*        dmg_reset.reset         */
    .dmg_reset_n_reset_n      ( dmg_reset_n              ), /*      dmg_reset_n.reset_n       */
    .audio_reset_reset        ( audio_reset              ), /*      audio_reset.reset         */
    .audio_reset_n_reset_n    ( audio_reset_n            ), /*    audio_reset_n.reset_n       */
    .clk_in_clk               ( hw_clk                   ), /*           clk_in.clk           */
    .sys_clk_clk              ( sys_clk                  ), /*          sys_clk.clk           */
    .vga_clk_clk              ( vga_clk                  ), /*          vga_clk.clk           */
    .dmg_clk_clk              ( dmg_clk                  ), /*          dmg_clk.clk           */
    .dmg_double_clk_clk       ( dmg_double_clk           ), /*   dmg_double_clk.clk           */
    .audio_clk_clk            ( audio_clk                ), /*        audio_clk.clk           */
    .pll_0_locked_export      ( pll_lock                 ), /*     pll_0_locked.export        */
                                                            /*------ Hardware Interface ------*/
    .audio_cntrlr_out_BCLK    ( AUD_BCLK                 ), /* audio_cntrlr_out.BCLK          */
    .audio_cntrlr_out_DACDAT  ( AUD_DACDAT               ), /*                 .DACDAT        */
    .audio_cntrlr_out_DACLRCK ( AUD_DACLRCK              ), /*                 .DACLRCK       */
    .audio_cfg_out_SDAT       ( I2C_SDAT                 ), /*    audio_cfg_out.SDAT          */
    .audio_cfg_out_SCLK       ( I2C_SCLK                 ), /*                 .SCLK          */
    .vga_out_CLK              ( VGA_CLK                  ), /*          vga_out.CLK           */
    .vga_out_HS               ( VGA_HS                   ), /*                 .HS            */
    .vga_out_VS               ( VGA_VS                   ), /*                 .VS            */
    .vga_out_BLANK            ( VGA_BLANK_N              ), /*                 .BLANK         */
    .vga_out_SYNC             ( VGA_SYNC_N               ), /*                 .SYNC          */
    .vga_out_R                ( VGA_R                    ), /*                 .R             */
    .vga_out_G                ( VGA_G                    ), /*                 .G             */
    .vga_out_B                ( VGA_B                    ), /*                 .B             */
    .ps2_out_CLK              ( PS2_CLK                  ), /*          ps2_out.CLK           */
    .ps2_out_DAT              ( PS2_DAT                  ), /*                 .DAT           */
//  .sd_out_b_SD_cmd          ( HPS_SD_CMD               ), /*           sd_out.b_SD_cmd      */
//  .sd_out_b_SD_dat          ( HPS_SD_DAT0              ), /*                 .b_SD_dat      */
//  .sd_out_b_SD_dat3         ( HPS_SD_DAT3              ), /*                 .b_SD_dat3     */
//  .sd_out_o_SD_clock        ( HPS_SD_CLK               ), /*                 .o_SD_clock    */
    .sdram_out_addr           ( DRAM_ADDR                ), /*        sdram_out.addr          */
    .sdram_out_ba             ( DRAM_BA                  ), /*                 .ba            */
    .sdram_out_cas_n          ( DRAM_CAS_N               ), /*                 .cas_n         */
    .sdram_out_cke            ( DRAM_CKE                 ), /*                 .cke           */
    .sdram_out_cs_n           ( DRAM_CS_N                ), /*                 .cs_n          */
    .sdram_out_dq             ( DRAM_DQ                  ), /*                 .dq            */
    .sdram_out_dqm            ( DRAM_DQM                 ), /*                 .dqm           */
    .sdram_out_ras_n          ( DRAM_RAS_N               ), /*                 .ras_n         */
    .sdram_out_we_n           ( DRAM_WE_N                ), /*                 .we_n          */
    .sdram_clk_clk            ( DRAM_CLK                 ), /*        sdram_clk.clk           */
                                                            /*--- Memory Mapped Interface ----*/
    .avalon_mm_in_address     ( mm.slave.addr            ), /*     avalon_mm_in.address       */
    .avalon_mm_in_byte_enable ( mm.slave.byte_en         ), /*                 .byte_enable   */
    .avalon_mm_in_read        ( mm.slave.read_en         ), /*                 .read          */
    .avalon_mm_in_write       ( mm.slave.write_en        ), /*                 .write         */
    .avalon_mm_in_write_data  ( mm.slave.write_data      ), /*                 .write_data    */
    .avalon_mm_in_acknowledge ( mm.slave.ack             ), /*                 .acknowledge   */
    .avalon_mm_in_read_data   ( mm.slave.read_data       ), /*                 .read_data     */
                                                            /*------- Stream Interface -------*/
    .ps2_cmd_in_data          ( ps2_cmd.sink.data        ), /*       ps2_cmd_in.data          */
    .ps2_cmd_in_valid         ( ps2_cmd.sink.valid       ), /*                 .valid         */
    .ps2_cmd_in_ready         ( ps2_cmd.sink.ready       ), /*                 .ready         */
    .ps2_data_out_ready       ( ps2_data.source.ready    ), /*     ps2_data_out.ready         */
    .ps2_data_out_data        ( ps2_data.source.data     ), /*                 .data          */
    .ps2_data_out_valid       ( ps2_data.source.valid    ), /*                 .valid         */
    .audio_l_in_data          ( audio_l_dac.sink.data    ), /*       audio_l_in.data          */
    .audio_l_in_valid         ( audio_l_dac.sink.valid   ), /*                 .valid         */
    .audio_l_in_ready         ( audio_l_dac.sink.ready   ), /*                 .ready         */
    .audio_r_in_data          ( audio_r_dac.sink.data    ), /*       audio_r_in.data          */
    .audio_r_in_valid         ( audio_r_dac.sink.valid   ), /*                 .valid         */
    .audio_r_in_ready         ( audio_r_dac.sink.ready   ), /*                 .ready         */
//  .audio_l_o_ready          ( audio_l_adc.source.ready ), /*        audio_l_o.ready         */
//  .audio_l_o_data           ( audio_l_adc.source.data  ), /*                 .data          */
//  .audio_l_o_valid          ( audio_l_adc.source.valid ), /*                 .valid         */
//  .audio_r_o_ready          ( audio_r_adc.source.ready ), /*        audio_r_o.ready         */
//  .audio_r_o_data           ( audio_r_adc.source.data  ), /*                 .data          */
//  .audio_r_o_valid          ( audio_r_adc.source.valid ), /*                 .valid         */
    .display_fifo_in_data     ( display_in.sink.data     ), /*  display_fifo_in.data          */
    .display_fifo_in_valid    ( display_in.sink.valid    ), /*                 .valid         */
    .display_fifo_in_ready    ( display_in.sink.ready    ), /*                 .ready         */
    .display_fifo_out_data    ( display_o.source.data    ), /* display_fifo_out.data          */
    .display_fifo_out_valid   ( display_o.source.valid   ), /*                 .valid         */
    .display_fifo_out_ready   ( display_o.source.ready   ), /*                 .ready         */
    .vga_in_data              ( vga.sink.data            ), /*           vga_in.data          */
    .vga_in_startofpacket     ( vga.sink.start_packet    ), /*                 .startofpacket */
    .vga_in_endofpacket       ( vga.sink.end_packet      ), /*                 .endofpacket   */
    .vga_in_valid             ( vga.sink.valid           ), /*                 .valid         */
    .vga_in_ready             ( vga.sink.ready           ), /*                 .ready         */
);                                                          /*================================*/


endmodule : gb_dmg
