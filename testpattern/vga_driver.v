module vga_driver #(
    /* Display Properties */
    parameter vga_width   = 1024,
    parameter vga_height  = 768,
    parameter color_depth = 8,

    /* Horizontal Timing Properties */
    parameter h_front_cnt = 24,
    parameter h_sync_cnt  = 136,
    parameter h_back_cnt  = 144,
    parameter pixel_cnt   = 1,
    
    /* Vertical Timing Properties */
    parameter v_front_cnt = 3,
    parameter v_sync_cnt  = 6,
    parameter v_back_cnt  = 29,
    parameter frame_cnt   = 1,
    
    parameter h_addr_cnt  = pixel_cnt * vga_width,
    parameter v_addr_cnt  = frame_cnt * vga_height,
    
    /* Horizontal Timing Triggers */
    parameter h_front_start = 0,
    parameter h_sync_start  = h_front_start + h_front_cnt, 
    parameter h_back_start  = h_sync_start  + h_sync_cnt,
    parameter h_addr_start  = h_back_start  + h_back_cnt,
    parameter h_cnt         = h_addr_start  + h_addr_cnt,
    
    /* Vertical Timing Triggers */
    parameter v_front_start = 0,
    parameter v_sync_start  = v_front_start + v_front_cnt, 
    parameter v_back_start  = v_sync_start  + v_sync_cnt,
    parameter v_addr_start  = v_back_start  + v_back_cnt,
    parameter v_cnt         = v_addr_start  + v_addr_cnt
)(
    input  wire                     clk,             
    input  wire [color_depth - 1:0] vga_r_in,
    input  wire [color_depth - 1:0] vga_g_in,
    input  wire [color_depth - 1:0] vga_b_in,
    output wire [color_depth - 1:0] vga_r_out,
    output wire [color_depth - 1:0] vga_g_out,
    output wire [color_depth - 1:0] vga_b_out,
    output wire                     vga_clk,
    output wire                     vga_blank_n,
    output wire                     vga_sync_n,
    output wire                     vga_hs,
    output wire                     vga_vs,
    output reg [log2(h_cnt) - 1:0]  ctr_h,
    output reg [log2(v_cnt) - 1:0]  ctr_v
);

/* Constant Time Functions */
function integer log2(input integer x); begin
    x = x - 1;
    for (log2 = 0; x > 0; log2 = log2 + 1) x = x >> 1;
end endfunction

/*---------------------------------------------------------------------------*/


wire [log2(h_cnt) - 1:0]
    ctr_h_next;
wire [log2(v_cnt) - 1:0]
    ctr_v_next;
wire
    /* Horizontal Ticks */
    h_sync,
//  h_back,
    h_addr,
//  h_front,

    /* Vertical Ticks */
    v_sync,
//  v_back,
//  v_front,
    v_addr;

/*---------------------------------------------------------------------------*/

//assign h_front   = (ctr_h >= h_front_start) && (ctr_h < h_sync_start );
assign h_sync      = (ctr_h >= h_sync_start ) && (ctr_h < h_back_start );
//assign h_back    = (ctr_h >= h_back_start ) && (ctr_h < h_addr_start );
assign h_addr      = (ctr_h >= h_addr_start ) && (ctr_h < h_cnt        );
//assign v_front   = (ctr_v >= v_front_start) && (ctr_v < v_sync_start );
assign v_sync      = (ctr_v >= v_sync_start ) && (ctr_v < v_back_start );
//assign v_back    = (ctr_v >= v_back_start ) && (ctr_v < v_addr_start );
assign v_addr      = (ctr_v >= v_addr_start ) && (ctr_v < v_cnt        );
assign vga_clk     = clk;
assign vga_r_out   = (h_addr) ? vga_r_in : 0;
assign vga_g_out   = (h_addr) ? vga_g_in : 0;
assign vga_b_out   = (h_addr) ? vga_b_in : 0;
assign vga_hs      = ~h_sync;
assign vga_vs      = ~v_sync;
assign vga_sync_n  = vga_hs ~^ vga_vs;
assign vga_blank_n = ~(v_addr | h_addr);

assign ctr_h_next  = ctr_h + 1;
assign ctr_v_next  = ctr_v;

always @(posedge clk) begin
    if (ctr_h_next < h_cnt) begin
        ctr_h <= ctr_h_next;
        ctr_v <= ctr_v_next;
    end else if (ctr_v_next + 1 < v_cnt) begin
        ctr_h <= 0;
        ctr_v <= ctr_v_next + 1;
    end else begin
        ctr_h <= 0;
        ctr_v <= 0;
    end
end

endmodule
