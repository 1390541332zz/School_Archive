// synthesis verilog_input_version verilog_2001
module question10 (
    input [3:0] in,
    output reg [1:0] pos  
);

always @(*) casez (in)
    4'b0000: pos = 2'h0;
    4'b???1: pos = 2'h0;
    4'b??10: pos = 2'h1;
    4'b?100: pos = 2'h2;
    4'b1000: pos = 2'h3;
endcase

endmodule
