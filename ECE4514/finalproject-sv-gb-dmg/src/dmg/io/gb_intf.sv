/*---------------------------------------------------------------------------*
 * Package: Gameboy Interfaces                                               *
 * Purpose: Interfaces for Gameboy IO                                        *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

package gb_intf;

import avalon_intf::st_state_source;
import avalon_intf::st_state_sink;

parameter
    dmg_w     = 160,
    dmg_color = 2;

/* Controller Button Input (Active Low) */
typedef struct packed {
    bit A;  
    bit B;
    bit select;
    bit start;
    bit up; 
    bit down; 
    bit left;
    bit right;
} cntrlr_data;

typedef bit [dmg_color-1:0][dmg_w-1:0] gb_display_line;

endpackage: gb_intf

typedef struct {
    bit [7:0] r_p1,    // Controller
    bit [7:0] r_sb,    // Serial Transfer Register
    bit [7:0] r_sc,    // Serial Control
    bit [7:0] r_div,   // Timer Divider
    bit [7:0] r_tima,  // Timer
    bit [7:0] r_tma,   // Timer Modulo
    bit [7:0] r_tac,   // Timer Control
    bit [7:0] r_if,    // Interrupt Request
    bit [7:0] r_ie,    // Interrupt Enable 
    bit [7:0] r_ime,   // Interrupt Master Enable 
    bit [7:0] r_lcdc,  // LCD Control
    bit [7:0] r_stat,  // LCD Status
    bit [7:0] r_scy,   // LCD Scroll Y
    bit [7:0] r_scx,   // LCD Scroll X
    bit [7:0] r_ly,    // LCD Y Coordinate 
    bit [7:0] r_lyc,   // LCD Y Comparison 
    bit [7:0] r_dma,   // DMA Transfer Register
    bit [7:0] r_bgp,   // Background Palette Data
    bit [7:0] r_obp0,  // Object Palette Data 0
    bit [7:0] r_obp1,  // Object Palette Data 1
    bit [7:0] r_obp1,  // Object Palette Data 1
    bit [7:0] r_wy,    // Window Y Coordinate
    bit [7:0] r_wx,    // Window X Coordinate
//  bit [7:0] r_key1,  // -- CBG ONLY -- 
//  bit [7:0] r_vbk,   // -- CBG ONLY -- 
//  bit [7:0] r_hdma1, // -- CBG ONLY -- 
//  bit [7:0] r_hdma2, // -- CBG ONLY -- 
//  bit [7:0] r_hdma3, // -- CBG ONLY -- 
//  bit [7:0] r_hdma4, // -- CBG ONLY -- 
//  bit [7:0] r_hdma5, // -- CBG ONLY -- 
//  bit [7:0] r_rp,    // -- CBG ONLY -- 
//  bit [7:0] r_bcps,  // -- CBG ONLY -- 
//  bit [7:0] r_bcpd,  // -- CBG ONLY -- 
//  bit [7:0] r_ocps,  // -- CBG ONLY -- 
//  bit [7:0] r_ocpd,  // -- CBG ONLY -- 
//  bit [7:0] r_svbk,  // -- CBG ONLY -- 
    bit [7:0][3:0] r_obj [39:0], // Object Data    
} mmio_reg_cntrl;
