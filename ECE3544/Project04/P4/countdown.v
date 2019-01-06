//////////////////////////////////////////////////////////////////
// Filename: countdown.v
// Author:   Jacob Abel
// Date:     28 November 2018
// Revision: 1

module countdown(
	input  CLK_50, CLK_1HZ,
	input  reset, adjust, toggle, mode, active,
    output hr, min, sec, alarm,
    output [3:0] H1,
	output reg [3:0] H0_o, M1_o, M0_o, S1_o, S0_o
);
reg [2:0] s;
reg [3:0] H0, M1, M0, S1, S0;
reg [3:0] H0_a, M1_a, M0_a, S1_a, S0_a;
wire soft_reset, hard_reset, cycle, clear;

assign H1 = 4'hA;
assign sec = 1'b0;
assign hard_reset = reset;
assign soft_reset = ((s == RUN_CD) && adjust);
assign cycle = ((s == SETUP_CD) && mode);
assign alarm = ({H0_o, M1_o, M0_o, S1_o, S0_o} == 20'h0);
assign clear = (active && (adjust || toggle || mode));

countdown_setup CDS(CLK_50, cycle, (soft_reset || hard_reset), hr, min);

//===============//
// State Machine //
//===============//
parameter [2:0] DEFAULT_CD = 3'h0, SETUP_CD = 3'h1, START_CD = 3'h2,
                   WAIT_CD = 3'h3,   RUN_CD = 3'h4, ALARM_CD = 3'h5;
    
always @(posedge CLK_50 or posedge hard_reset) begin
    if (hard_reset)
        s <= DEFAULT_CD;
    else if (soft_reset)
        s <= SETUP_CD;
    else
        case (s)
        DEFAULT_CD: s <= SETUP_CD;
          SETUP_CD: s <= (adjust) ? START_CD : SETUP_CD;
          START_CD: s <= WAIT_CD;
           WAIT_CD: s <= (toggle) ?   RUN_CD :  WAIT_CD;
            RUN_CD: s <= (toggle) ?  WAIT_CD :
                         (alarm)  ? ALARM_CD :   RUN_CD;
          ALARM_CD: s <= (clear)  ? START_CD : ALARM_CD;
        endcase
end

always @(posedge CLK_50) begin
    case (s)
    SETUP_CD: 
        {H0_o, M1_o, M0_o, S1_o, S0_o} <= {H0, M1, M0, S1, S0};
    START_CD: 
        {H0_o, M1_o, M0_o, S1_o, S0_o} <= {H0, M1, M0, S1, S0};
    default:
        {H0_o, M1_o, M0_o, S1_o, S0_o} <= {H0_a, M1_a, M0_a, S1_a, S0_a};
    endcase
end

//============//
// Alarm Edit //
//============//
always @(posedge CLK_50) begin
    if (s == DEFAULT_CD)
        {H0, M1, M0, S1, S0} <= 20'h0;
    else if ((s == SETUP_CD) && toggle) begin
        if (min) begin
            if  (M0 > 4'h9) {M1, M0} = {M1 + 4'h1, 4'h0};
            if  (M1 > 4'h5)  M1 = 4'h0;
        end
        else if (hr) 
            if (H0 > 4'h9) H0 = 4'h0;
            else           H0 = H0 + 4'h1;
    end
    else
        {H0, M1, M0, S1, S0} = {H0, M1, M0, S1, S0};
end

//=======//
// ALARM //
//=======//
always @(posedge CLK_1HZ) if (s == RUN_CD) begin
    if  (S0_a > 4'h9) {S1_a, S0_a} = {S1_a - 4'h1, 4'h9};
    if  (S1_a > 4'h5) {M0_a, S1_a} = {M0_a - 4'h1, 4'h5};
    if  (M0_a > 4'h9) {M1_a, M0_a} = {M1_a - 4'h1, 4'h9};
    if  (M1_a > 4'h5) {H0_a, M1_a} = {H0_a - 4'h1, 4'h5};
    if  (H0_a > 4'h9)        H0_a  = 4'h0;
    {H0_a, M1_a, M0_a, S1_a, S0_a} = {H0_a, M1_a, M0_a, S1_a, S0_a};
end else
    {H0_a, M1_a, M0_a, S1_a, S0_a} = {H0_a, M1_a, M0_a, S1_a, S0_a};


endmodule
