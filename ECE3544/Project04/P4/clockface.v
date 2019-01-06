//////////////////////////////////////////////////////////////////
// Filename: clockface.v
// Author:   Jacob Abel
// Date:     28 November 2018
// Revision: 1

module clockface(
	input  CLK_50, CLK_1HZ,
	input  reset, adjust, toggle, mode,
    output hr, min, sec, no_ten,
	output reg [3:0] H1, H0, M1, M0, S1, S0
);
reg [1:0] s;
wire cycle, cfs_reset;

assign no_ten = (H1 == 4'b0);
assign cycle = ((s == SETUP_CF) && mode);
assign cfs_reset = ((s == RUN_CF) || reset);

clockface_setup CFS(CLK_50, cycle, cfs_reset, hr, min, sec);

//===============//
// State Machine //
//===============//
parameter [1:0] DEFAULT_CF = 2'h0, RUN_CF = 2'h1, SETUP_CF = 2'h2;

always @(posedge CLK_50) begin
    if (reset)
        s <= DEFAULT_CF;
    else 
        case (s)
        DEFAULT_CF: s <= RUN_CF;
        RUN_CF:   s <= (adjust) ? SETUP_CF : RUN_CF;
        SETUP_CF: s <= (adjust) ? RUN_CF   : SETUP_CF;
        endcase
end

//=======//
// Clock //
//=======//
reg [1:0] det_clk_1hz;
wire sig;
assign sig = (det_clk_1hz == 2'b01);
always @(posedge CLK_50) begin
    det_clk_1hz <= {det_clk_1hz[0], CLK_1HZ};
end

always @(posedge CLK_50) begin
    if (s == DEFAULT_CF)
        {H1, H0, M1, M0, S1, S0} = 18'b0;
    else if ((s == SETUP_CF) && toggle) begin
        if (sec)
            {S1, S0} = {4'h0, 4'h0};
        else if (min) begin
            if  (M0 > 4'h9) {M1, M0} = {M1 + 4'h1, 4'h0};
            if  (M1 > 4'h5)  M1 = 4'h0;
        end
        else if (hr) begin
            if ((H0 > 4'h9) && (H1 == 4'h0)) {H1, H0} = {H1 + 4'h1, 4'h0};
            if ((H0 > 4'h2) && (H1 == 4'h1)) {H1, H0} = {4'h0,      4'h0};
        end
    end
    if ((s != DEFAULT_CF) && sig) begin
        if  (S0 > 4'h9)                  {S1, S0} = {S1 + 4'h1, 4'h0};
        if  (S1 > 4'h5)                  {M0, S1} = {M0 + 4'h1, 4'h0};
        if  (M0 > 4'h9)                  {M1, M0} = {M1 + 4'h1, 4'h0};
        if  (M1 > 4'h5)                  {H0, M1} = {H0 + 4'h1, 4'h0};
        if ((H0 > 4'h9) && (H1 == 4'h0)) {H1, H0} = {H1 + 4'h1, 4'h0};
        if ((H0 > 4'h2) && (H1 == 4'h1)) {H1, H0} = {4'h0,      4'h0};
    end
    {H1, H0, M1, M0, S1, S0} = {H1, H0, M1, M0, S1, S0};
end

endmodule
