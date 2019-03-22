module audio_gen(
    input             clk,
    input             reset,
    input             enable,
    input             bclk,
    inout             dac_lr_clk,
    input       [2:0] freq,
    input       [1:0] volume,
    input      [15:0] data_in,
    output            data_ready,
    output            dac_dat
);

localparam
    CNT_8KHZ = 5'h3; 

wire
    bclk_next,
    lr_clk_next,
    lr_clk_tick,
    bclk_tick;
wire [4:0]
    rate_cnt;
reg
    bclk_old,
    lr_clk;
reg [4:0]
    ctr_24_next,
    ctr_24;
reg [63:0]
    sample,
    sample_next;

assign bclk_tick   = ( bclk_old & ~bclk);    // negative edge of bclk_old
assign lr_clk_tick = (~lr_clk & dac_lr_clk); // positive edge of lr_clk

assign bclk_next   = bclk;
assign lr_clk_next = dac_lr_clk;

assign dac_dat  = sample[63];
assign rate_cnt = CNT_8KHZ /* {2'b0, freq})*/ - 5'h1;

assign data_ready = lr_clk_tick;

always @(posedge clk) begin
    ctr_24     <= ctr_24_next;
    sample     <= (reset) ? 64'h0 : sample_next;
    bclk_old   <= (reset) ?  1'h0 : bclk_next;
    lr_clk     <= (reset) ?  1'h0 : lr_clk_next;
end

always @(*) begin
    /* Clock Data */
    if (reset) begin
        ctr_24_next = 5'h0;
    end else if (lr_clk_tick) begin
        ctr_24_next = (ctr_24 == rate_cnt) ? 5'h0
                                           : ctr_24 + 5'h1;
    end else begin
        ctr_24_next = ctr_24;
    end
    /* Sample Data */
    sample_next = (lr_clk_tick) ? {2{{data_in >>> (volume * 3'h2), 16'h0}}}
                : (bclk_tick)   ? (sample << 1)
                                : sample;
end
endmodule
