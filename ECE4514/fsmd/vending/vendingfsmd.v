module vendingfsmd(input wire clk,
		   input wire  rst,
		   input wire  c,
		   output wire d);

   parameter COIN = 25,   // coins are quarters
             COST = 125;  // 5 quarters for a soda
   
   wire 			    add, clr, compare;
   wire [7:0] 			    a;
   wire [7:0] 			    s;

   assign a = COIN;
   assign s = COST;

   vendingdp dp(.clk(clk),
		.a(a),
		.s(s),
		.add(add),
		.clr(clr),
		.compare(compare));

   vendingfsm fsm(.rst(rst),
		  .clk(clk),
		  .c(c),
		  .compare(compare),
		  .add(add),
		  .clr(clr),
		  .d(d));
   
endmodule

module vendingdp(input  wire clk,
		 input wire [7:0] a,
		 input wire [7:0] s,
		 input wire 	  add,
		 input wire 	  clr,
                 output wire 	  compare);
   
   reg [7:0] 			  total;
   wire [7:0] 			  total_next;
   
   always @(posedge clk)
     total <= total_next;   
   
   assign total_next = clr ? 8'b0 :
	               add ? total + a :
		       total;
   
   assign compare = (total < s);
   
endmodule	 

module vendingfsm(input  wire  rst,
		  input  wire  clk,
		  input  wire  c,
		  input  wire  compare,
		  output reg   add,
		  output reg   clr,
		  output reg   d);
   
   localparam SInit = 0, Wait = 1, Add = 2, Disp = 3;
   
   reg [1:0] 		      state, next_state;
   
   always @(posedge clk, posedge rst)
     if (rst)
       state <= SInit;
     else
       state <= next_state;
   
   always @(*)
     begin
	add = 1'b0;
	clr = 1'b0;
	d   = 1'b0;
	case (state)
	  
	  SInit:	    
	    begin
	       clr = 1'b1;
               next_state = Wait;
	    end
	  
	  Wait: 
	    begin
	       if (~c & compare)       next_state = Wait;
               else if (~c & ~compare) next_state = Disp;
               else                    next_state = Add;
	    end
	  
	  Add:
	    begin
	       add = 1'b1;
               next_state = Wait;
	    end
	  
	  Disp: 
	    begin
	       d   = 1'b1;
               next_state = SInit;
	    end
	  
	  default:
	  	next_state = SInit;
	  	
	endcase
     end
   
endmodule
