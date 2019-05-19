module laserdistancefsmd(input wire clk,
                         input wire 	    reset,
                         input wire 	    B,
                         input wire 	    S,
                         output wire 	    L,
                         output wire [15:0] D);
   
   reg 					    Qclr, Dclr, Dinc, Qupd, Lctl;
                         
   laserdistancedp mydp(clk, Qclr, Dclr, Dinc, Qupd, D);
   
   localparam S0 = 3'd0, S1 = 3'd1, S2 = 3'd2, S3 = 3'd3, S4 = 3'd4;
   
   reg [2:0] 				    state, nextstate;
   
   always @(posedge clk, posedge reset)
     if (reset)
       state <= S0;
     else
       state <= nextstate;
   
    always @(*)
      begin
	 Qclr      = 1'b0;
	 Dclr      = 1'b0;
	 Dinc      = 1'b0;
	 Qupd      = 1'b0;
	 Lctl      = 1'b0;
	 nextstate = S0;
	 case (state)
	   
           S0: begin
              Qclr      = 1'b1;
              nextstate = S1;
           end
	   
           S1: if (B) 
             begin
                Lctl       = 1'b1;
                nextstate  = S2;
             end 
           else 
             begin
                Dclr       = 1'b1;
                nextstate  = S1;
             end
	   
           S2: nextstate = S3;
	   
           S3: if (S)
             begin
		Qupd        = 1'b1;
		nextstate   = S4;
             end
           else
             begin
		Dinc        = 1'b1;
		nextstate   = S3;
             end

           S4: nextstate = S1;
	   
           default: nextstate = S0;
	   
	 endcase
      end
   
   assign L = Lctl;  
   
endmodule
