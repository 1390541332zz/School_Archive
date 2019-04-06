module ballpixel
  #(parameter RADIUS = 16)
    (input wire clk,
    input wire rst,
    input wire [10:0]  bx,
    input wire [10:0]  by,
    input wire [10:0]  px,
    input wire [10:0]  py,
    output wire        ball_color);

   wire [10:0] 	       x_left, x_right, y_top, y_bottom;
   wire 	       inball;
   wire [4:0] 	       ball_y, ball_x;
   reg [31:0] 	       rom_data;
   wire [4:0] 	       rom_addr;
   wire                rom_bit;
   
   assign x_left     = bx - RADIUS;
   assign x_right    = bx + RADIUS;
   assign y_top      = by - RADIUS;
   assign y_bottom   = by + RADIUS;
   
   assign inball     = (px >= x_left) && (px <= x_right) &&
		       (py >=  y_top) && (py <= y_bottom);
   
   assign ball_x     = inball ? px - x_left : 0;
   assign ball_y     = inball ? py - y_top : 0;
   
   assign rom_addr   = ball_y;
   assign rom_bit    = rom_data[ball_x];
   
   assign ball_color = rom_bit;

   always @*
     case (rom_addr)
       5'h00: rom_data = 32'b00000000000011111111000000000000; 
       5'h01: rom_data = 32'b00000000011111111111111000000000; 
       5'h02: rom_data = 32'b00000000111111111111111100000000; 
       5'h03: rom_data = 32'b00000011111111111111111111000000; 
       5'h04: rom_data = 32'b00000111111111111111111111100000; 
       5'h05: rom_data = 32'b00001111111111111111111111110000; 
       5'h06: rom_data = 32'b00011111111111111111111111111000; 
       5'h07: rom_data = 32'b00011111111111111111111111111000; 
       5'h08: rom_data = 32'b00111111111111111111111111111100; 
       5'h09: rom_data = 32'b01111111111111111111111111111110; 
       5'h0a: rom_data = 32'b01111111111111111111111111111110; 
       5'h0b: rom_data = 32'b01111111111111111111111111111110; 
       5'h0c: rom_data = 32'b11111111111111111111111111111111; 
       5'h0d: rom_data = 32'b11111111111111111111111111111111; 
       5'h0e: rom_data = 32'b11111111111111111111111111111111; 
       5'h0f: rom_data = 32'b11111111111111111111111111111111; 
       5'h10: rom_data = 32'b11111111111111111111111111111111; 
       5'h11: rom_data = 32'b11111111111111111111111111111111; 
       5'h12: rom_data = 32'b11111111111111111111111111111111; 
       5'h13: rom_data = 32'b11111111111111111111111111111111; 
       5'h14: rom_data = 32'b01111111111111111111111111111110; 
       5'h15: rom_data = 32'b01111111111111111111111111111110; 
       5'h16: rom_data = 32'b01111111111111111111111111111110; 
       5'h17: rom_data = 32'b00111111111111111111111111111100; 
       5'h18: rom_data = 32'b00011111111111111111111111111000; 
       5'h19: rom_data = 32'b00011111111111111111111111111000; 
       5'h1a: rom_data = 32'b00001111111111111111111111110000; 
       5'h1b: rom_data = 32'b00000111111111111111111111100000; 
       5'h1c: rom_data = 32'b00000011111111111111111111000000; 
       5'h1d: rom_data = 32'b00000000111111111111111100000000; 
       5'h1e: rom_data = 32'b00000000011111111111111000000000; 
       5'h1f: rom_data = 32'b00000000000011111111000000000000; 
     endcase

endmodule 

