// 4-to-1-Line Multiplexer: Dataflow Verilog Description
module multiplexer_4_to_1_cf_v(S, I, Y);
    input [1:0] S;
    input [3:0] I;
    output Y;

	 assign Y = (S ==2'b00) ? I[0] :
               (S ==2'b01) ? I[1] :
               (S ==2'b10) ? I[2] :
               (S ==2'b11) ? I[3] : 1'bx;
endmodule
