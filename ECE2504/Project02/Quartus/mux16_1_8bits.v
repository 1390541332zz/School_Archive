// **************************************************************
// You are not permitted to modify this file.
// ****************************************************************
//  Created by Tom Martin
//  15 October 2012
//
//  Last modified: RFM, 8/30/2015
//
//  RFM => Changed Default mux_out from 8'bx to 8hFF => Unknown output could make debugging more difficult
// 
//
// mux16_1_8bits is a 16-to-1 mux that is 8 bits wide
// 

module mux16_1_8bits(mux_out, select, i15, i14, i13, i12, i11, i10, i9, i8, i7, i6, i5, i4, i3, i2, i1, i0);
	output [7:0] mux_out;
	input [3:0] select;
	input [7:0] i15, i14, i13, i12, i11, i10, i9, i8, i7, i6, i5, i4, i3, i2, i1, i0;
	
	
	reg [7:0] mux_out;
	// The syntax of the always statement is that i
	always @(select, i15, i14, i13, i12, i11, i10, i9, i8, i7, i6, i5, i4, i3, i2, i1, i0)
	begin	
		// x and z values are NOT treated as don't-care's
		case(select)
			4'd0: mux_out = i0;
			4'd1: mux_out = i1;
			4'd2: mux_out = i2;
			4'd3: mux_out = i3;
			4'd4: mux_out = i4;
			4'd5: mux_out = i5;
			4'd6: mux_out = i6;
			4'd7: mux_out = i7;
			4'd8: mux_out = i8;
			4'd9: mux_out = i9;
			4'd10: mux_out = i10;
			4'd11: mux_out = i11;
			4'd12: mux_out = i12;
			4'd13: mux_out = i13;
			4'd14: mux_out = i14;
			4'd15: mux_out = i15;
			// The default should never happen.
			default: mux_out = 8'hFF;  
		endcase
    end


endmodule