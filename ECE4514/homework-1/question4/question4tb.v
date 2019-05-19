`timescale 1ns/1ns

module question4tb;

	wire [7:0] in;
	wire [31:0] out;
	reg [7:0] cnt,cnt2;
	
	question4 dut(in,out);

	assign in = cnt;
	
	wire [31:0] exp_out[0:7];
	
	assign exp_out[0]=32'd0;
	assign exp_out[1]=32'd1;
	assign exp_out[2]=32'd2;
	assign exp_out[3]=32'd3;
	assign exp_out[4]=32'hffffffff;
	assign exp_out[5]=32'hfffffffe;
	assign exp_out[6]=32'hfffffffd;
	assign exp_out[7]=32'hfffffffc;

    initial begin
    cnt = 0;cnt2 = 0;
    repeat (4)
      begin
        #100 // needed to enable simulator to compute dut
		if(out !== exp_out[cnt2])
		  $display("ERROR - output wrong for in:%d saw %x but expected %x", in, out, exp_out[cnt2]);
 		cnt = cnt + 1;
		cnt2 = cnt2 + 1;
      end

	cnt = -1;
	repeat (4)
      begin
        #100 // needed to enable simulator to compute dut
		if(out !== exp_out[cnt2])
		  $display("ERROR - output wrong for in:%d saw %x but expected %x", in, out, exp_out[cnt2]);

 		cnt = cnt - 1;
		cnt2 = cnt2 + 1;
      end
	
    $display("DONE");
    $finish;
    end

endmodule