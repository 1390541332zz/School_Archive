`include "bitxmit.h"

module i2cwrite #(
    parameter ADDR_SZ = 7;
    parameter WORD_SZ = 8;
    parameter DATA_SZ = 4;
    parameter CMD_SZ = 3;
) (
    input reset, init, clk,
    input [ADDR_SZ - 1 : 0] addr,
    input [WORD_SZ - 1 : 0] data,
    input [clog2(DATA_SZ) : 0] ptr_begin,
    input [clog2(DATA_SZ) : 0] ptr_end,
    output reg [clog2(DATA_SZ) : 0] ptr_cur,
    output reg [CMD_SZ - 1 : 0] command,
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

reg [3:0] state;
wire addr_init;
wire data_init;

//---------------------------------------------------------------------------//

assign addr_init = (state == ADDR_BEG);
assign data_init = (state == DATA_BEG);

par_to_seq #(
    .PAR_SZ(7),
    .WORD_SZ(CMD_SZ),
    .BIT0(CMDBIT0),
    .BIT1(CMDBIT1)
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
    .BIT0(CMDBIT0),
    .BIT1(CMDBIT1)
) data_pts (
    .clk(clk),
    .reset(reset),
    .init(data_init),
    .par(addr),
    .seq(command),
    .ready(data_ready)
);

//---------------------------------------------------------------------------//

always @(negedge reset, posedge clk) begin
    if (reset == 1'b0) begin
        ready   <= 1'b1;
        state   <= WAIT;
        command <= CMDIDLE;
        ptr_cur <= { clog2(addr_sz) { 1'bz }};
    end else case (state)
    WAIT: begin 
        if (init == 1'b1) begin    
            ready   <= 1'b0;
            state   <= START;
        end else begin
            ready   <= 1'b1;
            state   <= WAIT;
        end
        command <= CMDIDLE;
        ptr_cur <= { clog2(ADDR_SZ) { 1'bZ }};
    end
    START: begin 
        ready   <= 1'b0;
        state   <= ADDR_BEG;
        command <= CMDSTART;
        ptr_cur <= { clog2(ADDR_SZ) { 1'bZ }};
    end
    ADDR_BEG: begin 
        ready   <= 1'b0;
        state   <= ADDR;
        command <= { CMD_SZ { 1'bZ }};
        ptr_cur <= { clog2(ADDR_SZ) { 1'bZ }};
    end
    ADDR: begin
        ready   <= 1'b0;
        state   <= (addr_ready == 1'b1) ? RW : ADDR;
        command <= { CMD_SZ { 1'bZ }};
        ptr_cur <= { clog2(ADDR_SZ) { 1'bZ }};
    end
    RW: begin
        ready   <= 1'b0;
        state   <= ACK;
        command <= CMDRBIT;
        ptr_cur <= ptr_begin;
    end
    ACK: begin
        ready   <= 1'b0;
        state   <= (ptr_cur >= ptr_end) ? STOP : DATA_BEG;
        command <= CMDIDLE;
        ptr_cur <= ptr_cur;
    end
    DATA_BEG: begin 
        ready   <= 1'b0;
        state   <= DATA;
        command <= { CMD_SZ { 1'bZ }};
        ptr_cur <= ptr_cur;
    end
    DATA: begin 
        ready   <= 1'b0;
        command <= { CMD_SZ { 1'bZ }};
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
        state   <= WAIT;
        command <= CMDSTOP;
        ptr_cur <= { clog2(ADDR_SZ) { 1'bZ }};
    end
    endcase
end
endmodule
