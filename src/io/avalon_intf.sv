/*---------------------------------------------------------------------------*
 * Package: Avalon Interfaces                                                *
 * Purpose: Interfaces for Avalon port definitions                           *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

package avalon_intf;

typedef enum {
    STANDBY,
    TRANSMIT
} st_state_source;

typedef enum {
    WAITING,
    PROCESSING
} st_state_sink;

endpackage : avalon_intf

/* Data Based Streaming Interface */
interface st_data #(
    parameter data_width
) (
    input logic clk, reset
);

logic [data_width-1:0] 
    data;
logic
    valid,    
    ready;

/* Bus Sink Access */
modport sink (
   input  clk,
   input  reset,
   input  data,
   input  valid,
   output ready
);

/* Bus Source Access */
modport source (
   input  clk,
   input  reset,
   output data,
   output valid,
   input  ready
);

endinterface : st_data

/* Packet Based Streaming Interface */
interface st_packet #(
    parameter data_width
) (
    input logic clk, reset
);

logic [data_width-1:0] 
    data;
logic
    start_packet,
    end_packet,
    valid,    
    ready;

/* Bus Sink Access */
modport sink (
   input  clk,
   input  reset,
   input  data,
   input  start_packet,
   input  end_packet,
   input  valid,
   output ready
);

/* Bus Source Access */
modport source (
   input  clk,
   input  reset,
   output data,
   output start_packet,
   output end_packet,
   output valid,
   input  ready
);

endinterface : st_packet

/* External Bus to Avalon Bridge Interface */
interface mm_ebab #(
    parameter data_width,
    parameter addr_width
) (
    input logic clk, reset
);

logic [addr_width-1:0] 
    addr;
logic [data_width-1:0] 
    read_data,
    write_data;
logic
    ack,    
    read_en,
    write_en,
    byte_en;

/* Bus Sink Access */
modport master (
   input  clk,
   input  reset,
   input  addr,
   input  write_data,
   input  read_en,
   input  write_en,
   input  byte_en,
   output read_data,
   output ack
);

/* Bus Source Access */
modport slave (
   input  clk,
   input  reset,
   output addr,
   output write_data,
   output read_en,
   output write_en,
   output byte_en,
   input  read_data,
   input  ack
);

endinterface : mm_ebab
