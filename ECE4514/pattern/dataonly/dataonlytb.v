`timescale 1ns/1ps

module dataonlytb;

   reg clk;
   reg rst;
   reg data;
   wire found;

   dataonly DUT(.clk(clk),
   	            .rst(rst),
   	            .data(data),
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
      data = $random % 2;
      @(posedge clk);
      end

    always
      begin
      @(posedge clk);
      $display("t %5d data %d found %d", $time, data, found);
      end

endmodule
