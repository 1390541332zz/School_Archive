module i2cmasterwrite(
    input  clk,
    input  reset,
    input  init,
    output sck,
    inout  sda
);
localparam ADDR_SZ = 7;
localparam DATA_SZ = 4;
localparam WORD_SZ = 8;
localparam  CMD_SZ = 3;
localparam [1:0]
    INIT  = 'h0, 
    STAGE = 'h1,
    WRITE = 'h2,
    WAIT  = 'h3;

reg write_init;
reg [1:0] state;
reg [DATA_SZ - 1 : 0] index;

wire 
    bit_ready, 
    write_ready, 
    write_init,
    bit_clk,
    command;
wire [ADDR_SZ - 1 : 0] addr;
wire [WORD_SZ - 1 : 0] data;
wire [DATA_SZ - 1 : 0]
    ptr_begin,
    ptr_end,
    ptr_cur;

//---------------------------------------------------------------------------//

assign bit_clk   = clk & bit_ready;

// Signal Level Interface
bitxmit bit(
    .clk(clk),
    .reset(reset),
    .command(command),
    .ready(bit_ready),
    .sck(sck),
    .sda(sda)
);

// Protocol Level Interface
i2cwrite #(
    .ADDR_SZ(ADDR_SZ),
    .DATA_SZ(DATA_SZ),
    .WORD_SZ(WORD_SZ),
    .CMD_SZ(3)
) writer (
    .reset(reset), 
    .init(write_init),
    .clk(bit_clk), 
    .addr(addr),
    .data(data),
    .ptr_begin(ptr_begin),
    .ptr_end(ptr_end),
    .ptr_cur(ptr_cur),
    .command(command),
    .ready(write_ready)
);

// Command Storage
cmdrom cmdrom (
    .addr(index),
    .data({ addr, ptr_begin, ptr_end })
);

// Data Storage
datarom datarom (
    .addr(ptr_cur),
    .data(data)
);

//---------------------------------------------------------------------------//

always @(negedge reset, posedge clk) begin
    if (reset == 1'b0) begin
        state      <= WAIT;
        index      <= { DATA_SZ { 1'bZ }};
        write_init <= 1'b0;
    end else case (state)
    INIT: begin
        state      <= STAGE;
        index      <= { DATA_SZ { 1'bZ }};
        write_init <= 1'b0;
    end
    STAGE: if (index >= MAX_INDEX) begin
        state      <= WAIT;
        index      <= index;
        write_init <= 1'b0;
    end else begin
        state      <= WRITE;
        index      <= index;
        write_init <= 1'b1;
    end
    WRITE: if (write_ready) begin
        state      <= STAGE;
        index      <= index + 1;
        write_init <= 1'b0;
    end else begin
        state      <= WRITE;
        index      <= index;
        write_init <= 1'b0;
    end
    WAIT: begin
        state      <= WAIT;
        index      <= { DATA_SZ { 1'bZ }};
        write_init <= 1'b0;
    end
    endcase
end
endmodule
