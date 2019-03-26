module XGA_testpattern(
    input  wire       CLOCK_50,
    input  wire [3:0] KEY,
	 input  wire [9:0] SW,
    output wire [7:0] VGA_R,
    output wire [7:0] VGA_G,
    output wire [7:0] VGA_B,
    output wire       VGA_CLK,
    output wire       VGA_BLANK_N,
    output wire       VGA_SYNC_N,
    output wire       VGA_HS,
    output wire       VGA_VS);

   wire 	      rst;
   wire 	      in_clock;
   wire 	      sys_clock;
   wire 	      locked;

   wire 	      hsync;
   wire 	      vsync;
   wire 	      csync;
   wire 	      video_on;
   wire [10:0] 	      pixel_x;
   wire [10:0] 	      pixel_y;
	
	wire RED_ON, BLUE_ON, GREEN_ON;
	
	localparam ONETHIRD = 341;
	localparam TWOTHIRD = 682;
	
   localparam ONEEIGHTH = 128;
	
   clockgen myclockgen(in_clock, 
		       rst, 
		       sys_clock, 
		       locked);
  
   vesasync myvesa(sys_clock, 
		   rst, 
		   hsync, 
		   vsync, 
		   csync, 
		   video_on, 
		   pixel_x, 
		   pixel_y);
   
   assign rst         = ~KEY[0];
   assign in_clock    = CLOCK_50;
   assign VGA_HS      = hsync;
   assign VGA_VS      = vsync;
   assign VGA_SYNC_N  = ~csync;
   assign VGA_BLANK_N = video_on;
	
	//Testpattern generation based on gray code.
	/*
	B G R
	0 0 0
	0 0 1
	0 1 1
	0 1 0
	1 1 0
	1 1 1
	1 0 1
	1 0 0
	*/

   
	assign RED_ON = (((pixel_x > ONEEIGHTH) && (pixel_x < 3*ONEEIGHTH)) || ((pixel_x > 5*ONEEIGHTH) && (pixel_x < 7*ONEEIGHTH)));
	assign BLUE_ON = ((pixel_x > 2*ONEEIGHTH) && (pixel_x < 6*ONEEIGHTH));
	assign GREEN_ON = ((pixel_x > 4*ONEEIGHTH) && (pixel_x < 8*ONEEIGHTH));
	
	assign VGA_R       = RED_ON ? 8'hff : 8'h0;	
	
	assign VGA_B       = BLUE_ON ? 8'hff : 8'h0;

   assign VGA_G       = GREEN_ON ? 8'hff : 8'h0;
   assign VGA_CLK     = sys_clock;
   
endmodule