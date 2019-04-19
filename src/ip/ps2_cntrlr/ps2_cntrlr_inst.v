	ps2_cntrlr u0 (
		.ps2_0_reset         (<connected-to-ps2_0_reset>),         //                   ps2_0_reset.reset
		.ps2_0_PS2_CLK       (<connected-to-ps2_0_PS2_CLK>),       //      ps2_0_external_interface.CLK
		.ps2_0_PS2_DAT       (<connected-to-ps2_0_PS2_DAT>),       //                              .DAT
		.ps2_0_command       (<connected-to-ps2_0_command>),       // ps2_0_avalon_ps2_command_sink.data
		.ps2_0_command_valid (<connected-to-ps2_0_command_valid>), //                              .valid
		.ps2_0_command_ready (<connected-to-ps2_0_command_ready>), //                              .ready
		.ps2_0_data_ready    (<connected-to-ps2_0_data_ready>),    //  ps2_0_avalon_ps2_data_source.ready
		.ps2_0_data          (<connected-to-ps2_0_data>),          //                              .data
		.ps2_0_data_valid    (<connected-to-ps2_0_data_valid>),    //                              .valid
		.clk_clk             (<connected-to-clk_clk>),             //                           clk.clk
		.reset_reset_n       (<connected-to-reset_reset_n>)        //                         reset.reset_n
	);

