module ALU_1(a, b, op, result, status);
    input  [7:0] a, b;
    input  [3:0] op;
    output [7:0] result;
    output [3:0] status; // VZCN

    parameter integer op_not    = 0;
    parameter integer op_and    = 1;
    parameter integer op_xnor   = 2;
    parameter integer op_lsl    = 3;
    parameter integer op_asr    = 4;
    parameter integer op_add    = 5;
    parameter integer op_sub    = 6;
    parameter integer op_inc    = 7;
    parameter integer op_dec    = 8;
    parameter integer op_neg    = 9;
    parameter integer op_multi8 = 10;
    parameter integer op_mod4   = 11;

    wire add_cin;
    wire [7:0] add_cout;
    wire s_overflow, s_carry;
    wire [7:0] add_a, add_b;
    wire [7:0] lsl_o, asr_o;
    wire [7:0] and_o,  xnor_o, not_o, not_b;
    wire [7:0] neg_o, mod4_o, multi8_o;
    wire [7:0] inc_o, dec_o,  add_o, sub_o;

    assign lsl_o = {b[6:0], 1'b0};
    assign asr_o = {{2{b[7]}}, b[6:1]};
    not   nota[7:0](not_o, a);
    not   notb[7:0](not_b, b);
    and   andg[7:0](and_o, a, b);
    xnor xnorg[7:0](xnor_o, a, b);

    assign add_cin = (op == op_sub) ? 1 :0;
    assign add_a   = (op == op_neg || op == op_mod4) ? not_o : a;
    assign add_b   = (op == op_add) ? b
                   : (op == op_sub) ? not_b
                   : (op == op_dec) ? -1
                                    : 1;

    add_8 addg(add_a, add_b, add_cin, add_o, add_cout);
    assign sub_o = add_o;
    assign inc_o = add_o;
    assign dec_o = add_o;
    assign neg_o = add_o;
    assign multi8_o = {b[4:0], 3'b0};
    assign mod4_o = {6'b0, (a[7]) ? neg_o[1:0] : a[1:0]};

    xor xorg(s_overflow, add_cout[7], add_cout[6]);

    assign status[3] = ((op == op_add)                                    // V
                     || (op == op_sub)
                     || (op == op_inc)
                     || (op == op_dec)
                     || (op == op_neg)) ? s_overflow : 0;
    assign status[2] = (result == 0) && (op != op_lsl) && (op != op_asr); // Z
    assign status[1] = ((op == op_add)                                    // C
                     || (op == op_sub)
                     || (op == op_inc)
                     || (op == op_dec)
                     || (op == op_neg)) ? add_cout[7] : 0;
    assign status[0] = result[7] && (op != op_lsl) && (op != op_asr);     // N

    assign result = (op == op_not)    ? not_o
                  : (op == op_and)    ? and_o
                  : (op == op_xnor)   ? xnor_o
                  : (op == op_lsl)    ? lsl_o
                  : (op == op_asr)    ? asr_o
                  : (op == op_add)    ? add_o
                  : (op == op_sub)    ? sub_o
                  : (op == op_inc)    ? inc_o
                  : (op == op_dec)    ? dec_o
                  : (op == op_neg)    ? neg_o
                  : (op == op_multi8) ? multi8_o
                  : (op == op_mod4)   ? mod4_o
                                      : 0;
endmodule

//----------------------------------------------------------------------------//
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

module add_8(a,b,cin,s,cout);
    input [7:0]a, b;
    input cin;
    output [7:0]s;
    output [7:0]cout;
    wire [7:0]c;
    assign c[0] = cin;
    assign c[7:1] = cout[6:0];
    full_adder fa0[7:0](a,b,c,s,cout);
endmodule
