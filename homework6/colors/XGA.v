module XGA(
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
	
	//Map one switch to each color. 8 combinations of SW -> 8 colors.
	assign VGA_B       = SW[0] ? 8'hff : 8'h0;
   assign VGA_R       = SW[1] ? 8'hff : 8'h0;  
   assign VGA_G       = SW[2] ? 8'hff : 8'h0;
   assign VGA_CLK     = sys_clock;
   
endmodule