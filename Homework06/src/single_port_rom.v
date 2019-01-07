module single_port_rom (
    input [(addr_width-1):0] addr,
    input clk,
    output reg [(data_width-1):0] q
);

parameter data_width = 3;
parameter addr_width = 5;

reg [data_width-1:0] rom[2**addr_width-1:0];
initial begin
    $readmemb("single_port_rom_init.txt", rom);
end

always @(posedge clk) begin
    q <= rom[addr];
end

endmodule
