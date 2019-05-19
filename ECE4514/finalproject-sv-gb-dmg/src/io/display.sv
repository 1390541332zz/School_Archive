/*---------------------------------------------------------------------------*
 * Module: Gameboy DMG Display Interface                                     *
 * Purpose: Converts the 160x144 LCD output to the XGA 1024x768 display and  *
 *     upscales the display by 5X.                                           *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

import avalon_intf::st_state_sink;
import avalon_intf::st_state_source;
import gb_intf::gb_display_line;

module display(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    st_packet.source vga,
    st_data.sink     dmg 
);

localparam
    x_factor   = 5,
    vga_w      = 1024,
    vga_h      = 768,
    vga_color  = 8,
    vga_colors = 3,
    vga_data_w = vga_color * vga_colors,
    dmg_w      = 160,
    dmg_h      = 144,
    dmg_vblank = 10,
    x_mount    = (vga_w / 2) - (dmg_w * x_factor / 2),
    y_mount    = (vga_h / 2) - (dmg_h * x_factor / 2),
    dmg_color  = 2,
    dmg_data_w = dmg_w * dmg_color;

typedef enum bit [vga_data_w-1:0] {
    DISABLE_BLACK  = 24'h000000,
    RGB_BLACK      = 24'h0F380F,
    RGB_DARK_GREY  = 24'h306230,
    RGB_LIGHT_GREY = 24'h8BAC0F,
    RGB_WHITE      = 24'h9BBC0F
} gb_color_palette_rgb;

typedef enum bit [dmg_color-1:0] {
    DMG_BLACK      = 2'h0,
    DMG_DARK_GREY  = 2'h1,
    DMG_LIGHT_GREY = 2'h2,
    DMG_WHITE      = 2'h3
} gb_color_palette_dmg;

bit [$clog2(vga_h)-1:0]
    ctr_vga_y, ctr_vga_y_;
bit [$clog2(vga_w)-1:0]
    ctr_vga_x, ctr_vga_x_;
bit [$clog2(dmg_h)-1:0]
    ctr_dmg_y, ctr_dmg_y_;
bit [$clog2(dmg_w)-1:0]
    ctr_dmg_x, ctr_dmg_x_;
bit [$clog2(x_factor)-1:0]
    ctr_x_y, ctr_x_y_,
    ctr_x_x, ctr_x_x_;
gb_display_line
    dmg_ln, dmg_ln_;
bit
    dmg_x_en,
    dmg_y_en,
    start_packet,
    end_packet;
st_state_source
    vga_s, vga_s_;
st_state_sink
    dmg_s, dmg_s_;
gb_color_palette_rgb
    pixel;

/*---------------------------------------------------------------------------*/
/*                                Assertions                                 */
/*---------------------------------------------------------------------------*/

assert property (vga.clk == dmg.clk);
assert property (vga.reset != dmg.reset);

assert property (
    ($size(vga.data) == vga_data_x)
 && ($size(dmg.data) == dmg_data_x)
);

assert property (
    (x_mount >= 0)
 && (x_mount + dmg_w * x_factor <= vga_w)
 && (y_mount >= 0)
 && (y_mount + dmg_h * x_factor <= vga_h)
);

assert property (dmg_s != RECIEVE);

/*---------------------------------------------------------------------------*/
/*                               Computation                                 */
/*---------------------------------------------------------------------------*/

assign dmg_x_en = (
    (ctr_vga_x >= x_mount) 
 && (ctr_vga_x <  x_mount + dmg_w * x_factor)
 && (ctr_vga_y >= y_mount) 
 && (ctr_vga_y <  y_mount + dmg_h * x_factor)
);

assign dmg_y_en = (
    (ctr_dmg_x == dmg_w - 1)
 && (ctr_vga_y >= y_mount) 
 && (ctr_vga_y <  y_mount + dmg_h * x_factor)
);
    
assign start_packet = (  (vga_s == avalon_intf::STANDBY) 
                      && (vga_s_ == avalon_intf::TRANSMIT)
                      );
assign end_packet   = (ctr_vga_x == vga_w - 1) && (ctr_vga_y == vga_h - 1);

