module audio_gen(
    input             reset,
    input             enable,
    input             bclk,
    inout             dac_lr_clk,
    input       [2:0] freq,
    input       [1:0] volume,
    input      [15:0] data_in,
    output reg        data_ready,
    output reg        dac_dat
);

localparam
    CNT_8KHZ = 5'h3,
    MAX_VOL = 2'h4;

wire [4:0]
    rate_cnt;
wire [1:0]
    volume_offset;
reg
    clk_1khz;
reg [4:0]
    ctr_24;
reg [3:0]
    ctr_16;
reg [15:0]
    data;

assign rate_cnt = CNT_8KHZ * {2'b0, freq};
assign volume_offset = MAX_VOL - volume;

always @(posedge dac_lr_clk) begin
    if (reset) begin
        clk_1khz <= 1'b0;
        ctr_24   <= 5'h0;
    end else if (ctr_24 == rate_cnt) begin
        clk_1khz <= ~clk_1khz;
        ctr_24   <= 5'h0;
    end else begin
        clk_1khz <= clk_1khz;
        ctr_24   <= ctr_24 + 4'h1;
    end
end

always @(negedge bclk) begin
    ctr_16 <= (reset || ~enable) ? 4'b0 : ctr_16 + 4'h1;
    if (ctr_16 == 4'h0 || reset || ~enable) begin
        data        <= data_in >>> (volume_offset * 2);
        dac_dat     <= 1'b0;
        data_ready <= 1'b1;
    end else begin
        data       <= data << 1;
        dac_dat    <= data[15] ^ ~clk_1khz;
        data_ready <= 1'b0;
    end
end
endmodule
