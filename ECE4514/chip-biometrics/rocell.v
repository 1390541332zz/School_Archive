module inv_cell
  (input wire  a,
   output wire q);
   wire        aw;
   lut_input  lut_a(a, aw);
   lut_output lut_q(~aw, q);
endmodule // inv_cell

module nand_cell
  (input wire  a,
   input wire  b,
   output wire q);
   wire        aw;
   wire        bw;
   lut_input  lut_a(a, aw);
   lut_input  lut_b(b, bw);
   lut_output lut_q(~aw | ~bw, q);
endmodule // nand_cell

module ro
  (input wire en,
   output wire q);
   parameter STAGES = 9;
   wire [0:(STAGES-2)] ni;
   wire 	       nandout /* synthesis keep = 1 */;
   wire [0:(STAGES-2)] no      /* synthesis keep = 1 */;
   
   nand_cell nc(en, no[(STAGES-2)], nandout);
   inv_cell  ic[0:(STAGES-2)] (ni, no);
   
   assign ni[0]            = nandout;	
   assign ni[1:(STAGES-2)] = no[0:(STAGES-3)];
   assign q                = no[(STAGES-3)];
endmodule

module rocell(input wire en,
	      output wire q);

   ro myro(en, q);

endmodule