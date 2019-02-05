module par_to_seq #(
    parameter PAR_SZ  = 8,
    parameter WORD_SZ = 1,
    parameter BIT0 = 0,
    parameter BIT1 = 1

) (
    input clk, reset, init,
    input [PAR_SZ - 1 : 0] par,
    output reg [WORD_SZ - 1 : 0] seq,
    output reg ready
);
localparam ACTIVE = 1'b1, WAIT = 1'b0;

reg state;
reg [clog2(PAR_SZ) : 0] cnt;

//---------------------------------------------------------------------------//

initial state = WAIT;

always @(negedge reset, posedge clk) begin
    if ((reset == 1'b0) || (cnt == PAR_SZ))
        { state, ready, cnt } <= { WAIT, 1'b1, (PAR_SZ)'b0 };
        seq <= { WORD_SZ { 1'bZ }};
    else case (state)
    ACTIVE:
        { state, ready, cnt } <= { ACTIVE, 1'b0, cnt + (PAR_SZ)'b1 };
        seq <= (par[cnt] == 1'b1) ? BIT1 : BIT0;
    WAIT:
        if (init == 1'b1)
            { state, ready, cnt, seq } <= {   WAIT, 1'b1, (PAR_SZ)'b0, { WORD_SZ {1'bZ }} };
        else
            { state, ready, cnt, seq } <= { ACTIVE, 1'b0, (PAR_SZ)'b0, { WORD_SZ {1'bZ }} };
    endcase
end
endmodule
