////////////////////////////////////////////////////////////
//  Filename     : clk_tb.v
//  Author       : T. Martin
//  Date         : 10/3/2013
//  Version      : 3
//  Description  : This module provides a testbench for the
// 		clk.v circuit, part of Project 1, Fall 2013.
//  		This module serves a a simple testbench for the
//  		CLK module.  Two CLKs are instantiated, and are
//  		stimulated with a simple sequence.
//
//		 	There are no inputs or outputs to this module.
//
//  Modification History:
//  Date      By    Version   Change Description
// ========================================================
//  09/07/04	TLM	1			Original
//  08/24/05	PMA	2			Restructured for Fall 2005
//  10/03/2013	TLM	3			Revised for Fall 2013 
//
`timescale 1ns/100ps

module clk_tb ();

	reg tb_enable1;		// Clock enable for CLK circuit M1
	reg tb_enable2;		// Clock enable for CLK circuit M2

	wire tb_clk1;			// Clock output for M1
	wire tb_clk2;			// Clock output for M2

	// Instantiate two versions of "clk".  The first will
	// be parameterized with a delay of 50 units, and the
	// second with a delay of 50 units.
	clk #(50)  M1 (tb_enable1, tb_clk1);
	clk #(100) M2 (tb_enable2, tb_clk2);

	// Sequence the ENABLE signals
	initial 
	begin
		tb_enable1 = 0; 
		tb_enable2 = 0;
		#100 tb_enable2 = 1;
		#100 tb_enable1 = 1;
		#400 tb_enable2 = 0;
		#100 tb_enable1 = 0;
		#100 tb_enable2 = 1;
		#100 tb_enable1 = 1;
	end
endmodule 
