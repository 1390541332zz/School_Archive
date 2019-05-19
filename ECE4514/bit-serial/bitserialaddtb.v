`timescale 1ns/1ns

module bitserialaddtb;

  reg clk;
  reg reset;
  reg a, b;
  wire q;

  bitserialadd dut(clk, reset, a, b, q);

  initial
  begin
  	reset = 1;
  	#200;
  	reset = 0;
  end

  always begin
  	clk = 1'b0;
  	#50;
  	clk = 1'b1;
  	#50;
  end

  wire [3:0] avec, bvec;
  assign avec = 4'b1011;
  assign bvec = 4'b1001;

  integer i;

  initial begin
    a = 0;
    b = 0;
    $monitor("t %8d state %d a %d b %d q %d", $time, dut.state, a, b, q);
    while (reset !== 1'b0)
      @(reset);
    for (i = 0 ; i < 4; i=i+1) begin
    	a = avec[i];
    	b = bvec[i];
    	@(posedge clk);
    end
    a = 0;
    b = 0;
    @(posedge clk);
    @(posedge clk);
    @(posedge clk);
    @(posedge clk);
    $finish;
    end

endmodule