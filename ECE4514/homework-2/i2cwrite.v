`include "bitxmit.h"

module i2cwrite #(
    parameter ADDR_SZ = 7,
    parameter WORD_SZ = 8,
    parameter DATA_SZ = 4,
    parameter CMD_SZ = 3
) (
    input reset, init, clk, bit_clk,
    input [ADDR_SZ - 1 : 0] addr,
    input [WORD_SZ - 1 : 0] data,
    input [DATA_SZ - 1: 0] ptr_begin,
    input [DATA_SZ - 1: 0] ptr_end,
    output reg [DATA_SZ - 1 : 0] ptr_cur,
    output [CMD_SZ - 1 : 0] command,
    output reg ready
); 
localparam [3:0] 
    WAIT     = 4'h0, 
    START    = 4'h1, 
    ADDR_BEG = 4'h2, 
    ADDR     = 4'h3, 
    RW       = 4'h4, 
    ACK      = 4'h5, 
    DATA_BEG = 4'h6, 
    DATA     = 4'h7, 
    STOP     = 4'h8;
    STOP2    = 4'h9;

reg [3:0] state;
reg [CMD_SZ - 1 : 0] cmd;
wire
    addr_init, 
    data_init,
    addr_ready,
    data_ready;

//---------------------------------------------------------------------------//

assign addr_init = (state == ADDR_BEG);
assign data_init = (state == DATA_BEG);
assign command = cmd;

par_to_seq #(
    .PAR_SZ(ADDR_SZ),
    .WORD_SZ(CMD_SZ),
    .BIT0(`CMDBIT0),
    .BIT1(`CMDBIT1)
) addr_pts (
    .clk(clk),
    .reset(reset),
    .init(addr_init),
    .par(addr),
    .seq(command),
    .ready(addr_ready)
);

par_to_seq #(
    .PAR_SZ(WORD_SZ),
    .WORD_SZ(CMD_SZ),
    .BIT0(`CMDBIT0),
    .BIT1(`CMDBIT1)
) data_pts (
    .clk(clk),
    .reset(reset),
    .init(data_init),
    .par(data),
    .seq(command),
    .ready(data_ready)
);

//---------------------------------------------------------------------------//

always @(posedge reset, posedge init, posedge clk) begin
    if (reset == 1'b1) begin
        ready   <= 1'b0;
        state   <= WAIT;
        cmd     <= `CMDIDLE;
        ptr_cur <= { DATA_SZ { 1'bz }};
    end else if (init == 1'b1) begin
        ready   <= 1'b0;
        state   <= START;
        cmd     <= `CMDIDLE;
        ptr_cur <= { DATA_SZ { 1'bZ }};
    end else case (state)
    WAIT: begin 
        ready   <= 1'b1;
        state   <= WAIT;
        cmd     <= `CMDIDLE;
        ptr_cur <= { DATA_SZ { 1'bZ }};
    end
    START: begin 
        ready   <= 1'b0;
        state   <= ADDR_BEG;
        cmd     <= `CMDSTART;
        ptr_cur <= { DATA_SZ { 1'bZ }};
    end
    ADDR_BEG: begin 
        ready   <= 1'b0;
        state   <= ADDR;
        cmd     <= { CMD_SZ { 1'bZ }};
        ptr_cur <= { DATA_SZ { 1'bZ }};
    end
    ADDR: begin
        ready   <= 1'b0;
        state   <= (addr_ready == 1'b1) ? RW : ADDR;
        cmd     <= { CMD_SZ { 1'bZ }};
        ptr_cur <= { DATA_SZ { 1'bZ }};
    end
    RW: begin
        ready   <= 1'b0;
        state   <= ACK;
        cmd     <= `CMDRBIT;
        ptr_cur <= ptr_begin;
    end
    ACK: begin
        ready   <= 1'b0;
        state   <= (ptr_cur >= ptr_end) ? STOP : DATA_BEG;
        cmd     <= `CMDIDLE;
        ptr_cur <= ptr_cur;
    end
    DATA_BEG: begin 
        ready   <= 1'b0;
        state   <= DATA;
        cmd     <= { CMD_SZ { 1'bZ }};
        ptr_cur <= ptr_cur;
    end
    DATA: begin 
        ready   <= 1'b0;
        cmd     <= { CMD_SZ { 1'bZ }};
        if (data_ready == 1'b1) begin
            state   <= ACK;
            ptr_cur <= ptr_cur + 1;
        end else begin
            state   <= DATA;
            ptr_cur <= ptr_cur;
        end
    end
    STOP: begin
        ready   <= 1'b0;
        state   <= STOP2;
        cmd     <= `CMDSTOP;
        ptr_cur <= { DATA_SZ { 1'bZ }};
    end
    STOP2: begin
        ready   <= 1'b0;
        state   <= WAIT;
        cmd     <= `CMDWAIT;
        ptr_cur <= { DATA_SZ { 1'bZ }};
    end
    endcase
end
endmodule
