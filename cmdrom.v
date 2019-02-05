module cmdrom (
    input [3:0] addr,
    output reg [15:0] data // { i2c_addr, start_ptr, end_ptr }
);

always @ (addr) casez (addr)
    4'h0 : data = { 8'h5, 4'h0, 4'h1 };
    4'h1 : data = { 8'h1, 4'h1, 4'h2 };
    4'h2 : data = { 8'h1, 4'h2, 4'h3 };
    4'h3 : data = { 8'h1, 4'h3, 4'h4 };
    4'h? : data = { 16 { 1'bZ }};
    endcase
endmodule
