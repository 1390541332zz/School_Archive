/*---------------------------------------------------------------------------*
 * Module: Gameboy DMG Controller Interface                                  *
 * Purpose: Connects the PS2 in from the DE1-SOC to the Gameboy DMG          *
 *     Controller input.                                                     *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

import gb_intf::cntrlr_data;

module controller(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    st_data.source     cmd,
    st_data.sink       data,
    output cntrlr_data cntrlr
);

typedef enum bit [7:0] {
    KBD_RESET     = 8'hFF,
    KBD_ENABLE    = 8'hF4,
    KBD_DISABLE   = 8'hF5,
    SET_SCAN_CODE = 8'hF0,
    SCAN_MODE_PS2 = 8'h02,
    NO_CMD        = 8'h00
} ps2_kb_cmd;

typedef enum bit [7:0] {
    W_KEY         = 8'h1D,
    A_KEY         = 8'h1C,
    S_KEY         = 8'h1B,
    D_KEY         = 8'h23,
    TILDE_KEY     = 8'h0E,
    TAB_KEY       = 8'h0D,
    ESCAPE_KEY    = 8'h76,
    SPACEBAR      = 8'h29,
    KEY_RELEASED  = 8'hF0,
    ACK           = 8'hFA,
    POWER_ON_PASS = 8'hAA 
} ps2_kb_response;

typedef enum {
    RESET,
    ENABLE,
    SET_SCAN_MODE,
    SET_SCAN_MODE_2,
    STANDBY
} ps2_kb_init_state;

bit
    key_break, key_break_;
ps2_kb_init_state
    init_s, init_s_;
ps2_kb_cmd
    cmd_;
cntrlr_data
    cntrlr_;

/*---------------------------------------------------------------------------*/
/*                                Assertions                                 */
/*---------------------------------------------------------------------------*/

assert property (cmd.clk   == data.clk);
assert property (cmd.reset == data.reset);

assert property (
    ($size( cmd.data) == 8)
 && ($size(data.data) == 8)
);

/*---------------------------------------------------------------------------*/
/*                               Computation                                 */
/*---------------------------------------------------------------------------*/

// Reset and Initialisation Command Control
always_comb case (init_s)
RESET: begin
   cmd_    = KBD_RESET;
   init_s_ = ENABLE;
end
ENABLE: begin
   cmd_    = KBD_ENABLE;
   init_s_ = SET_SCAN_MODE;
end
SET_SCAN_MODE: begin
   cmd_    = SET_SCAN_CODE;
   init_s_ = SET_SCAN_MODE_2;
end
SET_SCAN_MODE_2: begin
   cmd_    = SCAN_MODE_PS2;
   init_s_ = STANDBY;
end
STANDBY: begin
   cmd_    = NO_CMD;
   init_s_ = STANDBY;
end
endcase

// Data Input Control
always_comb begin
    cntrlr_    = cntrlr;
    key_break_ = 1'b0;
    if (data.valid && key_break) case (ps2_kb_response'(data.data))
        W_KEY        : cntrlr_.up     = 1'b1; 
        A_KEY        : cntrlr_.left   = 1'b1; 
        S_KEY        : cntrlr_.down   = 1'b1; 
        D_KEY        : cntrlr_.right  = 1'b1; 
        TILDE_KEY    : cntrlr_.select = 1'b1; 
        TAB_KEY      : cntrlr_.start  = 1'b1; 
        ESCAPE_KEY   : cntrlr_.A      = 1'b1; 
        SPACEBAR     : cntrlr_.B      = 1'b1; 
        default: begin end
    endcase else if (data.valid) case (ps2_kb_response'(data.data))
        W_KEY        : cntrlr_.up     = 1'b0; 
        A_KEY        : cntrlr_.left   = 1'b0; 
        S_KEY        : cntrlr_.down   = 1'b0; 
        D_KEY        : cntrlr_.right  = 1'b0; 
        TILDE_KEY    : cntrlr_.select = 1'b0; 
        TAB_KEY      : cntrlr_.start  = 1'b0; 
        ESCAPE_KEY   : cntrlr_.A      = 1'b0; 
        SPACEBAR     : cntrlr_.B      = 1'b0; 
        KEY_RELEASED : key_break_     = 1'b1;
        default: begin end
    endcase
end

always_ff @(posedge data.clk) if (data.reset) begin
    key_break  <= 1'b0;
    cntrlr     <=  'b1;
    init_s     <= RESET;
    data.ready <= 1'b0;
    cmd.valid  <= 1'b0;
    cmd.data   <= KBD_RESET;
end else begin
    key_break  <= key_break_; 
    cntrlr     <= cntrlr_;
    init_s     <= init_s_;
    data.ready <= 1'b1;
    cmd.valid  <= (init_s != STANDBY);
    cmd.data   <= cmd_;
end

endmodule : controller
