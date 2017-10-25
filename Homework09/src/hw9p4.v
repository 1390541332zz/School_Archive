// Combinational Circuit 2: Dataflow Verilog Description
module comb_ckt_2(y, a, b, c, d, e, f);
    input a, b, c, d, e, f;
    output y;
    wire n1, n2, n3, n4, n5;

    assign n1 = (~e & ~f) & a;
    assign n2 = e | ~f;
    assign n3 = e & ~f & c;
    assign n4 = ~d + ~e + ~f;
    assign n5 = ~n2 & b;
    assign y = n1 | n3 | ~n4 | n5;
endmodule
