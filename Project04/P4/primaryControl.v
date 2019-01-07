//////////////////////////////////////////////////////////////////
// Filename: primaryControl.v
// Author:   Jacob Abel
// Date:     28 November 2018
// Revision: 1

module primaryControl(
	input  CLK_50, CLK_1HZ,
	input  reset, adjust, toggle, mode,
    output [5:0] HEX_en, HEX_flash,
	output reg [3:0] H1, H0, M1, M0, S1, S0
);
    reg [1:0] s;
    reg hr, min, sec;
    wire alarm, no_ten, active;
    wire hr_cf, min_cf, sec_cf, hr_cd, min_cd, sec_cd; 
    wire [3:0] H1_cf, H0_cf, M1_cf, M0_cf, S1_cf, S0_cf;
    wire [3:0] H1_cd, H0_cd, M1_cd, M0_cd, S1_cd, S0_cd;

    assign active = (s == COUNTDOWN);
    assign HEX_flash = {(hr && ~no_ten), hr, {2{min}}, {2{sec}}};
    assign HEX_en = {
        ~(no_ten || (s == INIT)), 
        ~(s == INIT),
        4'b1
    };
    countdown CD(
        CLK_50, CLK_1HZ,
        reset, adjust, toggle, mode, active,
        hr_cd, min_cd, sec_cd, alarm,
        H1_cd, H0_cd, M1_cd, M0_cd, S1_cd, S0_cd
    );
    clockface CF(
        CLK_50, CLK_1HZ, 
        reset, adjust, toggle, mode,
        hr_cf, min_cf, sec_cf, no_ten,
        H1_cf, H0_cf, M1_cf, M0_cf, S1_cf, S0_cf
    );
//===============//
// State Machine //
//===============//
parameter [1:0] INIT = 2'h0, CLOCKFACE = 2'h1, COUNTDOWN = 2'h2;
    
always @(posedge CLK_50) begin
    if (reset)
        s <= INIT;
    else 
        case (s)
        INIT:      s <= CLOCKFACE; 
        CLOCKFACE: s <= (toggle ||  alarm) ? COUNTDOWN : CLOCKFACE;
        COUNTDOWN: s <= (toggle && ~alarm) ? CLOCKFACE : COUNTDOWN; 
        endcase
end

always @(posedge CLK_50) begin
    case (s)
    INIT:      
        {H1, H0, M1, M0, S1, S0, hr, min, sec} = {
            4'hx, 4'hx, 4'h9, 4'h6, 4'h5, 4'h4, 3'b0
         };
    CLOCKFACE: 
        {H1, H0, M1, M0, S1, S0, hr, min, sec} = {
            H1_cf, H0_cf, M1_cf, M0_cf, S1_cf, S0_cf, 
            hr_cf, min_cf, sec_cf
        }; 
    COUNTDOWN: 
        {H1, H0, M1, M0, S1, S0, hr, min, sec} = {
            H1_cd, H0_cd, M1_cd, M0_cd, S1_cd, S0_cd, 
            hr_cd, min_cd, sec_cd
        }; 
    endcase
end

endmodule
