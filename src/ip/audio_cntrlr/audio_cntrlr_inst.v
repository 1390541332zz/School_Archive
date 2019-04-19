	audio_cntrlr u0 (
		.audio_0_reset                        (<connected-to-audio_0_reset>),                        //                       audio_0_reset.reset
		.audio_0_AUD_BCLK                     (<connected-to-audio_0_AUD_BCLK>),                     //          audio_0_external_interface.BCLK
		.audio_0_AUD_DACDAT                   (<connected-to-audio_0_AUD_DACDAT>),                   //                                    .DACDAT
		.audio_0_AUD_DACLRCK                  (<connected-to-audio_0_AUD_DACLRCK>),                  //                                    .DACLRCK
		.audio_0_from_adc_left_channel_ready  (<connected-to-audio_0_from_adc_left_channel_ready>),  //  audio_0_avalon_left_channel_source.ready
		.audio_0_from_adc_left_channel_data   (<connected-to-audio_0_from_adc_left_channel_data>),   //                                    .data
		.audio_0_from_adc_left_channel_valid  (<connected-to-audio_0_from_adc_left_channel_valid>),  //                                    .valid
		.audio_0_from_adc_right_channel_ready (<connected-to-audio_0_from_adc_right_channel_ready>), // audio_0_avalon_right_channel_source.ready
		.audio_0_from_adc_right_channel_data  (<connected-to-audio_0_from_adc_right_channel_data>),  //                                    .data
		.audio_0_from_adc_right_channel_valid (<connected-to-audio_0_from_adc_right_channel_valid>), //                                    .valid
		.audio_0_to_dac_left_channel_data     (<connected-to-audio_0_to_dac_left_channel_data>),     //    audio_0_avalon_left_channel_sink.data
		.audio_0_to_dac_left_channel_valid    (<connected-to-audio_0_to_dac_left_channel_valid>),    //                                    .valid
		.audio_0_to_dac_left_channel_ready    (<connected-to-audio_0_to_dac_left_channel_ready>),    //                                    .ready
		.audio_0_to_dac_right_channel_data    (<connected-to-audio_0_to_dac_right_channel_data>),    //   audio_0_avalon_right_channel_sink.data
		.audio_0_to_dac_right_channel_valid   (<connected-to-audio_0_to_dac_right_channel_valid>),   //                                    .valid
		.audio_0_to_dac_right_channel_ready   (<connected-to-audio_0_to_dac_right_channel_ready>),   //                                    .ready
		.clk_clk                              (<connected-to-clk_clk>),                              //                                 clk.clk
		.reset_reset_n                        (<connected-to-reset_reset_n>)                         //                               reset.reset_n
	);

