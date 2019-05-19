module question5 (
    input clk, 
    input reset, 
    input d, 
    output q
);
wire q0, q1;

my_dff d0(clk, reset,  d, q0);
my_dff d1(clk, reset, q0, q1);
my_dff d2(clk, reset, q1, q );
endmodule

//---------------------------------------------------------------------------//

module my_dff (
    input clk, 
    input reset,
    input d,
    output reg q 
);

always @(negedge reset, posedge clk) begin
    if (!reset)
        q <= 1'b0;
    else
        q <= d;
end
endmodule
