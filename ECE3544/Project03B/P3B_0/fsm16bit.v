////////////////////////////////////////////////////////////////////////////////
// Filename:    fsm16bit.v
// Author:      Jacob Abel
// Date:        09 November 2018
// Version:     2
// Description: A 16-bit synchronous FSM implementing the required FSM 
//              for Project 3.
 
// Requires separate keypress state machine by T. Martin
module fsm16bit(clock, reset, enable, check, mode, direction, value, outputValue);
    input         clock, reset, enable, check, mode, direction;
    input [3:0]   value;
    output [15:0] outputValue;
    
    reg [15:0] fsm_state;
    initial fsm_state = 16'h0000;
// STATE MACHINE
// This always block represents sequential logic, so it uses non-blocking assignments.
// It is sensitized to the clock input and the clear input.
// You should picture this always block as a 16-bit register with an active-low asynchronous clear.
    always @(posedge clock or negedge reset) begin
        if (reset == 1'b0)
            fsm_state <= 16'b0;
        else 
            casez ({reset, enable, check, mode, direction})
                5'b10??? : fsm_state <= fsm_state;
                5'b110?? : fsm_state <= 16'h6453;
                5'b11100 : begin
                    fsm_state = fsm_state - value;
                end
                5'b11101 : begin
                    fsm_state = fsm_state + value;
                end
                5'b11110 : begin
                    fsm_state = {fsm_state[0], 15'b0 } | ((fsm_state >> 1) & 16'h7FFF);
                end
                5'b11111 : begin
                    fsm_state = {15'b0, fsm_state[15]} | ((fsm_state << 1) & 16'hFFFE);
                end
            endcase
    end 

// OUTPUT MACHINE
// Since the output is always the same as the FSM state, assign the present state to the output.

// The output machine is combinational logic. A continuous assignment represents combinational logic.
// In a more complex FSM, the output machine would consist of an always block.
// Since the always block for the output machine represents combinational logic, it would use blocking assignments.

// You should not need to modify this continuous assignment. 
// Changing the state machine will change the output machine directly.
    
    assign outputValue = fsm_state; 

endmodule
