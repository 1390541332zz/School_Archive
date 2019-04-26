module dualport_ram #(
    parameter DATA_SIZE  = 64,
    parameter DATA_WIDTH = 8
)(
    input  bit                         clk,
    input  bit                         we,
    input  bit [$clog2(DATA_SIZE)-1:0] addr_a, addr_b,
    input  bit [DATA_WIDTH-1:0]        din_a,
    output bit [DATA_WIDTH-1:0]        dout_a, dout_b
);

// signal declaration
bit [$clog2(DATA_SIZE)-1:0] ram [DATA_WIDTH-1:0];
bit [$clog2(DATA_SIZE)-1:0] addr_a_reg, addr_b_reg;

// body
always_ff @(posedge clk) begin
    if (we) begin  // write operation
        ram[addr_a] <= din_a;
    end
    addr_a_reg <= addr_a;
    addr_b_reg <= addr_b;
end

// two read operations
assign dout_a = ram[addr_a_reg];
assign dout_b = ram[addr_b_reg];

endmodule : dualport_ram
