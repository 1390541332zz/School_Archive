`timescale 1ns/1ns

module question10tb;

	wire [3:0] in;
	wire [1:0] pos;
	reg [3:0] cnt;
	reg [7:0] cnt2;
	
	question10 dut(in, pos);

	assign in = cnt;

	wire [1:0] exp_out[0:19];
	
	assign exp_out[0]=2'd0;
	assign exp_out[1]=2'd1;
	assign exp_out[2]=2'd2;
	assign exp_out[3]=2'd3;
	assign exp_out[4]=2'd0;
	assign exp_out[5]=2'd0;
	assign exp_out[6]=2'd1;
	assign exp_out[7]=2'd0;
	assign exp_out[8]=2'd2;
	assign exp_out[9]=2'd0;
	assign exp_out[10]=2'd1;
	assign exp_out[11]=2'd0;
	assign exp_out[12]=2'd3;
	assign exp_out[13]=2'd0;
	assign exp_out[14]=2'd1;
	assign exp_out[15]=2'd0;
	assign exp_out[16]=2'd2;
	assign exp_out[17]=2'd0;
	assign exp_out[18]=2'd1;
	assign exp_out[19]=2'd0;

    initial begin
    cnt = 1;cnt2 = 0;
    repeat (4)
      begin
        #100 // needed to enable simulator to compute dut
		if(pos !== exp_out[cnt2])
		  $display("ERROR - output wrong for in:%x saw %x but expected %x", in, pos, exp_out[cnt2]);
 		cnt = cnt * 2;
		cnt2 =  cnt2 + 1;
      end
	
	cnt = 0;
	repeat (16)
      begin
        #100 // needed to enable simulator to compute dut
		if(pos !== exp_out[cnt2])
		  $display("ERROR - output wrong for in:%x saw %x but expected %x", in, pos, exp_out[cnt2]);
 		cnt = cnt + 1;
		cnt2 =  cnt2 + 1;
      end
    	
	
    $display("DONE");
    $finish;
    end

endmodule