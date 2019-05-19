`include "bit_stream.h"

module i2c_gen (
    input        clk,
    input        reset,

    input [6:0]  address,
    input [15:0] data,
    input        load,
    output       ready,

    output [2:0] command,
    input        bitready
);

localparam 
    IDLE   = 0,
    START  = 1, 
    ADR    = 2,
    READ1  = 3,
    MSB    = 4,
    READ2  = 5,
    LSB    = 6,
    READ3  = 7,
    STOP   = 8;

reg [3:0] 
    state, 
    statenext;
reg [7:0] 
    worddata, 
    worddatanext,
    shift,
    shiftnext;

reg [2:0] 
    rcommand;

assign ready   = (state == IDLE);
assign command = rcommand;

always @(posedge clk)
begin
    if (reset) begin
        state    <= IDLE;
        worddata <= 8'b0;
        shift    <= 8'b0;
    end
    else begin
        state    <= statenext;
        worddata <= worddatanext;
        shift    <= shiftnext;
    end
end

always @(*)
begin
    rcommand     = `CMDWAIT;
    statenext    = state;
    worddatanext = worddata;
    shiftnext    = shift;

    case (state)

        IDLE : begin
            rcommand     = `CMDIDLE;
            if (load == 1) 
            begin
                statenext  = START;
            end
        end

        START : begin
            rcommand = `CMDSTART;
            if (bitready) begin
                statenext    = ADR; 
                rcommand     = `CMDWAIT;
                shiftnext    = 8'b1;
                worddatanext =  {address, 1'b0};
            end
        end

        ADR : begin
            if (shift == 8'b0) begin
                rcommand  = `CMDWAIT;
                statenext = READ1;
            end else begin
                rcommand = worddata[7] ? `CMDBIT1 : `CMDBIT0;
                if (bitready) begin
                    rcommand      = `CMDWAIT;
                    worddatanext  = worddata << 1;
                    shiftnext     = shift    << 1;
                end
            end
        end

        READ1 : begin
            rcommand = `CMDRBIT;
            if (bitready) begin
                statenext     = MSB; 
                rcommand      = `CMDWAIT;
                shiftnext     = 8'b1;
                worddatanext  = data[15:8];
            end
        end

        MSB : begin
            if (shift == 8'b0) begin
                rcommand = `CMDWAIT;
                statenext = READ2;
            end else begin
                rcommand = worddata[7] ? `CMDBIT1 : `CMDBIT0;
                if (bitready) begin
                    rcommand      = `CMDWAIT;
                    worddatanext  = worddata << 1;
                    shiftnext     = shift    << 1;
                end
            end
        end

        READ2 : begin
            rcommand = `CMDRBIT;
            if (bitready) begin
                statenext    = LSB; 
                rcommand     = `CMDWAIT;
                shiftnext    = 8'b1;
                worddatanext =  data[7:0];
            end
        end

        LSB : begin
            if (shift == 8'b0) begin
                rcommand = `CMDWAIT;
                statenext = READ3;
            end else begin
                rcommand = worddata[7] ? `CMDBIT1 : `CMDBIT0;
                if (bitready) begin
                    rcommand     = `CMDWAIT;
                    worddatanext = worddata << 1;
                    shiftnext    = shift    << 1;
                end
            end
        end

        READ3 : begin
            rcommand = `CMDRBIT;
            if (bitready) begin
                statenext    = STOP; 
                rcommand     = `CMDWAIT;
            end
        end

        STOP: begin
            rcommand = `CMDSTOP;
            if (bitready) begin
                statenext    = IDLE; 
                rcommand     = `CMDWAIT;
            end
        end

        default:
            statenext = IDLE;
    endcase
end

endmodule
