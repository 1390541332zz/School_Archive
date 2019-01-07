////////////////////////////////////////////////////////////////////////////////
// Filename:    cntr4ud.v
// Author:      Jacob Abel
// Date:        12 November 2018
// Version:     1
// Description: Counter Module for problem 1.
 
module fsm16bit(
    input clk, clr, updn, ld, enp, ent, 
    input [3:0] abcd,
    output [3:0] qabcd, 
    output rco
);
    reg [3:0] rabcd;
    always @(posedge clock) begin
        if (clr == 1'b0)
            rabcd <= 4'b0;
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

    
    assign outputValue = fsm_state; 

endmodule

