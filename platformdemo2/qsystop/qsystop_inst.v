	qsystop u0 (
		.clk_clk         (<connected-to-clk_clk>),         //      clk.clk
		.ledout_export   (<connected-to-ledout_export>),   //   ledout.export
		.reset_reset_n   (<connected-to-reset_reset_n>),   //    reset.reset_n
		.switchin_export (<connected-to-switchin_export>), // switchin.export
		.hex0_readdata   (<connected-to-hex0_readdata>),   //     hex0.readdata
		.hex1_name       (<connected-to-hex1_name>),       //     hex1.name
		.hex2_readdata   (<connected-to-hex2_readdata>),   //     hex2.readdata
		.hex3_readdata   (<connected-to-hex3_readdata>),   //     hex3.readdata
		.hex4_readdata   (<connected-to-hex4_readdata>),   //     hex4.readdata
		.hex5_readdata   (<connected-to-hex5_readdata>)    //     hex5.readdata
	);

