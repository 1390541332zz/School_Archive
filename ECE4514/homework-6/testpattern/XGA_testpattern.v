module XGA_testpattern(
    input  wire       CLOCK_50,
    input  wire [3:0] KEY,
	input  wire [9:0] SW,
    output wire [7:0] VGA_R,
    output wire [7:0] VGA_G,
    output wire [7:0] VGA_B,
    output wire       VGA_CLK,
    output wire       VGA_BLANK_N,
    output wire       VGA_SYNC_N,
    output wire       VGA_HS,
    output wire       VGA_VS
);

/* Constant Time Functions */
function integer log2(input integer x); begin
    x = x - 1;
    for (log2 = 0; x > 0; log2 = log2 + 1) x = x >> 1;
end endfunction

localparam 
    width  = 1024, 
    height = 768;

wire
    clk_75;
wire [log2(width) - 1:0]
    h_pos;
wire [log2(height) - 1:0]
    v_pos;
wire [7:0]
    vga_r,
    vga_g,
    vga_b;

altpll_75 pll(
    .refclk(CLOCK_50),
    .rst(1'b0),
    .outclk_0(clk_75),
    /* verilator lint_off PINCONNECTEMPTY */
    .locked()
    /* verilator lint_on PINCONNECTEMPTY */
);

vga_driver #(
    .vga_width(width),
    .vga_height(height),
    .color_depth( 8),
    /* Horizontal Timing Properties */
    .h_front_cnt(24),
    .h_sync_cnt(136),
    .h_back_cnt(144),
    .pixel_cnt(   1),
    /* Vertical Timing Properties */
    .v_front_cnt( 3),
    .v_sync_cnt(  6),
    .v_back_cnt( 29),
    .frame_cnt(   1)
) xga (
    .clk(clk_75),        
    .vga_r_in(vga_r),
    .vga_g_in(vga_g),
    .vga_b_in(vga_b),
    .vga_r_out(VGA_R),
    .vga_g_out(VGA_G),
    .vga_b_out(VGA_B),
    .vga_clk(VGA_CLK),
    .vga_blank_n(VGA_BLANK_N),
    .vga_sync_n(VGA_SYNC_N),
    .vga_hs(VGA_HS),
    .vga_vs(VGA_VS),
    .h_pos(h_pos),
    .v_pos(v_pos)
);

assign vga_r = {8{h_pos[log2(width) - 3]}};
assign vga_g = {8{h_pos[log2(width) - 2]}};
assign vga_b = {8{h_pos[log2(width) - 1]}};

endmodule