// Pixel Conversion
always_comb if (dmg_x_en && (vga_s == avalon_intf::TRANSMIT)) begin
    case (gb_color_palette_dmg'(dmg_ln[ctr_dmg_x]))
        DMG_BLACK      : pixel = RGB_BLACK;
        DMG_DARK_GREY  : pixel = RGB_DARK_GREY;
        DMG_LIGHT_GREY : pixel = RGB_LIGHT_GREY;
        DMG_WHITE      : pixel = RGB_WHITE;
    endcase 
end else begin
    pixel = DISABLE_BLACK;
end

// DMG Sink Logic
always_comb case (dmg_s)
avalon_intf::WAITING: begin
    dmg_ln_ = dmg.data;
    dmg_s_  = (dmg.valid) ? avalon_intf::PROCESSING : avalon_intf::WAITING;
end
avalon_intf::PROCESSING: begin
    dmg_ln_ = dmg_ln;
    dmg_s_  = (  dmg_x_en 
              && (ctr_dmg_x == dmg_w - 1)
              && (ctr_x_x   == x_factor  - 1)
              ) ? avalon_intf::PROCESSING : avalon_intf::WAITING;
end

endcase

// VGA Source Logic
always_comb case (vga_s)
avalon_intf::STANDBY: begin
    ctr_vga_y_ = 'b0;
    ctr_vga_x_ = 'b0;
    ctr_dmg_y_ = 'b0;
    ctr_dmg_x_ = 'b0;
    ctr_x_y_   = 'b0;
    ctr_x_x_   = 'b0;
    vga_s_     = (dmg_s == avalon_intf::PROCESSING && vga.ready) 
               ? avalon_intf::TRANSMIT
               : avalon_intf::STANDBY;
end
avalon_intf::TRANSMIT: begin
    // VGA Position Control: XY Coord
    if ((ctr_vga_x < vga_w) && (ctr_vga_y < vga_h)) begin
        ctr_vga_x_ = ctr_vga_x + 1;
        ctr_vga_y_ = ctr_vga_y;
        vga_s_     = avalon_intf::TRANSMIT;
    end else if (ctr_vga_y < vga_h) begin
        ctr_vga_x_ = 'b0;
        ctr_vga_y_ = ctr_vga_y + 1;
        vga_s_     = avalon_intf::TRANSMIT;
    end else begin
        ctr_vga_y_ = 'b0;
        ctr_vga_x_ = 'b0;
        vga_s_     = avalon_intf::STANDBY;
    end
    
    // DMG Position Control: X Coord
    if ((ctr_x_x < x_factor) && dmg_x_en) begin
        ctr_dmg_x_ = ctr_dmg_x;
        ctr_x_x_   = ctr_x_x + 1;
    end else if (dmg_x_en) begin
        ctr_dmg_x_ = ctr_dmg_x + 1;
        ctr_x_x_   = 'b0;
    end else begin
        ctr_dmg_x_ = 'b0;
        ctr_x_x_   = 'b0;
    end
    
    // DMG Position Control: Y Coord
    if ((ctr_x_y < x_factor) && dmg_y_en) begin
        ctr_dmg_y_ = ctr_dmg_y;
        ctr_x_y_   = ctr_x_y + 1;
    end else if (dmg_y_en) begin
        ctr_dmg_y_ = ctr_dmg_y + 1;
        ctr_x_y_   = 'b0;
    end else begin
        ctr_dmg_y_ = 'b0;
        ctr_x_y_   = 'b0;
    end
end
endcase

always_ff @(posedge vga.clk) if (vga.reset) begin  
    ctr_vga_y        <= 'b0;
    ctr_vga_x        <= 'b0;
    ctr_dmg_y        <= 'b0;
    ctr_dmg_x        <= 'b0;
    ctr_x_y          <= 'b0;
    ctr_x_x          <= 'b0;
    dmg_ln           <= 'b0;
    vga.valid        <= 'b0; 
    dmg.ready        <= 'b0;
    vga_s            <= avalon_intf::STANDBY;
    dmg_s            <= avalon_intf::WAITING;
    vga.data         <= 'b0;
    vga.start_packet <= 1'b0;
    vga.end_packet   <= (vga_s == avalon_intf::TRANSMIT);
end else begin
    ctr_vga_y        <= ctr_vga_y_;
    ctr_vga_x        <= ctr_vga_x_;
    ctr_dmg_y        <= ctr_dmg_y_;
    ctr_dmg_x        <= ctr_dmg_x_;
    ctr_x_y          <= ctr_x_y_;
    ctr_x_x          <= ctr_x_x_;
    dmg_ln           <= dmg_ln_;
    vga.valid        <= (vga_s == avalon_intf::TRANSMIT);
    dmg.ready        <= (dmg_s == avalon_intf::WAITING);
    vga_s            <= vga_s_;
    dmg_s            <= dmg_s_;
    vga.data         <= pixel;
    vga.start_packet <= start_packet; 
    vga.end_packet   <= end_packet; 
end

endmodule : display
