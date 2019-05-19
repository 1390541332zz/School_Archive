module audiogen(
    input  reset,
    input  enable,
    input  bclk,
    inout  dac_lr_clk,
    output reg dac_dat
);

reg
    clk_1khz;
reg [4:0]
    ctr_24;
reg [3:0]
    ctr_16;

always @(posedge reset or posedge dac_lr_clk) begin
    if (reset) begin
        clk_1khz <= 1'b0;
        ctr_24   <= 5'h0;
    end else if (ctr_24 == 5'h17) begin
        clk_1khz <= ~clk_1khz;
        ctr_24   <= 5'h0;
    end else begin
        clk_1khz <= clk_1khz;
        ctr_24   <= ctr_24 + 4'h1;
    end
end

localparam
    AUDIO_VAL = 16'h7F;

reg [15:0]
    data;

always @(negedge bclk) begin
    ctr_16 <= (reset || ~enable) ? 4'b0 : ctr_16 + 4'h1;
    if (ctr_16 == 4'h0 || reset || ~enable) begin
        data    <= AUDIO_VAL;
        dac_dat <= 1'b0;
    end else begin
        data    <= data << 1;
        dac_dat <= data[15] ^ ~clk_1khz;
    end
end
endmodule
