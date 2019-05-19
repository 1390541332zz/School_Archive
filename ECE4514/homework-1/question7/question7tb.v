`timescale 1ns/1ns

module question7tb;

	reg [31:0] a,b;
	wire [31:0] sum;
	reg [7:0] cnt;
	
	question7 dut(a,b,sum);

	wire [31:0] test_a_array[0:15];
	wire [31:0] test_b_array[0:15];
	
	assign test_a_array[0]=32'd0;
	assign test_a_array[1]=32'd0;
	assign test_a_array[2]=32'd1;
	assign test_a_array[3]=32'd1;
	assign test_a_array[4]=32'd0;
	assign test_a_array[5]=32'd1;
	assign test_a_array[6]=32'd3;
	assign test_a_array[7]=32'hffff;
	assign test_a_array[8]=32'hffff;
	
	assign test_b_array[0]=32'd0;
	assign test_b_array[1]=32'd1;
	assign test_b_array[2]=32'd0;
	assign test_b_array[3]=32'd1;
	assign test_b_array[4]=32'd1;
	assign test_b_array[5]=32'd3;
	assign test_b_array[6]=32'd3;
	assign test_b_array[7]=32'd0;
	assign test_b_array[8]=32'd1;
	
	wire [31:0] exp_out[0:15];
	
	assign exp_out[0]=32'd0;
	assign exp_out[1]=32'd1;
	assign exp_out[2]=32'd1;
	assign exp_out[3]=32'd2;
	assign exp_out[4]=32'd1;
	assign exp_out[5]=32'd4;
	assign exp_out[6]=32'd6;
	assign exp_out[7]=32'hffff;
	assign exp_out[8]=32'h10000;

    initial begin
    cnt = 0;a=0;b=0;
    repeat (9)
      begin
        #99 // needed to enable simulator to compute dut
		a = test_a_array[cnt]; 
		b = test_b_array[cnt];
		#1
		if(sum !== exp_out[cnt])
		  $display("ERROR - output wrong for a:%x  b:%x saw %x but expected %x", a, b, sum, exp_out[cnt]);
 		cnt = cnt + 1;
      end
	
    $display("DONE");
    $finish;
    end

endmodule