// Combinational Circuit 3
module comb_ckt_3(S,X,Y,R);
    input [3:0]X,Y;
    input [2:0]R;
    output [3:0]S;
    wire [3:0]n1, n2, n3, n4, n5;

    assign n1 = X + Y;
    assign n2 = X + Y + 1;
    assign n3 = X + ~Y;
    assign n4 = X + ~Y + 1;
    assign n5 = X;
    assign n6 = X + 1;
    assign n7 = X - 1;
    assign S = (R == 3'b000) ? n1 :
               (R == 3'b001) ? n2 :
               (R == 3'b010) ? n3 :
               (R == 3'b011) ? n4 :
               (R == 3'b100) ? n5 :
               (R == 3'b101) ? n6 :
               (R == 3'b110) ? n7 : 4'bx;
endmodule
