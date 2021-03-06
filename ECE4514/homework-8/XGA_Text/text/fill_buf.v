/*---------------------------------------------------------------------------*
 * Module: Screen Buffer Filler                                              *
 * Purpose: Fills the next screen buffer frame with random characters        *
 * Last Edit: 2019-04-12                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

`include "const_funcs.h"

module fill_buf #(
/*---------------------------------------------------------------------------*/
/*                            Module Templating                              */
/*---------------------------------------------------------------------------*/
    parameter width,
    parameter height,
    parameter char_width,
    parameter blank_char
)(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    input  wire                      clk,
    input  wire                      reset,        
    input  wire                      refresh,
    input  wire                      zero_buf,
    output reg                       write_en,
    output reg  [log2(width ) - 1:0] x,
    output reg  [log2(height) - 1:0] y,
    output wire [char_width - 1:0]   c_out    
);

localparam
    uppercase_a        = 10,
    lowercase_a        = uppercase_a + 26,
    numeric_offset     = 48,
    uppercase_a_offset = 65 - uppercase_a,
    lowercase_a_offset = 97 - lowercase_a; 

wire [char_width - 1:0]
    c; 
wire [log2(width ) - 1:0] 
    x_next;
wire [log2(height) - 1:0] 
    y_next;
wire
    write_en_next;

/*---------------------------------------------------------------------------*/
/*                                 Compute                                   */
/*---------------------------------------------------------------------------*/

assign c_out  = (zero_buf)         ? blank_char
              : (c >= lowercase_a) ? c + lowercase_a_offset
              : (c >= uppercase_a) ? c + uppercase_a_offset
                                   : c + numeric_offset;

/* verilator lint_off WIDTH */
always @(*) if (write_en) begin
    if (x >= (width - 1)) begin
        x_next = 0;
        y_next = (y >= (width - 1)) ? 0 : y + 1;
    end else begin
        x_next = x + 1;
        y_next = y;
    end
end else begin
    x_next = x;
    y_next = y;
end

assign write_en_next = write_en ^ ((x == (width - 1)) && (y == (height - 1)));
/* verilator lint_on WIDTH */

always @(posedge clk) begin
    x        <= (reset || refresh) ?    0 : x_next;
    y        <= (reset || refresh) ?    0 : y_next;
    write_en <= (reset || refresh) ? 1'b1 : write_en_next;
end

/*---------------------------------------------------------------------------*/
/*                                Submodules                                 */
/*---------------------------------------------------------------------------*/

character_gen #(
    .char_width(char_width),
    .num_of_chars(26 * 2 + 10)
) char_gen (
    .clk(clk),
    .reset(reset),
    .c_out(c)
);


endmodule
