`timescale 1ns/1ns

module question8tb;

	reg [31:0] a,b;
	reg sub;
	wire [31:0] sum;
	reg [7:0] cnt;
	
	question8 dut(a,b,sub,sum);

	wire [31:0] test_a_array[0:15];
	wire [31:0] test_b_array[0:15];
	wire        test_sub_array[0:15];
	
	assign test_a_array[0]=32'h0;
	assign test_a_array[1]=32'h1;
	assign test_a_array[2]=32'h2;
	assign test_a_array[3]=32'h2;
	assign test_a_array[4]=32'h2;
	assign test_a_array[5]=32'hffff;
	assign test_a_array[6]=32'h10000;
	assign test_a_array[7]=32'hffffffff;
	
	assign test_b_array[0]=32'd0;
	assign test_b_array[1]=32'd0;
	assign test_b_array[2]=32'd0;
	assign test_b_array[3]=32'd1;
	assign test_b_array[4]=32'd2;
	assign test_b_array[5]=32'd1;
	assign test_b_array[6]=32'd1;
	assign test_b_array[7]=32'hffffffff;
	
	assign test_sub_array[0]=1'b0;
	assign test_sub_array[1]=1'b0;
	assign test_sub_array[2]=1'b0;
	assign test_sub_array[3]=1'b1;
	assign test_sub_array[4]=1'b1;
	assign test_sub_array[5]=1'b0;
	assign test_sub_array[6]=1'b1;
	assign test_sub_array[7]=1'b0;
	
	wire [31:0] exp_out[0:15];
	
	assign exp_out[0]=32'd0;
	assign exp_out[1]=32'd1;
	assign exp_out[2]=32'd2;
	assign exp_out[3]=32'd1;
	assign exp_out[4]=32'd0;
	assign exp_out[5]=32'h10000;
	assign exp_out[6]=32'hffff;
	assign exp_out[7]=32'hfffffffe;

    initial begin
    cnt = 0;
    a   = 0;
    b   = 0;
    sub = 0;
    repeat (8)
      begin
        #99 // needed to enable simulator to compute dut
		a   = test_a_array[cnt]; 
		b   = test_b_array[cnt];
		sub = test_sub_array[cnt];
		#1
		if(sum !== exp_out[cnt])
		  $display("ERROR - output wrong for a:%x  b:%x saw %x but expected %x", a, b, sum, exp_out[cnt]);
 		cnt = cnt + 1;
      end
	
    $display("DONE");
    $finish;
    end

endmodule