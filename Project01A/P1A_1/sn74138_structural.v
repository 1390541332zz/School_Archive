////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    sn74138_structural.v
// Author:      Jason Thweatt
// Date:        05 September 2017
// Version:     1
// Description: This file contains a structural model for the 74138 3-to-8 decoder IC chip.
//              It uses primitive logic gates.
//              We are using it here as an introduction to the ModelSim environment.

module sn74138_structural(G1, G2a_n, G2b_n, C, B, A, Y_n);
   input        G1, G2a_n, G2b_n;	// Enable inputs: G1 is active-high, G2a and G2b are active-low.
   input        C, B, A;           	// Decoder inputs: C is the MSB. A is the LSB.
   output [7:0] Y_n;               	// Decoder outputs Y_n[7] to Y_n[0]. The outputs are active low.

   // Intermediate signals, declared as wires.
   wire         en2a, en2b;		// Inverted signals from the active-low enables.
   wire         C_n, B_n, A_n;		// Inverted decoder inputs.
   wire         en;                	// Intermediate signal for the enable inputs.

   // NOT gates produce the necessary inverted versions of the signals.
   not n1(en2a, G2a_n), n2(en2b, G2b_n), n3(C_n, C), n4(B_n, B), n5(A_n, A);

   // An AND function defines the enable condition.
   and a1(en, G1, en2a, en2b);		// en = 1 only if G1 = 1, G2a_n = 0, and G2b_n = 0.

   // NAND gates supply the active-low decoder outputs.
   nand out0(Y_n[0], en, C_n, B_n, A_n), out1(Y_n[1], en, C_n, B_n, A  ),
        out2(Y_n[2], en, C_n, B  , A_n), out3(Y_n[3], en, C_n, B  , A  ),
        out4(Y_n[4], en, C  , B_n, A_n), out5(Y_n[5], en, C  , B_n, A  ),
        out6(Y_n[6], en, C  , B  , A_n), out7(Y_n[7], en, C  , B  , A  );

endmodule
