module p3_comb_ckt (x2, x1, x0, a, b, c, d);
    input x2, x1, x0;
    output a, b, c, d;
    wire [2:0]nx;
    wire [5:0]lvl1o;

    not
        n0(nx[0], x0),
        n1(nx[1], x1),
        n2(nx[2], x2);
    and
        a0(lvl1o[0], x1, nx[0]),
        a1(lvl1o[1], x1, nx[2]),
        a2(lvl1o[2], x2, nx[1]),
        a3(lvl1o[3], x2, nx[0]),
        a4(lvl1o[4], x0, nx[1]),
        a5(lvl1o[5], x0, nx[2]),
        a6(c, lvl1o[3], x1);
    or
        o0(a, lvl1o[0], lvl1o[1], lvl1o[2]),
        o1(b, lvl1o[2], lvl1o[3]),
        o2(d, lvl1o[4], lvl1o[5]);
endmodule
