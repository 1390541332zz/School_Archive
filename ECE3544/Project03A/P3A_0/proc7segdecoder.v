module proc7segdecoder(
    input [3:0] hex_digit,
    output [6:0] hex_display
);

reg [6:0] disp;

assign hex_display = disp;

always @(hex_digit) begin
    case (hex_digit)      //gfedcba
        0: disp = 7'b1000000;
        1: disp = 7'b1111001;
        2: disp = 7'b0100100;
        3: disp = 7'b0110000;
        4: disp = 7'b0011001;
        5: disp = 7'b0010010;
        6: disp = 7'b0000010;
        7: disp = 7'b1111000;
        8: disp = 7'b0000000;
        9: disp = 7'b0010000;
       10: disp = 7'b0001000;
       11: disp = 7'b0000011;
       12: disp = 7'b1000110;
       13: disp = 7'b0100001;
       14: disp = 7'b0000110;
       15: disp = 7'b0001110;
   endcase
end
endmodule
