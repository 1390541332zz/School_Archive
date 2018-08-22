// This file was created by 
// Tom Martin 
// 16 October 2012
//  Last modified: RFM, 8/30/2015
//
//  RFM => Implemented Aysnchronous Reset correctly
// 
//  This module implements a counter to generate addresses 
//  for a ROM on every button push (the enable input ). 
 
//  
//  You must not modify any part of this file.
// 
//  It is intended that the top level module uses Pushbutton KEY[0] for the reset (active low) 
//  and that KEY[1] is used for enable, which increments the counter.
// 
	
// This module contains two state machines that are combined to 
// count through addresses.  The counter is incremented once every time
// that enable (KEY[1]) is pushed.

module address_counter(clock, reset, enable, counter_out);
	input clock, reset, enable;
   parameter COUNTER_WIDTH = 4;
	output [(COUNTER_WIDTH-1):0] counter_out;
	
		
	// These parameters are for the state of the KEY[1]
	parameter [1:0] KEY_OPEN = 2'b00, KEY_PUSHED = 2'b01,  KEY_RELEASED = 2'b10;

	// These reg declarations are for the state and output 
	// of the state machine for generating a pulse on key_out for one clock cycle 
	// whenever enable is high.  
	reg [1:0]key_state, next_key_state; 
	reg key_out;
	reg [(COUNTER_WIDTH-1):0] counter;
	reg [1:0] resetD;
	
	assign counter_out = counter;
	
	// Synchronize Reset Signal to Clock
		always @(posedge clock, negedge reset)
		if (~reset) begin
			resetD[0] <= 1'b0;
			resetD[1] <= 1'b0;
		end
		else begin
			resetD[0] <= 1'b1;
			resetD[1] <= resetD[0];
		end
	
	// The counter state machine for supplying addresses to the memory
	always @(posedge clock, negedge resetD[1])
	begin
		if (~resetD[1])
			counter <= {COUNTER_WIDTH{1'b0}};
		else
			if (key_out)
				counter <= counter +  1'b1;
	end

	
// State machine for checking for a key press and release
// Output is high for only one clock cycle after the key is released
// This always block describes the state elements.
	always @(posedge clock, negedge resetD[1])
	begin
		if (~resetD[1])
			key_state <= KEY_OPEN;
		else
			 key_state <= next_key_state;	
	end

	
	// This always block describes the next state and 
	// output logic for the key press state machine
	always @(key_state, enable)
	begin
	   // default assignments that will be overridden
		// as needed in the case statement
		next_key_state = key_state;
		key_out = 1'b0;
		case (key_state)
			KEY_OPEN: begin
				if (enable == 1'b1) 
					next_key_state = KEY_PUSHED;
			end
			KEY_PUSHED: begin
				if (enable == 1'b0) 
					next_key_state = KEY_RELEASED;
			end
			KEY_RELEASED: begin
					key_out = 1'b1;
					next_key_state = KEY_OPEN;
			end
			default: begin   // This should never happen
			                 // so let the tools treat it as don't cares.
			      next_key_state = 2'bxx;
					key_out = 1'bx;
			end
		endcase
	end
	
endmodule	
	
