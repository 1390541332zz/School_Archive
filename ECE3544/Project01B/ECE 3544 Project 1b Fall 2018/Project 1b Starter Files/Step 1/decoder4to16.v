////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    decoder4to16.v
// Author:      Jason Thweatt
// Date:        24 September 2017
// Version:     1
// Description: This file contains a 4-to-16 decoder.
//              It uses two SN74138 decoders and an inverter.
//              We are using it here as an introduction to the ModelSim environment.

module decoder4to16(en_n, S, W_n);
   input         en_n;		// Active-low enable input for the 4-to-16 decoder
   input  [3:0]  S;		// Decoder inputs: S[3] is the MSB. S[0] is the LSB.
   output [15:0] W_n;		// Active-low decoder outputs W_n[0] to W_n[15].

// INSTANTIATE two SN74138 decoders as "structural" blocks.
// - S[3] (from the 4-to-16 decoder) is used to control the active-high input of the 3-to-8 decoders.
// - The "lower" decoder should be active when S[3] = 0.
//   The "upper" decoder should be active when S[3] = 1.
// - S[2:0] (from the 4-to-16) decoder provides the inputs of both 3-to-8 decoders.
// - The 4-to-16 decoder's active low enable controls the two active-low enables of both 3-to-8 decoders.
// - The outputs of the "lower" decoder are the lower 8 outputs of the 4-to-16 decoder.
//   The outputs of the "upper" decoder are the upper 8 outputs of the 4-to-16 decoder.

   sn74138_continuous U1(~S[3], en_n, en_n, S[2], S[1], S[0], W_n[ 7:0]);
   sn74138_continuous U2( S[3], en_n, en_n, S[2], S[1], S[0], W_n[15:8]);

endmodule
