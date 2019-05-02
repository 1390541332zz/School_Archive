`timescale 1ns/1ps

module tmonmul;
  parameter K = 8;
  parameter M = 8'd239;
  
  reg [K-1:0] x, y;
  reg         clk, reset, start;
  wire [K-1:0] z;
  wire done;

  monmul #(8, 8'd239) my_monmul(x,y,clk,reset,start,z,done);
  
  always #50 clk = ~clk;
  
  initial begin
    clk   = 0;
	reset = 1;
	start = 0;
    #25 reset = 0;
    #100    x = 202; y = 236; start = 1;
    #100    start = 0;
    @(posedge done) ;
    @(posedge clk) x = 203; y = 236; start = 1;
	#100    start = 0;
    @(posedge done);
    @(posedge clk)  x = 204; y = 236; start = 1;
	#100    start = 0;
    @(posedge done);
    @(posedge clk)  x = 205; y = 236; start = 1;
	#100    start = 0;
	end

endmodule
