`timescale 1ns/1ns

module question3tb;

	reg [4:0] a,b,c,d,e,f;
	reg [3:0] cnt;
	wire [7:0] w,x,y,z;
	wire [31:0] concat_out;
	assign concat_out={w,x,y,z};

	question3 dut(a,b,c,d,e,f,w,x,y,z);

	wire [31:0] exp_out[0:11];
	assign exp_out[0]={8'h0,8'h0,8'h0,8'h3};
	assign exp_out[1]={8'h0,8'h0,8'h0,8'h7};
	assign exp_out[2]={8'h0,8'h0,8'h0,8'hb};
	assign exp_out[3]={8'h0,8'h0,8'h0,8'h13};
	assign exp_out[4]={8'h0,8'h0,8'h0,8'h23};
	assign exp_out[5]={8'h0,8'h0,8'h0,8'h43};
	assign exp_out[6]={8'h0,8'h0,8'h0,8'h83};
	assign exp_out[7]={8'h0,8'h0,8'h1,8'h3};
	assign exp_out[8]={8'h0,8'h0,8'h2,8'h3};
	assign exp_out[9]={8'h0,8'h0,8'h4,8'h3};
	assign exp_out[10]={8'h0,8'h0,8'h8,8'h3};
	assign exp_out[11]={8'h0,8'h0,8'h10,8'h3};

    initial begin
    a = 0; b = 0; c = 0; d = 0; e = 0; f = 0; cnt = 0;
    repeat (6)
      begin
        #100 // needed to enable simulator to compute dut
		if(concat_out !== exp_out[cnt])
		  $display("ERROR - output wrong for a:%d b:%d c:%d d:%d e:%d f:%d saw %d but expected %d", a, b, c, d, e, f, concat_out, exp_out[cnt]);
        if(cnt==0)
			f = f+1;
		else
			f = f * 2;

 		cnt = cnt + 1;
      end

	f = 0; e = 1;
	repeat (5)
      begin
        #100 // needed to enable simulator to compute dut
		if(concat_out !== exp_out[cnt])
		  $display("ERROR - output wrong for a:%d b:%d c:%d d:%d e:%d f:%d saw %d but expected %d", a, b, c, d, e, f, concat_out, exp_out[cnt]);

		e = e * 2;
 		cnt = cnt + 1;
      end
	
	
    $display("DONE");
    $finish;
    end

endmodule