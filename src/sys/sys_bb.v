
module sys (
	audio_cfg_out_SDAT,
	audio_cfg_out_SCLK,
	audio_cntrlr_out_BCLK,
	audio_cntrlr_out_DACDAT,
	audio_cntrlr_out_DACLRCK,
	audio_left_in_data,
	audio_left_in_valid,
	audio_left_in_ready,
	audio_left_out_ready,
	audio_left_out_data,
	audio_left_out_valid,
	audio_right_in_data,
	audio_right_in_valid,
	audio_right_in_ready,
	audio_right_out_ready,
	audio_right_out_data,
	audio_right_out_valid,
	avalon_mm_in_address,
	avalon_mm_in_byte_enable,
	avalon_mm_in_read,
	avalon_mm_in_write,
	avalon_mm_in_write_data,
	avalon_mm_in_acknowledge,
	avalon_mm_in_read_data,
	clk_in_clk,
	dmg_double_clk_clk,
	pll_0_locked_export,
	ps2_cmd_in_data,
	ps2_cmd_in_valid,
	ps2_cmd_in_ready,
	ps2_data_out_ready,
	ps2_data_out_data,
	ps2_data_out_valid,
	ps2_out_CLK,
	ps2_out_DAT,
	sd_out_b_SD_cmd,
	sd_out_b_SD_dat,
	sd_out_b_SD_dat3,
	sd_out_o_SD_clock,
	vga_clk_clk,
	vga_in_data,
	vga_in_startofpacket,
	vga_in_endofpacket,
	vga_in_valid,
	vga_in_ready,
	vga_out_CLK,
	vga_out_HS,
	vga_out_VS,
	vga_out_BLANK,
	vga_out_SYNC,
	vga_out_R,
	vga_out_G,
	vga_out_B,
	sys_clk_clk,
	sdram_clk_clk,
	sdram_out_addr,
	sdram_out_ba,
	sdram_out_cas_n,
	sdram_out_cke,
	sdram_out_cs_n,
	sdram_out_dq,
	sdram_out_dqm,
	sdram_out_ras_n,
	sdram_out_we_n,
	hard_reset_reset);	

	inout		audio_cfg_out_SDAT;
	output		audio_cfg_out_SCLK;
	input		audio_cntrlr_out_BCLK;
	output		audio_cntrlr_out_DACDAT;
	input		audio_cntrlr_out_DACLRCK;
	input	[15:0]	audio_left_in_data;
	input		audio_left_in_valid;
	output		audio_left_in_ready;
	input		audio_left_out_ready;
	output	[15:0]	audio_left_out_data;
	output		audio_left_out_valid;
	input	[15:0]	audio_right_in_data;
	input		audio_right_in_valid;
	output		audio_right_in_ready;
	input		audio_right_out_ready;
	output	[15:0]	audio_right_out_data;
	output		audio_right_out_valid;
	input	[26:0]	avalon_mm_in_address;
	input	[1:0]	avalon_mm_in_byte_enable;
	input		avalon_mm_in_read;
	input		avalon_mm_in_write;
	input	[15:0]	avalon_mm_in_write_data;
	output		avalon_mm_in_acknowledge;
	output	[15:0]	avalon_mm_in_read_data;
	input		clk_in_clk;
	output		dmg_double_clk_clk;
	output		pll_0_locked_export;
	input	[7:0]	ps2_cmd_in_data;
	input		ps2_cmd_in_valid;
	output		ps2_cmd_in_ready;
	input		ps2_data_out_ready;
	output	[7:0]	ps2_data_out_data;
	output		ps2_data_out_valid;
	inout		ps2_out_CLK;
	inout		ps2_out_DAT;
	inout		sd_out_b_SD_cmd;
	inout		sd_out_b_SD_dat;
	inout		sd_out_b_SD_dat3;
	output		sd_out_o_SD_clock;
	output		vga_clk_clk;
	input	[29:0]	vga_in_data;
	input		vga_in_startofpacket;
	input		vga_in_endofpacket;
	input		vga_in_valid;
	output		vga_in_ready;
	output		vga_out_CLK;
	output		vga_out_HS;
	output		vga_out_VS;
	output		vga_out_BLANK;
	output		vga_out_SYNC;
	output	[7:0]	vga_out_R;
	output	[7:0]	vga_out_G;
	output	[7:0]	vga_out_B;
	output		sys_clk_clk;
	output		sdram_clk_clk;
	output	[12:0]	sdram_out_addr;
	output	[1:0]	sdram_out_ba;
	output		sdram_out_cas_n;
	output		sdram_out_cke;
	output		sdram_out_cs_n;
	inout	[15:0]	sdram_out_dq;
	output	[1:0]	sdram_out_dqm;
	output		sdram_out_ras_n;
	output		sdram_out_we_n;
	input		hard_reset_reset;
endmodule
