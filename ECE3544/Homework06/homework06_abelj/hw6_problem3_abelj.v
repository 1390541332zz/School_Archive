module hw6_p3(
    input [1:0] a, b,
    input c_in,
    input clk,
    output [1:0] sum.
    output c_out
);

single_port_rom({c_in, a, b}, clk, {c_out, sum});

endmodule
