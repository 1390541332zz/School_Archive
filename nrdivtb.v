module nrdivtb;
   wire [7:0] Z;
   wire [15:0] R;
   wire        done;
   reg 	       start;
   reg [15:0]  X;
   reg [15:0]  Y;
   reg 	       clk;

   nrdiv DUT(.Z(Z), .R(R), .done(done), .X(X), .Y(Y), .start(start), .clk(clk));
   
   always
     begin
	clk = 0;
	#25;
	clk = 1;
	#25;
     end
   
   initial 
     begin
	X = 16'd15644;
	Y = 16'd17124;
	start = 0;
	#200;
	start = 1;
	#50;
	start = 0;
     end
   
endmodule
