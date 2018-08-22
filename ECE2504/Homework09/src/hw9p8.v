module case_study_2 (R, x, y, cin, S);
    input cin;
    input [2:0]R;
    input [3:0]x, y;
    output [3:0]S;
    wire [3:0]muxo;

    multiplexer_4_to_1_cf_v
        m0(R, {y[0], ~y[0],1'b0,1'b1}, muxo[0]),
        m1(R, {y[1], ~y[1],1'b0,1'b1}, muxo[1]),
        m2(R, {y[2], ~y[2],1'b0,1'b1}, muxo[2]),
        m3(R, {y[3], ~y[3],1'b0,1'b1}, muxo[3]);
    ripple_carry_adder
        rca(x, muxo, cin, S,);
endmodule
