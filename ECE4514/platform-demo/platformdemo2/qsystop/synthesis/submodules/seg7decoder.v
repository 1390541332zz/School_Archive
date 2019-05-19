module seg7decoder(input wire [3:0] x,
				   output reg [6:0] q);

	always @*
	    begin
        q = 7'b1000000;    	
		case (x)
			4'h0: q = 7'b1000000; //0  
			4'h1: q = 7'b1111001; //1
			4'h2: q = 7'b0100100; //2
			4'h3: q = 7'b0110000; //3
			4'h4: q = 7'b0011001; //4
			4'h5: q = 7'b0010010; //5
			4'h6: q = 7'b0000010; //6
			4'h7: q = 7'b1111000; //7
			4'h8: q = 7'b0000000; //8
			4'h9: q = 7'b0011000; //9
			4'ha: q = 7'b0001000; //a
			4'hb: q = 7'b0000011; //b
			4'hc: q = 7'b1000110; //c
			4'hd: q = 7'b0100001; //d
			4'he: q = 7'b0000110; //e
			4'hf: q = 7'b0001110; //f
 	    endcase
	    end

endmodule