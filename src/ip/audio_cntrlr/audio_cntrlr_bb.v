
module audio_cntrlr (
	audio_0_reset,
	audio_0_AUD_BCLK,
	audio_0_AUD_DACDAT,
	audio_0_AUD_DACLRCK,
	audio_0_from_adc_left_channel_ready,
	audio_0_from_adc_left_channel_data,
	audio_0_from_adc_left_channel_valid,
	audio_0_from_adc_right_channel_ready,
	audio_0_from_adc_right_channel_data,
	audio_0_from_adc_right_channel_valid,
	audio_0_to_dac_left_channel_data,
	audio_0_to_dac_left_channel_valid,
	audio_0_to_dac_left_channel_ready,
	audio_0_to_dac_right_channel_data,
	audio_0_to_dac_right_channel_valid,
	audio_0_to_dac_right_channel_ready,
	clk_clk,
	reset_reset_n);	

	input		audio_0_reset;
	input		audio_0_AUD_BCLK;
	output		audio_0_AUD_DACDAT;
	input		audio_0_AUD_DACLRCK;
	input		audio_0_from_adc_left_channel_ready;
	output	[15:0]	audio_0_from_adc_left_channel_data;
	output		audio_0_from_adc_left_channel_valid;
	input		audio_0_from_adc_right_channel_ready;
	output	[15:0]	audio_0_from_adc_right_channel_data;
	output		audio_0_from_adc_right_channel_valid;
	input	[15:0]	audio_0_to_dac_left_channel_data;
	input		audio_0_to_dac_left_channel_valid;
	output		audio_0_to_dac_left_channel_ready;
	input	[15:0]	audio_0_to_dac_right_channel_data;
	input		audio_0_to_dac_right_channel_valid;
	output		audio_0_to_dac_right_channel_ready;
	input		clk_clk;
	input		reset_reset_n;
endmodule
