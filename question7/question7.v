module question7 (
    input [31:0] a,
    input [31:0] b,
    output [31:0] sum
);
wire c, cout;

add16 a0(a[15:0 ], b[15:0 ], 1'b0, sum[15:0 ],    c);
add16 a1(a[31:15], b[31:15],    c, sum[31:16], cout);

endmodule

module add1 (
    input a,
    input b,
    input cin,
    output sum,
    output cout
);

assign sum  = ^{a, b, cin};
assign cout = ((a ^ b) & cin) | (a & b);

endmodule

module add16 (
    input[15:0] a,
    input[15:0] b,
    input cin,
    output[15:0] sum,
    output cout
);
wire[15:1] c;

add1 a00(a[ 0], b[ 0],   cin, sum[ 0], c[ 1]);
add1 a01(a[ 1], b[ 1], c[ 1], sum[ 1], c[ 2]);
add1 a02(a[ 2], b[ 2], c[ 2], sum[ 2], c[ 3]);
add1 a03(a[ 3], b[ 3], c[ 3], sum[ 3], c[ 4]);
add1 a04(a[ 4], b[ 4], c[ 4], sum[ 4], c[ 5]);
add1 a05(a[ 5], b[ 5], c[ 5], sum[ 5], c[ 6]);
add1 a06(a[ 6], b[ 6], c[ 6], sum[ 6], c[ 7]);
add1 a07(a[ 7], b[ 7], c[ 7], sum[ 7], c[ 8]);
add1 a08(a[ 8], b[ 8], c[ 8], sum[ 8], c[ 9]);
add1 a09(a[ 9], b[ 9], c[ 9], sum[ 9], c[10]);
add1 a10(a[10], b[10], c[10], sum[10], c[11]);
add1 a11(a[11], b[11], c[11], sum[11], c[12]);
add1 a12(a[12], b[12], c[12], sum[12], c[13]);
add1 a13(a[13], b[13], c[13], sum[13], c[14]);
add1 a14(a[14], b[14], c[14], sum[14], c[15]);
add1 a15(a[15], b[15], c[15], sum[15],  cout);

endmodule

