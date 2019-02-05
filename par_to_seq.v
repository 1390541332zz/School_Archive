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
reg [$clog2(PAR_SZ) : 0] cnt;

//---------------------------------------------------------------------------//

always @(posedge reset, posedge clk) begin
    if ((reset == 1'b1) || (cnt == PAR_SZ)) begin
        state <= WAIT;
        ready <= 1'b1; 
        cnt   <= 1'b0; 
        seq   <= { WORD_SZ { 1'bZ }};
    end else case (state)
    ACTIVE: begin
        state <= ACTIVE;
        ready <= 1'b0; 
        cnt   <= cnt + 1'b1; 
        seq   <= (par[cnt] == 1'b1) ? BIT1 : BIT0;
    end
    WAIT: if (init == 1'b1) begin
        state <= ACTIVE;
        ready <= 1'b0; 
        cnt   <= 1'b0; 
        seq   <= { WORD_SZ { 1'bZ }};
    end else begin
        state <= WAIT;
        ready <= 1'b1; 
        cnt   <= 1'b0; 
        seq   <= { WORD_SZ { 1'bZ }};
    end
    endcase
end
endmodule
