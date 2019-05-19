module ro16_mm (input wire 	   clk, 
		input wire 	   reset, 
		input wire         address, 
		input wire 	   read, 
		output reg [31:0] readdata, 
		input wire 	   write, 
		input wire [31:0]  writedata, 
		output reg 	   readdatavalid, 
		output wire 	   waitrequest 
		);
   
   reg [31:0] 			   reg00;
   reg [31:0] 			   readdata_read;
   wire [31:0] 			   r50;
   wire [31:0] 			   osc;
   
   ro16 myro16(.clk(clk),
	       .cmd(reg00),
	       .r50(r50),
	       .osc(osc));
   
   always @ (posedge clk) begin
      if (reset) begin
	 reg00 <= 0;
      end 
      else begin
	 reg00 <= (write & (address == 1'b0)) ? writedata : reg00;
      end
   end
   
   assign waitrequest = 1'b0;
   
   always @* begin
      readdata_read = 32'b0;
      if (read) begin
	 case (address)
	   1'b0: readdata_read = r50;
	   1'b1: readdata_read = osc;
	 endcase
      end
   end

   always @(posedge clk)
     begin
     readdatavalid <= read;
     readdata      <= readdata_read;
     end
   
endmodule
