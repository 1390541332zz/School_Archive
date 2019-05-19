`timescale 1ns / 100ps

module tb_tv80;

  reg reset_n;
  reg clk;
  reg wait_n;
  reg int_n;
  reg nmi_n;
  reg busrq_n;
  reg [7:0] di;

  wire m1_n;
  wire mreq_n;
  wire iorq_n;
  wire rd_n;
  wire wr_n;
  wire rfsh_n;
  wire halt_n;
  wire busak_n;
  wire [15:0] address;
  wire [7:0] dout;

  tv80s mytv80(m1_n,      // m1 machine cycle
               mreq_n,    // memory access cycle
               iorq_n,    // IO access cycle
               rd_n,      // read control
               wr_n,      // write control
               rfsh_n,    // refresh cycle
               halt_n,    // cpu halted
               busak_n,   // bus acknowledge
               address,   // 16-bit address
               dout,      // 8-bit data output
               reset_n,   // reset input
               clk,       // clock
               wait_n,    // wait state input
               int_n,     // interrupt request input
               nmi_n,     // non-maskable interrupt input
               busrq_n,   // bus request input
               di);       // 8-bit data input

  reg [7:0] ram[0:255]; // 256 byte memory
   integer  i;
   
  initial
    begin
       for (i=0; i<255; i=i+1)
	 ram[i] = 8'h0;
       
       ram[8'h00] = 8'h26;
       ram[8'h01] = 8'h00;
       ram[8'h02] = 8'h2e;
       ram[8'h03] = 8'h3f;
       ram[8'h04] = 8'hf9;   
       ram[8'h05] = 8'h2e; 
       ram[8'h06] = 8'h40;
       ram[8'h07] = 8'h34;  
       ram[8'h08] = 8'hcb;  
       ram[8'h09] = 8'hc6;  
       ram[8'h0A] = 8'h18; 
       ram[8'h0B] = 8'hf9;
       ram[8'h66] = 8'he5;  
       ram[8'h67] = 8'h2e; 
       ram[8'h68] = 8'h42;
       ram[8'h69] = 8'h34; 
       ram[8'h6A] = 8'he1; 
       ram[8'h6B] = 8'hed;
       ram[8'h6C] = 8'h4d;
    end

  initial
    begin
      clk          = 1'h0;
      reset_n      = 1'h0;
      wait_n       = 1'h1;
      int_n        = 1'h1;
      nmi_n        = 1'h1;
      busrq_n      = 1'h1;
      #500 reset_n = 1'h1;       
    end

  always
    #50 clk = ~clk;

  always @*
    begin
      if (!mreq_n)
	begin
	  if (!rd_n)
	      di = ram[address];
          if (!wr_n)
              ram[address] = dout;
        end
    end

   initial
     begin
	#50000 nmi_n = 0;
	#100   nmi_n = 1;
     end
   
endmodule
