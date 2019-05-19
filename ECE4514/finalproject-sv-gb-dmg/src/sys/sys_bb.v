
module sys (
	audio_cfg_out_SDAT,
	audio_cfg_out_SCLK,
	audio_clk_clk,
	audio_cntrlr_out_BCLK,
	audio_cntrlr_out_DACDAT,
	audio_cntrlr_out_DACLRCK,
	audio_l_in_data,
	audio_l_in_valid,
	audio_l_in_ready,
	audio_r_in_data,
	audio_r_in_valid,
	audio_r_in_ready,
	audio_reset_reset,
	audio_reset_n_reset_n,
	avalon_mm_in_address,
	avalon_mm_in_byte_enable,
	avalon_mm_in_read,
	avalon_mm_in_write,
	avalon_mm_in_write_data,
	avalon_mm_in_acknowledge,
	avalon_mm_in_read_data,
	clk_in_clk,
	display_fifo_in_data,
	display_fifo_in_valid,
	display_fifo_in_ready,
	display_fifo_out_data,
	display_fifo_out_valid,
	display_fifo_out_ready,
	dmg_clk_clk,
	dmg_double_clk_clk,
	dmg_reset_reset,
	dmg_reset_n_reset_n,
	pll_0_locked_export,
	ps2_cmd_in_data,
	ps2_cmd_in_valid,
	ps2_cmd_in_ready,
	ps2_data_out_data,
	ps2_data_out_valid,
	ps2_data_out_ready,
	ps2_out_CLK,
	ps2_out_DAT,
	reset_in_reset_n,
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
	sys_clk_clk,
	sys_reset_reset,
	sys_reset_n_reset_n,
	vga_clk_clk,
	vga_in_startofpacket,
	vga_in_endofpacket,
	vga_in_valid,
	vga_in_ready,
	vga_in_data,
	vga_out_CLK,
	vga_out_HS,
	vga_out_VS,
	vga_out_BLANK,
	vga_out_SYNC,
	vga_out_R,
	vga_out_G,
	vga_out_B,
	vga_reset_reset,
	vga_reset_n_reset_n);	

	inout		audio_cfg_out_SDAT;
	output		audio_cfg_out_SCLK;
	output		audio_clk_clk;
	input		audio_cntrlr_out_BCLK;
	output		audio_cntrlr_out_DACDAT;
	input		audio_cntrlr_out_DACLRCK;
	input	[15:0]	audio_l_in_data;
	input		audio_l_in_valid;
	output		audio_l_in_ready;
	input	[15:0]	audio_r_in_data;
	input		audio_r_in_valid;
	output		audio_r_in_ready;
	output		audio_reset_reset;
	output		audio_reset_n_reset_n;
	input	[26:0]	avalon_mm_in_address;
	input	[1:0]	avalon_mm_in_byte_enable;
	input		avalon_mm_in_read;
	input		avalon_mm_in_write;
	input	[15:0]	avalon_mm_in_write_data;
	output		avalon_mm_in_acknowledge;
	output	[15:0]	avalon_mm_in_read_data;
	input		clk_in_clk;
	input	[319:0]	display_fifo_in_data;
	input		display_fifo_in_valid;
	output		display_fifo_in_ready;
	output	[319:0]	display_fifo_out_data;
	output		display_fifo_out_valid;
	input		display_fifo_out_ready;
	input		dmg_clk_clk;
	output		dmg_double_clk_clk;
	output		dmg_reset_reset;
	output		dmg_reset_n_reset_n;
	output		pll_0_locked_export;
	input	[7:0]	ps2_cmd_in_data;
	input		ps2_cmd_in_valid;
	output		ps2_cmd_in_ready;
	output	[7:0]	ps2_data_out_data;
	output		ps2_data_out_valid;
	input		ps2_data_out_ready;
	inout		ps2_out_CLK;
	inout		ps2_out_DAT;
	input		reset_in_reset_n;
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
	output		sys_clk_clk;
	output		sys_reset_reset;
	output		sys_reset_n_reset_n;
	output		vga_clk_clk;
	input		vga_in_startofpacket;
	input		vga_in_endofpacket;
	input		vga_in_valid;
	output		vga_in_ready;
	input	[23:0]	vga_in_data;
	output		vga_out_CLK;
	output		vga_out_HS;
	output		vga_out_VS;
	output		vga_out_BLANK;
	output		vga_out_SYNC;
	output	[7:0]	vga_out_R;
	output	[7:0]	vga_out_G;
	output	[7:0]	vga_out_B;
	output		vga_reset_reset;
	output		vga_reset_n_reset_n;
endmodule
