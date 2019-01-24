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


module question9tb;

	reg a,b,reset;
	wire out_assign, out_always_comb, out_always_ff, clk;
	reg [7:0] cnt;
	
	//clock generation
	clkgen CLK (reset,clk);
	
	question9 dut(clk, a, b, out_assign, out_always_comb, out_always_ff);
	
	wire [0:9] test_a_array = 10'b001100110;
	wire [0:9] test_b_array = 10'b010101010;
	
	
    wire [0:9] exp_out_assign = 10'b011001100;
	wire [0:9] exp_out_always_comb = 10'b011001100;
	wire [0:9] exp_out_always_ff = 10'b001100110;


    initial begin
	cnt = 0; 
	a = 0;
	b = 0;
	reset = 1;
	#5
	reset = 0;
	#5
	reset = 1;
    repeat (10)
      begin
        #9 // needed to enable simulator to compute dut
		a = test_a_array[cnt]; 
		b = test_b_array[cnt];
		#1
		if(out_assign !== exp_out_assign[cnt])
		  $display("ERROR - out_assign wrong for a:%x  b:%x saw %x but expected %x", a, b, out_assign, exp_out_assign[cnt]);
		if(out_always_comb !== exp_out_always_comb[cnt])
		  $display("ERROR - out_always_comb wrong for a:%x  b:%x saw %x but expected %x", a, b, out_always_comb, exp_out_always_comb[cnt]);
		if(out_always_ff !== exp_out_always_ff[cnt])
		  $display("ERROR - out_always_ff wrong for a:%x  b:%x saw %x but expected %x", a, b, out_always_ff, exp_out_always_ff[cnt]);
 		cnt = cnt + 1;
      end
	
    $display("DONE");
    $finish;
    end

endmodule