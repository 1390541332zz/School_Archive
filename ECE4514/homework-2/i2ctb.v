`timescale 1ns/1ns

// THIS FILE MUST REMAIN THE TOP-LEVEL MODULE OF YOUR SIMULATION
// YOU CANNOT MAKE CHANGES TO THIS FILE

module i2ctb;
   
   reg        clk;
   reg        reset;
   reg        init;
   wire       sck;
   wire       sda;
   
   i2cmasterwrite dut(.clk(clk),
                      .reset(reset),
                      .init(init),
                      .sck(sck),
                      .sda(sda));
   
   wire [7:0] myReg0;
   wire [7:0] myReg1;
   wire [7:0] myReg2;
   wire [7:0] myReg3;
   wire [7:0] myReg4;
   wire [7:0] myReg5;
   wire [7:0] myReg6;
   wire [7:0] myReg7;
   
   i2cSlave receiver(.clk(clk),
                     .rst(reset),
                     .sda(sda),
                     .scl(sck),
                     .myReg0(myReg0),
                     .myReg1(myReg1),
                     .myReg2(myReg2),
                     .myReg3(myReg3),
                     .myReg4(myReg4),
                     .myReg5(myReg5),
                     .myReg6(myReg6),
                     .myReg7(myReg7)
                     );
   
   initial
     begin
        reset = 1'b1;
        #200;
        reset = 1'b0;           
     end
   
   always 
     begin
        clk = 1'b0;
        #25;
        clk = 1'b1;
        #25;
     end
   
   initial
     begin
        $monitor("t %8d %3h %3h %3h %3h %3h %3h %3h %3h",
                 $time,
                 myReg0,
                 myReg1,
                 myReg2,
                 myReg3,
                 myReg4,
                 myReg5,
                 myReg6,
                 myReg7);
        #500;
        init    = 1'b1;
        #50;
        init    = 1'b0;
     end
   
endmodule
