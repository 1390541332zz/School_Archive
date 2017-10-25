module half_adder(a,b,s,cout);
    input a, b;
    output s, cout;

    xor g0(s, a, b);
    and g1(cout, a, b);
endmodule

module full_adder(a,b,cin,s,cout);
    input a, b, cin;
    output s, cout;
    wire has1, hac1, has2, hac2;
    half_adder g0(a,b,has1,hac1);
    half_adder g1(has1,cin,has2,hac2);
    or g2(cout, hac1, hac2);
    assign s=has2;
endmodule

module ripple_carry_adder(a,b,cin,s,cout);
    input [3:0]a;
    input [3:0]b;
    input cin;
    output [3:0]s;
    output cout;
    wire [2:0]c;
    full_adder fa0(a[0],b[0],cin,s[0],c[0]);
    full_adder fa1(a[1],b[1],c[0],s[1],c[1]);
    full_adder fa2(a[2],b[2],c[1],s[2],c[2]);
    full_adder fa3(a[3],b[3],c[2],s[3],cout);
endmodule
