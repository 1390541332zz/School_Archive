module quadratic(input signed  [9: 0] in,
                 output signed [9: 0] out);

  parameter CONST_0_85 = (0.85 * 32);
  parameter CONST_1    = (1    * 32);

  wire signed [19: 0] square;
  wire   ovfsquare, ovfsign;

  assign square    = in * in;
  assign ovfsquare = (square[19:15] != 5'b11111) && 
                     (square[19:15] != 5'b00000);

  wire signed [19: 0] cmul;
  assign cmul = CONST_0_85 * square[15:5];

  wire signed [9:0] result;
  assign result = cmul[15:5] + CONST_1;

  assign ovfsign   = result[9];

  assign out = (ovfsquare || ovfsign) ? 10'd0 : result;

endmodule
