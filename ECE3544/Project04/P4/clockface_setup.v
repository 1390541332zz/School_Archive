//////////////////////////////////////////////////////////////////
// Filename: clockface_setup.v
// Author:   Jacob Abel
// Date:     28 November 2018
// Revision: 1

module clockface_setup(
	input  CLK_50,
    input  cycle, reset,
	output reg hr, min, sec
);

reg [1:0] s;
parameter [1:0] DEFAULT_CFS = 2'h0, SEC_CFS = 2'h1, MIN_CFS = 2'h2, HOUR_CFS = 2'h3;

always @(posedge CLK_50) begin
    if (reset)
        s <= DEFAULT_CFS;
    else if (s == DEFAULT_CFS)
        s <= SEC_CFS;
    else if (cycle)
        case (s)
        SEC_CFS:  s <= MIN_CFS;
        MIN_CFS:  s <= HOUR_CFS;
        HOUR_CFS: s <= SEC_CFS;
        endcase
    else
        s <= s;
end

always @(s) begin
    case (s) 
    DEFAULT_CFS: {hr, min, sec} = 3'b000;
    SEC_CFS:     {hr, min, sec} = 3'b001;
    MIN_CFS:     {hr, min, sec} = 3'b010;
    HOUR_CFS:    {hr, min, sec} = 3'b100;
    endcase
end

endmodule
