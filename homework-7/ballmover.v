module ballmover
  #(parameter RADIUS = 32,
	      SCREENX = 1024,
	      SCREENY = 768)
    (input  wire clk,
     input  wire rst,
     input  wire move,
     output wire [10:0] centerx,
     output wire [10:0] centery);
   
   reg [10:0] 		bx_reg, by_reg;
   wire [10:0] 		bx_next, by_next;
   
   reg 			bx_dir_reg, by_dir_reg;
   wire 		bx_dir_next, by_dir_next;
   
   wire [10:0] 		bx_to, by_to;
   wire 		bounce_x, bounce_y;
   
   always @(posedge clk or posedge rst)
	if (rst) 
	  begin
	     bx_reg = SCREENX / 2;   // ball starts middle of screen
	     by_reg = SCREENY / 2;
	     bx_dir_reg = 1'b0;      // ball moves diagonally up
	     by_dir_reg = 1'b0;	     
	  end
	else
	  begin
	     bx_reg = bx_next;
	     by_reg = by_next;
	     bx_dir_reg = bx_dir_next;
	     by_dir_reg = by_dir_next;
	  end

   // bounce X left at RADIUS
   // bounce X right at SCREENX - RADIUS - 1
   // bounce Y top at RADIUS
   // bounce Y bottom at SCREENY - RADIUS - 1
   
   assign bx_to       = (bx_dir_reg) ? bx_reg + 1'b1 : bx_reg - 1'b1;
   assign by_to       = (by_dir_reg) ? by_reg + 1'b1 : by_reg - 1'b1;
   
   assign bounce_x    = (bx_to <= RADIUS) || (bx_to >= (SCREENX - RADIUS));
   assign bounce_y    = (by_to <= RADIUS) || (by_to >= (SCREENY - RADIUS));

   assign bx_dir_next = (move & bounce_x) ? ~bx_dir_reg : bx_dir_reg;
   assign by_dir_next = (move & bounce_y) ? ~by_dir_reg : by_dir_reg;
   
   assign bx_next     = (move) ? bx_to : bx_reg;
   assign by_next     = (move) ? by_to : by_reg;

   assign centerx     = bx_reg;
   assign centery     = by_reg;

endmodule
