module datarom (
    input [3:0] addr;
    output reg [7:0] data;
)

always @ (addr) casez (addr)
    4'h0 : data = 8'hAA;
    4'h1 : data = 8'h12;
    4'h2 : data = 8'h55;
    4'h3 : data = 8'hDE;
    4'h? : data = 8'h00;
endcase
endmodule
