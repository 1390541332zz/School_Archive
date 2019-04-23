/*---------------------------------------------------------------------------*
 * Package: Avalon Interfaces                                                *
 * Purpose: Interfaces for Avalon port definitions                           *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

package avalon_interface;

/* Data Based Streaming Interface */
interface st_data #(
    parameter DATA_WIDTH
) (
    input wire clk
);

logic [DATA_WIDTH-1:0] 
    data;
logic
    clk,
    reset,
    valid,    
    ready;

/* Bus Sink Access */
modport sink (
   input  data,
   input  valid,
   output ready
);

/* Bus Source Access */
modport source (
   output data,
   output valid,
   input  ready
);

endinterface : st_data

/* Packet Based Streaming Interface */
interface st_packet #(
    parameter DATA_WIDTH
) (
    input logic clk, reset
);

logic [DATA_WIDTH-1:0] 
    data;
logic
    clk,
    reset,
    start_packet,
    end_packet,
    valid,    
    ready;

/* Bus Sink Access */
modport sink (
   input  data,
   input  start_packet,
   input  end_packet,
   input  valid,
   output ready
);

/* Bus Source Access */
modport source (
   output data,
   output start_packet,
   output end_packet,
   output valid,
   input  ready
);

endinterface : st_package

/* External Bus to Avalon Bridge Interface */
interface mm_ebab #(
    parameter DATA_WIDTH,
    parameter ADDR_WIDTH
) (
    input logic clk, reset
);

logic [ADDR_WIDTH-1:0] 
    addr;
logic [DATA_WIDTH-1:0] 
    read_data,
    write_data;
logic
    clk,
    reset,
    ack,    
    read_en,
    write_en,
    byte_en;

/* Bus Sink Access */
modport sink (
   input  addr,
   input  write_data,
   input  read_en,
   input  write_en,
   input  byte_en,
   output read_data,
   output ack
);

/* Bus Source Access */
modport source (
   output addr,
   output write_data,
   output read_en,
   output write_en,
   output byte_en,
   input  read_data,
   input  ack
);

endinterface : mm_ebab

endpackage
