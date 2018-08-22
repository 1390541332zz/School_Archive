// Combinational Circuit 1: Structural Verilog Description
module comb_ckt_1(f, x1, x2, x3, x4, x5);
    input x1, x2, x3, x4, x5;
    output f;

    wire n1, n2, n3, n4, n5;
    not
        g0(n4, n1),
        g1(n5, x4);
    and
        g2(n1, x1, x2),
        g3(n2, n4, x3),
        g4(n3, n4, n5);
    or
        g6(f, n1, n2, n3, x5);
endmodule
