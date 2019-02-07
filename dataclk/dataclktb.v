`timescale 1ns/1ps

module dataclktb;

   reg clk;
   reg rst;
   reg data;
   reg dataclk;
   wire found;

   dataclk  DUT(.clk(clk),
   	            .rst(rst),
   	            .data(data),
                .dataclk(dataclk),
   	            .found(found));

   always 
   	begin
   	  clk = 1'b0;
   	  #10;
   	  clk = 1'b1;
   	  #10;
    end

   initial
    begin
      rst = 1;
      #50;
      rst = 0;	
    end

    always 
      begin
        dataclk = 1'b0;
        @(negedge clk);
        dataclk = 1'b1;
        @(negedge clk);       
      end

    always 
      begin
        data = $random % 2;
        @(negedge dataclk);
      end

    always
      begin
        @(posedge clk);
        $display("t %5d data %d dataclk %d found %d", $time, data, dataclk, found);
      end

endmodule
