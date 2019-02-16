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

always @(posedge reset or posedge dac_lr_clk) begin
    if (reset) begin
        clk_1khz <= 1'b0;
        ctr_24   <= 5'h0;
    end else if (ctr_24 == 5'h17) begin
        clk_1khz <= ~clk_1khz;
        ctr_24   <= 5'h0;
    end else begin
        clk_1khz <= ~clk_1khz;
        ctr_24   <= ctr_24 + 4'h1;
    end
end

always @(negedge bclk) dac_dat = (reset || ~enable) ? 1'b0 : clk_1khz;


endmodule
