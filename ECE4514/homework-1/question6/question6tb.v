`timescale 1ns/1ns
module clkgen(input reset, output reg clk);
	always
		begin
		
		if(reset==1'b0)
		#1	clk=1'b0;
		else
		#5	clk = !clk;
		end
endmodule

module question6tb;
	
	wire [7:0] q;
	reg [7:0] d;
	reg [1:0] sel;
	reg reset;
	
	//clock generation
	clkgen CLK (reset,clk);

	reg [7:0] cnt;
	
	question6 dut(clk,reset,d,sel,q);
	
	wire [7:0] test_d_array [0:31];
	assign test_d_array[0]=8'h4;
	assign test_d_array[1]=8'h5;
	assign test_d_array[2]=8'h6;
	assign test_d_array[3]=8'h7;
	assign test_d_array[4]=8'h8;
	assign test_d_array[5]=8'h9;
	assign test_d_array[6]=8'ha;
	assign test_d_array[7]=8'hb;
	assign test_d_array[8]=8'hc;
	assign test_d_array[9]=8'hd;
	assign test_d_array[10]=8'he;
	assign test_d_array[11]=8'hf;
	assign test_d_array[12]=8'h10;
	assign test_d_array[13]=8'h11;
	assign test_d_array[14]=8'h12;
	assign test_d_array[15]=8'h13;
	assign test_d_array[16]=8'h14;
	assign test_d_array[17]=8'h15;
	assign test_d_array[18]=8'h16;
	
	wire [7:0] exp_q [0:31];
	assign exp_q[0]=8'h3;
	assign exp_q[1]=8'h4;
	assign exp_q[2]=8'h5;
	assign exp_q[3]=8'h6;
	assign exp_q[4]=8'h7;
	assign exp_q[5]=8'h8;
	assign exp_q[6]=8'h9;
	assign exp_q[7]=8'ha;
	assign exp_q[8]=8'hb;
	assign exp_q[9]=8'hc;
	assign exp_q[10]=8'hc;
	assign exp_q[11]=8'hd;
	assign exp_q[12]=8'he;
	assign exp_q[13]=8'hf;
	assign exp_q[14]=8'h10;
	assign exp_q[15]=8'h10;
	assign exp_q[16]=8'h11;
	assign exp_q[17]=8'h12;
	assign exp_q[18]=8'h13;
	assign exp_q[19]=8'h14;
	

    initial begin
    cnt = 0; 
    d = 3;
    reset = 1;
    sel = 0;
	#5
	reset = 0;
	#5
	reset = 1;
    repeat (5)
      begin
        #10 // needed to enable simulator to compute dut
		d = test_d_array[cnt];
		//$display("testing d:%d q:%d cnt:%d", d, q, cnt);
		if(q !== exp_q[cnt])
		  $display("ERROR - output wrong for cycle number:%d saw %d but expected %d", cnt, q, exp_q[cnt]);
 		cnt = cnt + 1;
      end
	sel=1;
	repeat (5)
      begin
        #10 // needed to enable simulator to compute dut
		d = test_d_array[cnt];
		//$display("testing d:%d q:%d cnt:%d", d, q, cnt);
		if(q !== exp_q[cnt])
		  $display("ERROR - output wrong for cycle number:%d saw %d but expected %d", cnt, q, exp_q[cnt]);
 		cnt = cnt + 1;
      end
	  
	sel=2;
	repeat (5)
      begin
        #10 // needed to enable simulator to compute dut
		d = test_d_array[cnt];
		//$display("testing d:%d q:%d cnt:%d", d, q, cnt);
		if(q !== exp_q[cnt])
		  $display("ERROR - output wrong for cycle number:%d saw %d but expected %d", cnt, q, exp_q[cnt]);
 		cnt = cnt + 1;
      end
	  
	sel=3;
	repeat (5)
      begin
        #10 // needed to enable simulator to compute dut
		d = test_d_array[cnt];
		//$display("testing d:%d q:%d cnt:%d", d, q, cnt);
		if(q !== exp_q[cnt])
		  $display("ERROR - output wrong for cycle number:%d saw %d but expected %d", cnt, q, exp_q[cnt]);
 		cnt = cnt + 1;
      end

    $display("DONE");
    $finish;
    end

endmodule