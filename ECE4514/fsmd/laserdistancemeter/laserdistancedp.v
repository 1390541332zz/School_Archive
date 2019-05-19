module laserdistancedp(input  wire clk,
                       input wire 	  Qclr, Dclr, Dinc, Qupd,
                       output wire [15:0] D
                       );
   
   reg [15:0] 				  Dctr;
   wire [15:0] 				  Dctr_next;
   
   reg [15:0] 				  Q;
   wire [15:0] 				  Q_next;
   
   always @(posedge clk)
     begin
	Dctr <= Dctr_next;
	Q    <= Q_next;
     end
   
   assign Dctr_next = Dclr ? 16'b0 :
                      Dinc ? Dctr + 16'b1 :
                      Dctr;
   
   assign Q_next    = Qupd ? (Dctr >> 1) : 
                      Qclr ? 16'd0       : Q;
   
   assign D = Q;
   
endmodule
