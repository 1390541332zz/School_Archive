// sys.v

// Generated using ACDS version 17.0 595

`timescale 1 ps / 1 ps
module sys (
		inout  wire        audio_cfg_out_SDAT,       //    audio_cfg_out.SDAT
		output wire        audio_cfg_out_SCLK,       //                 .SCLK
		input  wire        audio_cntrlr_out_BCLK,    // audio_cntrlr_out.BCLK
		output wire        audio_cntrlr_out_DACDAT,  //                 .DACDAT
		input  wire        audio_cntrlr_out_DACLRCK, //                 .DACLRCK
		input  wire [15:0] audio_left_in_data,       //    audio_left_in.data
		input  wire        audio_left_in_valid,      //                 .valid
		output wire        audio_left_in_ready,      //                 .ready
		input  wire        audio_left_out_ready,     //   audio_left_out.ready
		output wire [15:0] audio_left_out_data,      //                 .data
		output wire        audio_left_out_valid,     //                 .valid
		input  wire [15:0] audio_right_in_data,      //   audio_right_in.data
		input  wire        audio_right_in_valid,     //                 .valid
		output wire        audio_right_in_ready,     //                 .ready
		input  wire        audio_right_out_ready,    //  audio_right_out.ready
		output wire [15:0] audio_right_out_data,     //                 .data
		output wire        audio_right_out_valid,    //                 .valid
		input  wire [26:0] avalon_mm_in_address,     //     avalon_mm_in.address
		input  wire [1:0]  avalon_mm_in_byte_enable, //                 .byte_enable
		input  wire        avalon_mm_in_read,        //                 .read
		input  wire        avalon_mm_in_write,       //                 .write
		input  wire [15:0] avalon_mm_in_write_data,  //                 .write_data
		output wire        avalon_mm_in_acknowledge, //                 .acknowledge
		output wire [15:0] avalon_mm_in_read_data,   //                 .read_data
		input  wire        clk_in_clk,               //           clk_in.clk
		output wire        dmg_double_clk_clk,       //   dmg_double_clk.clk
		input  wire        hard_reset_reset,         //       hard_reset.reset
		output wire        pll_0_locked_export,      //     pll_0_locked.export
		input  wire [7:0]  ps2_cmd_in_data,          //       ps2_cmd_in.data
		input  wire        ps2_cmd_in_valid,         //                 .valid
		output wire        ps2_cmd_in_ready,         //                 .ready
		input  wire        ps2_data_out_ready,       //     ps2_data_out.ready
		output wire [7:0]  ps2_data_out_data,        //                 .data
		output wire        ps2_data_out_valid,       //                 .valid
		inout  wire        ps2_out_CLK,              //          ps2_out.CLK
		inout  wire        ps2_out_DAT,              //                 .DAT
		inout  wire        sd_out_b_SD_cmd,          //           sd_out.b_SD_cmd
		inout  wire        sd_out_b_SD_dat,          //                 .b_SD_dat
		inout  wire        sd_out_b_SD_dat3,         //                 .b_SD_dat3
		output wire        sd_out_o_SD_clock,        //                 .o_SD_clock
		output wire        sdram_clk_clk,            //        sdram_clk.clk
		output wire [12:0] sdram_out_addr,           //        sdram_out.addr
		output wire [1:0]  sdram_out_ba,             //                 .ba
		output wire        sdram_out_cas_n,          //                 .cas_n
		output wire        sdram_out_cke,            //                 .cke
		output wire        sdram_out_cs_n,           //                 .cs_n
		inout  wire [15:0] sdram_out_dq,             //                 .dq
		output wire [1:0]  sdram_out_dqm,            //                 .dqm
		output wire        sdram_out_ras_n,          //                 .ras_n
		output wire        sdram_out_we_n,           //                 .we_n
		output wire        sys_clk_clk,              //          sys_clk.clk
		output wire        vga_clk_clk,              //          vga_clk.clk
		input  wire [29:0] vga_in_data,              //           vga_in.data
		input  wire        vga_in_startofpacket,     //                 .startofpacket
		input  wire        vga_in_endofpacket,       //                 .endofpacket
		input  wire        vga_in_valid,             //                 .valid
		output wire        vga_in_ready,             //                 .ready
		output wire        vga_out_CLK,              //          vga_out.CLK
		output wire        vga_out_HS,               //                 .HS
		output wire        vga_out_VS,               //                 .VS
		output wire        vga_out_BLANK,            //                 .BLANK
		output wire        vga_out_SYNC,             //                 .SYNC
		output wire [7:0]  vga_out_R,                //                 .R
		output wire [7:0]  vga_out_G,                //                 .G
		output wire [7:0]  vga_out_B                 //                 .B
	);

	wire  [15:0] fpga_master_avalon_master_readdata;                             // mm_interconnect_0:fpga_master_avalon_master_readdata -> fpga_master:avalon_readdata
	wire         fpga_master_avalon_master_waitrequest;                          // mm_interconnect_0:fpga_master_avalon_master_waitrequest -> fpga_master:avalon_waitrequest
	wire   [1:0] fpga_master_avalon_master_byteenable;                           // fpga_master:avalon_byteenable -> mm_interconnect_0:fpga_master_avalon_master_byteenable
	wire         fpga_master_avalon_master_read;                                 // fpga_master:avalon_read -> mm_interconnect_0:fpga_master_avalon_master_read
	wire  [26:0] fpga_master_avalon_master_address;                              // fpga_master:avalon_address -> mm_interconnect_0:fpga_master_avalon_master_address
	wire         fpga_master_avalon_master_write;                                // fpga_master:avalon_write -> mm_interconnect_0:fpga_master_avalon_master_write
	wire  [15:0] fpga_master_avalon_master_writedata;                            // fpga_master:avalon_writedata -> mm_interconnect_0:fpga_master_avalon_master_writedata
	wire  [31:0] mm_interconnect_0_audio_cfg_avalon_av_config_slave_readdata;    // audio_cfg:readdata -> mm_interconnect_0:audio_cfg_avalon_av_config_slave_readdata
	wire         mm_interconnect_0_audio_cfg_avalon_av_config_slave_waitrequest; // audio_cfg:waitrequest -> mm_interconnect_0:audio_cfg_avalon_av_config_slave_waitrequest
	wire   [1:0] mm_interconnect_0_audio_cfg_avalon_av_config_slave_address;     // mm_interconnect_0:audio_cfg_avalon_av_config_slave_address -> audio_cfg:address
	wire         mm_interconnect_0_audio_cfg_avalon_av_config_slave_read;        // mm_interconnect_0:audio_cfg_avalon_av_config_slave_read -> audio_cfg:read
	wire   [3:0] mm_interconnect_0_audio_cfg_avalon_av_config_slave_byteenable;  // mm_interconnect_0:audio_cfg_avalon_av_config_slave_byteenable -> audio_cfg:byteenable
	wire         mm_interconnect_0_audio_cfg_avalon_av_config_slave_write;       // mm_interconnect_0:audio_cfg_avalon_av_config_slave_write -> audio_cfg:write
	wire  [31:0] mm_interconnect_0_audio_cfg_avalon_av_config_slave_writedata;   // mm_interconnect_0:audio_cfg_avalon_av_config_slave_writedata -> audio_cfg:writedata
	wire         mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_chipselect;     // mm_interconnect_0:sd_cntrlr_avalon_sdcard_slave_chipselect -> sd_cntrlr:i_avalon_chip_select
	wire  [31:0] mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_readdata;       // sd_cntrlr:o_avalon_readdata -> mm_interconnect_0:sd_cntrlr_avalon_sdcard_slave_readdata
	wire         mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_waitrequest;    // sd_cntrlr:o_avalon_waitrequest -> mm_interconnect_0:sd_cntrlr_avalon_sdcard_slave_waitrequest
	wire   [7:0] mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_address;        // mm_interconnect_0:sd_cntrlr_avalon_sdcard_slave_address -> sd_cntrlr:i_avalon_address
	wire         mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_read;           // mm_interconnect_0:sd_cntrlr_avalon_sdcard_slave_read -> sd_cntrlr:i_avalon_read
	wire   [3:0] mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_byteenable;     // mm_interconnect_0:sd_cntrlr_avalon_sdcard_slave_byteenable -> sd_cntrlr:i_avalon_byteenable
	wire         mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_write;          // mm_interconnect_0:sd_cntrlr_avalon_sdcard_slave_write -> sd_cntrlr:i_avalon_write
	wire  [31:0] mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_writedata;      // mm_interconnect_0:sd_cntrlr_avalon_sdcard_slave_writedata -> sd_cntrlr:i_avalon_writedata
	wire         mm_interconnect_0_sdram_cntrlr_s1_chipselect;                   // mm_interconnect_0:sdram_cntrlr_s1_chipselect -> sdram_cntrlr:az_cs
	wire  [15:0] mm_interconnect_0_sdram_cntrlr_s1_readdata;                     // sdram_cntrlr:za_data -> mm_interconnect_0:sdram_cntrlr_s1_readdata
	wire         mm_interconnect_0_sdram_cntrlr_s1_waitrequest;                  // sdram_cntrlr:za_waitrequest -> mm_interconnect_0:sdram_cntrlr_s1_waitrequest
	wire  [24:0] mm_interconnect_0_sdram_cntrlr_s1_address;                      // mm_interconnect_0:sdram_cntrlr_s1_address -> sdram_cntrlr:az_addr
	wire         mm_interconnect_0_sdram_cntrlr_s1_read;                         // mm_interconnect_0:sdram_cntrlr_s1_read -> sdram_cntrlr:az_rd_n
	wire   [1:0] mm_interconnect_0_sdram_cntrlr_s1_byteenable;                   // mm_interconnect_0:sdram_cntrlr_s1_byteenable -> sdram_cntrlr:az_be_n
	wire         mm_interconnect_0_sdram_cntrlr_s1_readdatavalid;                // sdram_cntrlr:za_valid -> mm_interconnect_0:sdram_cntrlr_s1_readdatavalid
	wire         mm_interconnect_0_sdram_cntrlr_s1_write;                        // mm_interconnect_0:sdram_cntrlr_s1_write -> sdram_cntrlr:az_wr_n
	wire  [15:0] mm_interconnect_0_sdram_cntrlr_s1_writedata;                    // mm_interconnect_0:sdram_cntrlr_s1_writedata -> sdram_cntrlr:az_data
	wire         rst_controller_reset_out_reset;                                 // rst_controller:reset_out -> [audio_cfg:reset, audio_cntrlr:reset, fpga_master:reset, mm_interconnect_0:fpga_master_reset_reset_bridge_in_reset_reset, ps2_cntrlr:reset, sd_cntrlr:i_reset_n]
	wire         rst_controller_001_reset_out_reset;                             // rst_controller_001:reset_out -> [clk_50:ref_reset_reset, mm_interconnect_0:sdram_cntrlr_reset_reset_bridge_in_reset_reset, pll_0:rst, rst_controller:reset_in0, rst_controller_002:reset_in0, sdram_cntrlr:reset_n]
	wire         rst_controller_002_reset_out_reset;                             // rst_controller_002:reset_out -> vga_cntrlr:reset

	sys_audio_cfg audio_cfg (
		.clk         (sys_clk_clk),                                                    //                    clk.clk
		.reset       (rst_controller_reset_out_reset),                                 //                  reset.reset
		.address     (mm_interconnect_0_audio_cfg_avalon_av_config_slave_address),     // avalon_av_config_slave.address
		.byteenable  (mm_interconnect_0_audio_cfg_avalon_av_config_slave_byteenable),  //                       .byteenable
		.read        (mm_interconnect_0_audio_cfg_avalon_av_config_slave_read),        //                       .read
		.write       (mm_interconnect_0_audio_cfg_avalon_av_config_slave_write),       //                       .write
		.writedata   (mm_interconnect_0_audio_cfg_avalon_av_config_slave_writedata),   //                       .writedata
		.readdata    (mm_interconnect_0_audio_cfg_avalon_av_config_slave_readdata),    //                       .readdata
		.waitrequest (mm_interconnect_0_audio_cfg_avalon_av_config_slave_waitrequest), //                       .waitrequest
		.I2C_SDAT    (audio_cfg_out_SDAT),                                             //     external_interface.export
		.I2C_SCLK    (audio_cfg_out_SCLK)                                              //                       .export
	);

	sys_audio_cntrlr audio_cntrlr (
		.clk                          (sys_clk_clk),                    //                         clk.clk
		.reset                        (rst_controller_reset_out_reset), //                       reset.reset
		.from_adc_left_channel_ready  (audio_left_out_ready),           //  avalon_left_channel_source.ready
		.from_adc_left_channel_data   (audio_left_out_data),            //                            .data
		.from_adc_left_channel_valid  (audio_left_out_valid),           //                            .valid
		.from_adc_right_channel_ready (audio_right_out_ready),          // avalon_right_channel_source.ready
		.from_adc_right_channel_data  (audio_right_out_data),           //                            .data
		.from_adc_right_channel_valid (audio_right_out_valid),          //                            .valid
		.to_dac_left_channel_data     (audio_left_in_data),             //    avalon_left_channel_sink.data
		.to_dac_left_channel_valid    (audio_left_in_valid),            //                            .valid
		.to_dac_left_channel_ready    (audio_left_in_ready),            //                            .ready
		.to_dac_right_channel_data    (audio_right_in_data),            //   avalon_right_channel_sink.data
		.to_dac_right_channel_valid   (audio_right_in_valid),           //                            .valid
		.to_dac_right_channel_ready   (audio_right_in_ready),           //                            .ready
		.AUD_BCLK                     (audio_cntrlr_out_BCLK),          //          external_interface.export
		.AUD_DACDAT                   (audio_cntrlr_out_DACDAT),        //                            .export
		.AUD_DACLRCK                  (audio_cntrlr_out_DACLRCK)        //                            .export
	);

	sys_clk_50 clk_50 (
		.ref_clk_clk        (clk_in_clk),                         //      ref_clk.clk
		.ref_reset_reset    (rst_controller_001_reset_out_reset), //    ref_reset.reset
		.sys_clk_clk        (sys_clk_clk),                        //      sys_clk.clk
		.sdram_clk_clk      (sdram_clk_clk),                      //    sdram_clk.clk
		.reset_source_reset ()                                    // reset_source.reset
	);

	sys_fpga_master fpga_master (
		.clk                (sys_clk_clk),                           //                clk.clk
		.reset              (rst_controller_reset_out_reset),        //              reset.reset
		.avalon_readdata    (fpga_master_avalon_master_readdata),    //      avalon_master.readdata
		.avalon_waitrequest (fpga_master_avalon_master_waitrequest), //                   .waitrequest
		.avalon_byteenable  (fpga_master_avalon_master_byteenable),  //                   .byteenable
		.avalon_read        (fpga_master_avalon_master_read),        //                   .read
		.avalon_write       (fpga_master_avalon_master_write),       //                   .write
		.avalon_writedata   (fpga_master_avalon_master_writedata),   //                   .writedata
		.avalon_address     (fpga_master_avalon_master_address),     //                   .address
		.address            (avalon_mm_in_address),                  // external_interface.export
		.byte_enable        (avalon_mm_in_byte_enable),              //                   .export
		.read               (avalon_mm_in_read),                     //                   .export
		.write              (avalon_mm_in_write),                    //                   .export
		.write_data         (avalon_mm_in_write_data),               //                   .export
		.acknowledge        (avalon_mm_in_acknowledge),              //                   .export
		.read_data          (avalon_mm_in_read_data)                 //                   .export
	);

	sys_pll_0 pll_0 (
		.refclk   (sys_clk_clk),                        //  refclk.clk
		.rst      (rst_controller_001_reset_out_reset), //   reset.reset
		.outclk_0 (vga_clk_clk),                        // outclk0.clk
		.outclk_1 (dmg_double_clk_clk),                 // outclk1.clk
		.locked   (pll_0_locked_export)                 //  locked.export
	);

	sys_ps2_cntrlr ps2_cntrlr (
		.clk           (sys_clk_clk),                    //                     clk.clk
		.reset         (rst_controller_reset_out_reset), //                   reset.reset
		.command       (ps2_cmd_in_data),                // avalon_ps2_command_sink.data
		.command_valid (ps2_cmd_in_valid),               //                        .valid
		.command_ready (ps2_cmd_in_ready),               //                        .ready
		.data_ready    (ps2_data_out_ready),             //  avalon_ps2_data_source.ready
		.data          (ps2_data_out_data),              //                        .data
		.data_valid    (ps2_data_out_valid),             //                        .valid
		.PS2_CLK       (ps2_out_CLK),                    //      external_interface.export
		.PS2_DAT       (ps2_out_DAT)                     //                        .export
	);

	Altera_UP_SD_Card_Avalon_Interface sd_cntrlr (
		.i_avalon_chip_select (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_chipselect),  // avalon_sdcard_slave.chipselect
		.i_avalon_address     (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_address),     //                    .address
		.i_avalon_read        (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_read),        //                    .read
		.i_avalon_write       (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_write),       //                    .write
		.i_avalon_byteenable  (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_byteenable),  //                    .byteenable
		.i_avalon_writedata   (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_writedata),   //                    .writedata
		.o_avalon_readdata    (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_readdata),    //                    .readdata
		.o_avalon_waitrequest (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_waitrequest), //                    .waitrequest
		.i_clock              (sys_clk_clk),                                                 //                 clk.clk
		.i_reset_n            (~rst_controller_reset_out_reset),                             //               reset.reset_n
		.b_SD_cmd             (sd_out_b_SD_cmd),                                             //         conduit_end.export
		.b_SD_dat             (sd_out_b_SD_dat),                                             //                    .export
		.b_SD_dat3            (sd_out_b_SD_dat3),                                            //                    .export
		.o_SD_clock           (sd_out_o_SD_clock)                                            //                    .export
	);

	sys_sdram_cntrlr sdram_cntrlr (
		.clk            (clk_in_clk),                                      //   clk.clk
		.reset_n        (~rst_controller_001_reset_out_reset),             // reset.reset_n
		.az_addr        (mm_interconnect_0_sdram_cntrlr_s1_address),       //    s1.address
		.az_be_n        (~mm_interconnect_0_sdram_cntrlr_s1_byteenable),   //      .byteenable_n
		.az_cs          (mm_interconnect_0_sdram_cntrlr_s1_chipselect),    //      .chipselect
		.az_data        (mm_interconnect_0_sdram_cntrlr_s1_writedata),     //      .writedata
		.az_rd_n        (~mm_interconnect_0_sdram_cntrlr_s1_read),         //      .read_n
		.az_wr_n        (~mm_interconnect_0_sdram_cntrlr_s1_write),        //      .write_n
		.za_data        (mm_interconnect_0_sdram_cntrlr_s1_readdata),      //      .readdata
		.za_valid       (mm_interconnect_0_sdram_cntrlr_s1_readdatavalid), //      .readdatavalid
		.za_waitrequest (mm_interconnect_0_sdram_cntrlr_s1_waitrequest),   //      .waitrequest
		.zs_addr        (sdram_out_addr),                                  //  wire.export
		.zs_ba          (sdram_out_ba),                                    //      .export
		.zs_cas_n       (sdram_out_cas_n),                                 //      .export
		.zs_cke         (sdram_out_cke),                                   //      .export
		.zs_cs_n        (sdram_out_cs_n),                                  //      .export
		.zs_dq          (sdram_out_dq),                                    //      .export
		.zs_dqm         (sdram_out_dqm),                                   //      .export
		.zs_ras_n       (sdram_out_ras_n),                                 //      .export
		.zs_we_n        (sdram_out_we_n)                                   //      .export
	);

	sys_vga_cntrlr vga_cntrlr (
		.clk           (vga_clk_clk),                        //                clk.clk
		.reset         (rst_controller_002_reset_out_reset), //              reset.reset
		.data          (vga_in_data),                        //    avalon_vga_sink.data
		.startofpacket (vga_in_startofpacket),               //                   .startofpacket
		.endofpacket   (vga_in_endofpacket),                 //                   .endofpacket
		.valid         (vga_in_valid),                       //                   .valid
		.ready         (vga_in_ready),                       //                   .ready
		.VGA_CLK       (vga_out_CLK),                        // external_interface.export
		.VGA_HS        (vga_out_HS),                         //                   .export
		.VGA_VS        (vga_out_VS),                         //                   .export
		.VGA_BLANK     (vga_out_BLANK),                      //                   .export
		.VGA_SYNC      (vga_out_SYNC),                       //                   .export
		.VGA_R         (vga_out_R),                          //                   .export
		.VGA_G         (vga_out_G),                          //                   .export
		.VGA_B         (vga_out_B)                           //                   .export
	);

	sys_mm_interconnect_0 mm_interconnect_0 (
		.clk_50_sys_clk_clk                             (sys_clk_clk),                                                    //                           clk_50_sys_clk.clk
		.sys_clk_clk_clk                                (clk_in_clk),                                                     //                              sys_clk_clk.clk
		.fpga_master_reset_reset_bridge_in_reset_reset  (rst_controller_reset_out_reset),                                 //  fpga_master_reset_reset_bridge_in_reset.reset
		.sdram_cntrlr_reset_reset_bridge_in_reset_reset (rst_controller_001_reset_out_reset),                             // sdram_cntrlr_reset_reset_bridge_in_reset.reset
		.fpga_master_avalon_master_address              (fpga_master_avalon_master_address),                              //                fpga_master_avalon_master.address
		.fpga_master_avalon_master_waitrequest          (fpga_master_avalon_master_waitrequest),                          //                                         .waitrequest
		.fpga_master_avalon_master_byteenable           (fpga_master_avalon_master_byteenable),                           //                                         .byteenable
		.fpga_master_avalon_master_read                 (fpga_master_avalon_master_read),                                 //                                         .read
		.fpga_master_avalon_master_readdata             (fpga_master_avalon_master_readdata),                             //                                         .readdata
		.fpga_master_avalon_master_write                (fpga_master_avalon_master_write),                                //                                         .write
		.fpga_master_avalon_master_writedata            (fpga_master_avalon_master_writedata),                            //                                         .writedata
		.audio_cfg_avalon_av_config_slave_address       (mm_interconnect_0_audio_cfg_avalon_av_config_slave_address),     //         audio_cfg_avalon_av_config_slave.address
		.audio_cfg_avalon_av_config_slave_write         (mm_interconnect_0_audio_cfg_avalon_av_config_slave_write),       //                                         .write
		.audio_cfg_avalon_av_config_slave_read          (mm_interconnect_0_audio_cfg_avalon_av_config_slave_read),        //                                         .read
		.audio_cfg_avalon_av_config_slave_readdata      (mm_interconnect_0_audio_cfg_avalon_av_config_slave_readdata),    //                                         .readdata
		.audio_cfg_avalon_av_config_slave_writedata     (mm_interconnect_0_audio_cfg_avalon_av_config_slave_writedata),   //                                         .writedata
		.audio_cfg_avalon_av_config_slave_byteenable    (mm_interconnect_0_audio_cfg_avalon_av_config_slave_byteenable),  //                                         .byteenable
		.audio_cfg_avalon_av_config_slave_waitrequest   (mm_interconnect_0_audio_cfg_avalon_av_config_slave_waitrequest), //                                         .waitrequest
		.sd_cntrlr_avalon_sdcard_slave_address          (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_address),        //            sd_cntrlr_avalon_sdcard_slave.address
		.sd_cntrlr_avalon_sdcard_slave_write            (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_write),          //                                         .write
		.sd_cntrlr_avalon_sdcard_slave_read             (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_read),           //                                         .read
		.sd_cntrlr_avalon_sdcard_slave_readdata         (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_readdata),       //                                         .readdata
		.sd_cntrlr_avalon_sdcard_slave_writedata        (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_writedata),      //                                         .writedata
		.sd_cntrlr_avalon_sdcard_slave_byteenable       (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_byteenable),     //                                         .byteenable
		.sd_cntrlr_avalon_sdcard_slave_waitrequest      (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_waitrequest),    //                                         .waitrequest
		.sd_cntrlr_avalon_sdcard_slave_chipselect       (mm_interconnect_0_sd_cntrlr_avalon_sdcard_slave_chipselect),     //                                         .chipselect
		.sdram_cntrlr_s1_address                        (mm_interconnect_0_sdram_cntrlr_s1_address),                      //                          sdram_cntrlr_s1.address
		.sdram_cntrlr_s1_write                          (mm_interconnect_0_sdram_cntrlr_s1_write),                        //                                         .write
		.sdram_cntrlr_s1_read                           (mm_interconnect_0_sdram_cntrlr_s1_read),                         //                                         .read
		.sdram_cntrlr_s1_readdata                       (mm_interconnect_0_sdram_cntrlr_s1_readdata),                     //                                         .readdata
		.sdram_cntrlr_s1_writedata                      (mm_interconnect_0_sdram_cntrlr_s1_writedata),                    //                                         .writedata
		.sdram_cntrlr_s1_byteenable                     (mm_interconnect_0_sdram_cntrlr_s1_byteenable),                   //                                         .byteenable
		.sdram_cntrlr_s1_readdatavalid                  (mm_interconnect_0_sdram_cntrlr_s1_readdatavalid),                //                                         .readdatavalid
		.sdram_cntrlr_s1_waitrequest                    (mm_interconnect_0_sdram_cntrlr_s1_waitrequest),                  //                                         .waitrequest
		.sdram_cntrlr_s1_chipselect                     (mm_interconnect_0_sdram_cntrlr_s1_chipselect)                    //                                         .chipselect
	);

	altera_reset_controller #(
		.NUM_RESET_INPUTS          (1),
		.OUTPUT_RESET_SYNC_EDGES   ("deassert"),
		.SYNC_DEPTH                (2),
		.RESET_REQUEST_PRESENT     (0),
		.RESET_REQ_WAIT_TIME       (1),
		.MIN_RST_ASSERTION_TIME    (3),
		.RESET_REQ_EARLY_DSRT_TIME (1),
		.USE_RESET_REQUEST_IN0     (0),
		.USE_RESET_REQUEST_IN1     (0),
		.USE_RESET_REQUEST_IN2     (0),
		.USE_RESET_REQUEST_IN3     (0),
		.USE_RESET_REQUEST_IN4     (0),
		.USE_RESET_REQUEST_IN5     (0),
		.USE_RESET_REQUEST_IN6     (0),
		.USE_RESET_REQUEST_IN7     (0),
		.USE_RESET_REQUEST_IN8     (0),
		.USE_RESET_REQUEST_IN9     (0),
		.USE_RESET_REQUEST_IN10    (0),
		.USE_RESET_REQUEST_IN11    (0),
		.USE_RESET_REQUEST_IN12    (0),
		.USE_RESET_REQUEST_IN13    (0),
		.USE_RESET_REQUEST_IN14    (0),
		.USE_RESET_REQUEST_IN15    (0),
		.ADAPT_RESET_REQUEST       (0)
	) rst_controller (
		.reset_in0      (rst_controller_001_reset_out_reset), // reset_in0.reset
		.clk            (sys_clk_clk),                        //       clk.clk
		.reset_out      (rst_controller_reset_out_reset),     // reset_out.reset
		.reset_req      (),                                   // (terminated)
		.reset_req_in0  (1'b0),                               // (terminated)
		.reset_in1      (1'b0),                               // (terminated)
		.reset_req_in1  (1'b0),                               // (terminated)
		.reset_in2      (1'b0),                               // (terminated)
		.reset_req_in2  (1'b0),                               // (terminated)
		.reset_in3      (1'b0),                               // (terminated)
		.reset_req_in3  (1'b0),                               // (terminated)
		.reset_in4      (1'b0),                               // (terminated)
		.reset_req_in4  (1'b0),                               // (terminated)
		.reset_in5      (1'b0),                               // (terminated)
		.reset_req_in5  (1'b0),                               // (terminated)
		.reset_in6      (1'b0),                               // (terminated)
		.reset_req_in6  (1'b0),                               // (terminated)
		.reset_in7      (1'b0),                               // (terminated)
		.reset_req_in7  (1'b0),                               // (terminated)
		.reset_in8      (1'b0),                               // (terminated)
		.reset_req_in8  (1'b0),                               // (terminated)
		.reset_in9      (1'b0),                               // (terminated)
		.reset_req_in9  (1'b0),                               // (terminated)
		.reset_in10     (1'b0),                               // (terminated)
		.reset_req_in10 (1'b0),                               // (terminated)
		.reset_in11     (1'b0),                               // (terminated)
		.reset_req_in11 (1'b0),                               // (terminated)
		.reset_in12     (1'b0),                               // (terminated)
		.reset_req_in12 (1'b0),                               // (terminated)
		.reset_in13     (1'b0),                               // (terminated)
		.reset_req_in13 (1'b0),                               // (terminated)
		.reset_in14     (1'b0),                               // (terminated)
		.reset_req_in14 (1'b0),                               // (terminated)
		.reset_in15     (1'b0),                               // (terminated)
		.reset_req_in15 (1'b0)                                // (terminated)
	);

	altera_reset_controller #(
		.NUM_RESET_INPUTS          (1),
		.OUTPUT_RESET_SYNC_EDGES   ("deassert"),
		.SYNC_DEPTH                (2),
		.RESET_REQUEST_PRESENT     (0),
		.RESET_REQ_WAIT_TIME       (1),
		.MIN_RST_ASSERTION_TIME    (3),
		.RESET_REQ_EARLY_DSRT_TIME (1),
		.USE_RESET_REQUEST_IN0     (0),
		.USE_RESET_REQUEST_IN1     (0),
		.USE_RESET_REQUEST_IN2     (0),
		.USE_RESET_REQUEST_IN3     (0),
		.USE_RESET_REQUEST_IN4     (0),
		.USE_RESET_REQUEST_IN5     (0),
		.USE_RESET_REQUEST_IN6     (0),
		.USE_RESET_REQUEST_IN7     (0),
		.USE_RESET_REQUEST_IN8     (0),
		.USE_RESET_REQUEST_IN9     (0),
		.USE_RESET_REQUEST_IN10    (0),
		.USE_RESET_REQUEST_IN11    (0),
		.USE_RESET_REQUEST_IN12    (0),
		.USE_RESET_REQUEST_IN13    (0),
		.USE_RESET_REQUEST_IN14    (0),
		.USE_RESET_REQUEST_IN15    (0),
		.ADAPT_RESET_REQUEST       (0)
	) rst_controller_001 (
		.reset_in0      (hard_reset_reset),                   // reset_in0.reset
		.clk            (clk_in_clk),                         //       clk.clk
		.reset_out      (rst_controller_001_reset_out_reset), // reset_out.reset
		.reset_req      (),                                   // (terminated)
		.reset_req_in0  (1'b0),                               // (terminated)
		.reset_in1      (1'b0),                               // (terminated)
		.reset_req_in1  (1'b0),                               // (terminated)
		.reset_in2      (1'b0),                               // (terminated)
		.reset_req_in2  (1'b0),                               // (terminated)
		.reset_in3      (1'b0),                               // (terminated)
		.reset_req_in3  (1'b0),                               // (terminated)
		.reset_in4      (1'b0),                               // (terminated)
		.reset_req_in4  (1'b0),                               // (terminated)
		.reset_in5      (1'b0),                               // (terminated)
		.reset_req_in5  (1'b0),                               // (terminated)
		.reset_in6      (1'b0),                               // (terminated)
		.reset_req_in6  (1'b0),                               // (terminated)
		.reset_in7      (1'b0),                               // (terminated)
		.reset_req_in7  (1'b0),                               // (terminated)
		.reset_in8      (1'b0),                               // (terminated)
		.reset_req_in8  (1'b0),                               // (terminated)
		.reset_in9      (1'b0),                               // (terminated)
		.reset_req_in9  (1'b0),                               // (terminated)
		.reset_in10     (1'b0),                               // (terminated)
		.reset_req_in10 (1'b0),                               // (terminated)
		.reset_in11     (1'b0),                               // (terminated)
		.reset_req_in11 (1'b0),                               // (terminated)
		.reset_in12     (1'b0),                               // (terminated)
		.reset_req_in12 (1'b0),                               // (terminated)
		.reset_in13     (1'b0),                               // (terminated)
		.reset_req_in13 (1'b0),                               // (terminated)
		.reset_in14     (1'b0),                               // (terminated)
		.reset_req_in14 (1'b0),                               // (terminated)
		.reset_in15     (1'b0),                               // (terminated)
		.reset_req_in15 (1'b0)                                // (terminated)
	);

	altera_reset_controller #(
		.NUM_RESET_INPUTS          (1),
		.OUTPUT_RESET_SYNC_EDGES   ("deassert"),
		.SYNC_DEPTH                (2),
		.RESET_REQUEST_PRESENT     (0),
		.RESET_REQ_WAIT_TIME       (1),
		.MIN_RST_ASSERTION_TIME    (3),
		.RESET_REQ_EARLY_DSRT_TIME (1),
		.USE_RESET_REQUEST_IN0     (0),
		.USE_RESET_REQUEST_IN1     (0),
		.USE_RESET_REQUEST_IN2     (0),
		.USE_RESET_REQUEST_IN3     (0),
		.USE_RESET_REQUEST_IN4     (0),
		.USE_RESET_REQUEST_IN5     (0),
		.USE_RESET_REQUEST_IN6     (0),
		.USE_RESET_REQUEST_IN7     (0),
		.USE_RESET_REQUEST_IN8     (0),
		.USE_RESET_REQUEST_IN9     (0),
		.USE_RESET_REQUEST_IN10    (0),
		.USE_RESET_REQUEST_IN11    (0),
		.USE_RESET_REQUEST_IN12    (0),
		.USE_RESET_REQUEST_IN13    (0),
		.USE_RESET_REQUEST_IN14    (0),
		.USE_RESET_REQUEST_IN15    (0),
		.ADAPT_RESET_REQUEST       (0)
	) rst_controller_002 (
		.reset_in0      (rst_controller_001_reset_out_reset), // reset_in0.reset
		.clk            (vga_clk_clk),                        //       clk.clk
		.reset_out      (rst_controller_002_reset_out_reset), // reset_out.reset
		.reset_req      (),                                   // (terminated)
		.reset_req_in0  (1'b0),                               // (terminated)
		.reset_in1      (1'b0),                               // (terminated)
		.reset_req_in1  (1'b0),                               // (terminated)
		.reset_in2      (1'b0),                               // (terminated)
		.reset_req_in2  (1'b0),                               // (terminated)
		.reset_in3      (1'b0),                               // (terminated)
		.reset_req_in3  (1'b0),                               // (terminated)
		.reset_in4      (1'b0),                               // (terminated)
		.reset_req_in4  (1'b0),                               // (terminated)
		.reset_in5      (1'b0),                               // (terminated)
		.reset_req_in5  (1'b0),                               // (terminated)
		.reset_in6      (1'b0),                               // (terminated)
		.reset_req_in6  (1'b0),                               // (terminated)
		.reset_in7      (1'b0),                               // (terminated)
		.reset_req_in7  (1'b0),                               // (terminated)
		.reset_in8      (1'b0),                               // (terminated)
		.reset_req_in8  (1'b0),                               // (terminated)
		.reset_in9      (1'b0),                               // (terminated)
		.reset_req_in9  (1'b0),                               // (terminated)
		.reset_in10     (1'b0),                               // (terminated)
		.reset_req_in10 (1'b0),                               // (terminated)
		.reset_in11     (1'b0),                               // (terminated)
		.reset_req_in11 (1'b0),                               // (terminated)
		.reset_in12     (1'b0),                               // (terminated)
		.reset_req_in12 (1'b0),                               // (terminated)
		.reset_in13     (1'b0),                               // (terminated)
		.reset_req_in13 (1'b0),                               // (terminated)
		.reset_in14     (1'b0),                               // (terminated)
		.reset_req_in14 (1'b0),                               // (terminated)
		.reset_in15     (1'b0),                               // (terminated)
		.reset_req_in15 (1'b0)                                // (terminated)
	);

endmodule
