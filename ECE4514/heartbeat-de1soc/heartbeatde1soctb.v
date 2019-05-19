`timescale 1ns/ 1ns

module heartbeatde1soctb;

  reg CLOCK_50;
  reg CLOCK2_50;
  reg CLOCK3_50;
  reg CLOCK4_50;

  wire [9:0] LEDR;
  reg [3:0] KEY;
  wire dangling;
  
  heartbeatde1soc dut(CLOCK2_50,
  	                  CLOCK3_50,
  	                  CLOCK4_50,
                      CLOCK_50,
                      KEY,
  	                  LEDR);

  always #10 CLOCK_50 <= ~CLOCK_50;

  initial
    begin
      $monitor("t=%8d LEDR=%10b", $time, LEDR);
    	CLOCK_50  <= 0;
    	CLOCK2_50 <= 0;
    	CLOCK3_50 <= 0;
      CLOCK4_50 <= 0;
    	KEY <= 4'hf;
    	#500 KEY[0] <= 0;
    	#1000 KEY[0] <= 1;
    end

endmodule 
