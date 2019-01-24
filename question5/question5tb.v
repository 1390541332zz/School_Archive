`timescale 1ns/1ns
module clkgen(input reset, output reg clk);
	always
		begin
		#5
		if(reset==1'b0)
			clk=1'b0;
		else
			clk = !clk;
		end
endmodule

module question5tb;
	
	wire d,q;
	reg d_test,reset;
	
	//clock generation
	clkgen CLK (reset,clk);
	
	assign d = d_test;
	reg [7:0] cnt;
	
	question5 dut(clk,reset,d,q);
	
	wire [0:31] test_d_array = 32'b00001111001100000000110000000011;
    wire [0:31] exp_q = 32'b00000000011110011000000001100000;
	

    initial begin
    cnt = 0; d_test=1'b0;reset=1;
	#5
	reset=0;
	#5
	reset=1;
    repeat (32)
      begin
        #5 // needed to enable simulator to compute dut
		d_test = test_d_array[cnt];
		//$display("testing d:%d q:%d cnt:%d", d, q, cnt);
		if(q !== exp_q[cnt])
		  $display("ERROR - output wrong for cycle number:%d saw %d but expected %d", cnt, q, exp_q[cnt]);
 		cnt = cnt + 1;
      end

    $display("DONE");
    $finish;
    end

endmodule