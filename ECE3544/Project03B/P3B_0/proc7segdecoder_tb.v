`timescale 1ns/100ps
module prog7segdecoder_tb ();
    reg [3:0] hex_in;
    reg [4:0] count;
    wire [6:0] display_out;

    prog7segdecoder DUT(hex_in, display_out);

    initial begin
        hex_in = 0;
        #1;
        for (count = 0; count < 16; count = count + 1) begin
            hex_in = count;
            #1;
        end
    end
endmodule
