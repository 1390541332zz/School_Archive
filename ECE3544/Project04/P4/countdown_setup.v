//////////////////////////////////////////////////////////////////
// Filename: countdown_setup.v
// Author:   Jacob Abel
// Date:     28 November 2018
// Revision: 1

module countdown_setup(
	input  CLK_50,
    input  cycle, reset,
	output reg hr, min
);

//===============//
// State Machine //
//===============//
reg [1:0] s;
parameter [1:0] DEFAULT_CDS = 2'h0, HOUR_CDS = 2'h1, MIN_CDS = 2'h2;

always @(posedge CLK_50) begin
    if (reset)
        s <= DEFAULT_CDS;
    else if (cycle)
        case (s)
        DEFAULT_CDS: s <= HOUR_CDS;
        HOUR_CDS:    s <= MIN_CDS;
        MIN_CDS:     s <= HOUR_CDS;
        endcase
    else
        s <= s;
end

always @(s) begin
    case (s) 
    DEFAULT_CDS: {hr, min} = 2'b00;
    HOUR_CDS:    {hr, min} = 2'b10;
    MIN_CDS:     {hr, min} = 2'b01;
    endcase
end

endmodule
