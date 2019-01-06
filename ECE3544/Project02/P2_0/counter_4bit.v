/////////////////////////////////////////////////////////////////
//  Filename     : counter_4bit.v
//  Author       : T. Martin
//  Date         : 09/07/04
//  Version      : 3
//  Description  : This module is a behavioral description of
// 		a simple four-bit counter with enable and
// 		asynchronous clear.
//
// 		This module has three inputs and one output:
//					clk:	input - system clock
//					clear:	input -	asynchronous clear (active high)
// 				enable:	input - count advances when asserted high
//					cout:	output - 4-bit counter output
//
// 		This module has two parameters:
//					CLRDEL	- delay from clear asserted to output valid
// 				CLKDEL	- delay from clk rising to output valid
//
//
//   		This module is not synthesizable.  It is intended
// 		for modeling only and should not be used as a
// 		template for synthesizable modules. 
//
//  Modification History:
//  Date      By    Version   Change Description
// ========================================================
//  09/07/04	TLM	1			Original
//  08/24/05	PMA	2			Restructured for Fall 2005
//  10/03/2013	TLM  3 			Revised for DD 1, fall 2013
//

`timescale 1 ns/100 ps
module counter_4bit (enable, clear, clk, cout);
	parameter CLRDEL = 5;	// delay from clear asserted to output valid
  	parameter CLKDEL = 10;	// delay from clk rising to output valid

	input 	enable;			// count advances when asserted high
   input 	clear;			// asynchronous clear (active high)
  	input		clk;				// system clock
	output [3:0] cout;		// 4-bit counter output

	reg [3:0] cout;			// cout is a reg

	// Locally declared nets
	reg [3:0] count;			// local count holder register

	initial count = 0;

	// Build behavioral 4-bit up-counter with asynchronous clear
	always @(posedge clk or posedge clear)
	begin
		if (clear == 1) 
			begin
				count = 4'b0;
				cout = #CLRDEL count;
			end
		else if (clk == 1) 
			begin
				if (enable == 1) 
					begin
						if (count == 4'd15) 
							count = 0;
						else
							count = count + 4'd1;
					end	
				cout =  #CLKDEL count;
			end
	end
endmodule
