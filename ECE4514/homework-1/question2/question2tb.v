`timescale 1ns/1ns

module question2tb;

	wire [2:0] a;
	wire [2:0] b;
	wire [2:0] out_or_bitwise;
	wire       out_or_logical;
	wire [5:0] out_not;
    reg  [2:0] cnt1;
	reg  [2:0] cnt2;

	question2 dut(a,b,out_or_bitwise,out_or_logical,out_not);

	assign a=cnt1;
	assign b=cnt2;

	wire [5:0] exp_out_not[0:15];//{6'h7,6'h6,6'h5,6'h4,6'h3,6'h2,6'h1,6'h0,6'h3f,6'h3e,6'h3d,6'h3c,6'h3b,6'h3a,6'h39,6'h38};
	assign exp_out_not[0]=6'h7; 
	assign exp_out_not[1]=6'h6;
	assign exp_out_not[2]=6'h5;
	assign exp_out_not[3]=6'h4;
	assign exp_out_not[4]=6'h3; 
	assign exp_out_not[5]=6'h2;
	assign exp_out_not[6]=6'h1;
	assign exp_out_not[7]=6'h0;
	assign exp_out_not[8]=6'h3f; 
	assign exp_out_not[9]=6'h3e;
	assign exp_out_not[10]=6'h3d;
	assign exp_out_not[11]=6'h3c;
	assign exp_out_not[12]=6'h3b; 
	assign exp_out_not[13]=6'h3a;
	assign exp_out_not[14]=6'h39;
	assign exp_out_not[15]=6'h38;
	
    wire [0:15] exp_out_or_logical = 16'b1111111101111111;
	
    wire [2:0] exp_out_or_bitwise[0:15];// = {3'h7,3'h7,3'h7,3'h7,3'h7,3'h7,3'h7,3'h7,3'h0,3'h1,3'h2,3'h3,3'h4,3'h5,3'h6,3'h7};
	assign exp_out_or_bitwise[0]=3'h7;
	assign exp_out_or_bitwise[1]=3'h7;
	assign exp_out_or_bitwise[2]=3'h7;
	assign exp_out_or_bitwise[3]=3'h7;
	assign exp_out_or_bitwise[4]=3'h7;
	assign exp_out_or_bitwise[5]=3'h7;
	assign exp_out_or_bitwise[6]=3'h7;
	assign exp_out_or_bitwise[7]=3'h7;
	assign exp_out_or_bitwise[8]=3'h0;
	assign exp_out_or_bitwise[9]=3'h1;
	assign exp_out_or_bitwise[10]=3'h2;
	assign exp_out_or_bitwise[11]=3'h3;
	assign exp_out_or_bitwise[12]=3'h4;
	assign exp_out_or_bitwise[13]=3'h5;
	assign exp_out_or_bitwise[14]=3'h6;
	assign exp_out_or_bitwise[15]=3'h7;
	
    initial begin
    cnt1 = 0;
	cnt2 = 7;
    repeat (8)
      begin
        #100 // needed to enable simulator to compute dut
        if (out_or_bitwise !== exp_out_or_bitwise[cnt1]) 
          $display("ERROR - out_or_bitwise wrong for a %d and b %d: saw %d but expected %d", cnt1, cnt2, out_or_bitwise, exp_out_or_bitwise[cnt1]);
		if (out_or_logical !== exp_out_or_logical[cnt1]) 
          $display("ERROR - out_or_logical wrong for a %d and b %d: saw %d but expected %d", cnt1, cnt2, out_or_logical, exp_out_or_logical[cnt1]);
		if (out_not !== exp_out_not[cnt1]) 
          $display("ERROR - out_not wrong for a %d and b %d: saw %d but expected %d", cnt1, cnt2, out_not, exp_out_not[cnt1]);
        cnt1 = cnt1 + 1;
      end
	cnt1 = 0;
	cnt2 = 0;
	repeat (8)
      begin
        #100 // needed to enable simulator to compute dut
        if (out_or_bitwise !== exp_out_or_bitwise[cnt1+8]) 
          $display("ERROR - out_or_bitwise wrong for a %d and b %d: saw %d but expected %d", cnt1, cnt2, out_or_bitwise, exp_out_or_bitwise[cnt1+8]);
		if (out_or_logical !== exp_out_or_logical[cnt1+8]) 
          $display("ERROR - out_or_logical wrong for a %d and b %d: saw %d but expected %d", cnt1, cnt2, out_or_logical, exp_out_or_logical[cnt1+8]);
		if (out_not !== exp_out_not[cnt1+8]) 
          $display("ERROR - out_not wrong for a %d and b %d: saw %d but expected %d", cnt1, cnt2, out_not, exp_out_not[cnt1+8]);
        cnt1 = cnt1 + 1;
      end
	
	
    $display("DONE");
    $finish;
    end

endmodule