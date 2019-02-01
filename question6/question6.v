module question6 ( 
    input clk,
	input reset,
    input [7:0] d, 
    input [1:0] sel, 
    output [7:0] q 
);

wire [7:0] q0, q1, q2;

my_dff8 d0(clk, reset,  d, q0);
my_dff8 d1(clk, reset, q0, q1);
my_dff8 d2(clk, reset, q1, q2);

always @(*) case (sel)
    2'h0: q = d;
    2'h1: q = q0;
    2'h2: q = q1;
    2'h3: q = q2;
endcase

endmodule

//---------------------------------------------------------------------------//

module my_dff8 (
    input clk,
    input reset,
    input [7:0] d,
    output reg [7:0] q
);

always @(negedge reset, posedge clk) begin
    if (!reset)
        q <= 8'b0;
    else
        q <= d;
end
endmodule
