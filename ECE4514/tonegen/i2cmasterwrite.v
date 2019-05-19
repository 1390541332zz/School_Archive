module i2cmasterwrite(input  clk,
                      input  reset,
                      input  loopback,
                      input  audioon,
                      input  audiooff,
                      output sck,
                      inout  sda
                      );
   // loopback: place IC in loopback mode
   // 
   // R4   0_0000_1010   bypass on
   // R6   0_0000_0000   all on
   //
   // audiooff: place IC on power-off, disable bypass
   //
   // R4   0_0000_0010   bypass off
   // R9   0_0000_0000   disable audio interface
   // R6   0_1111_1111   power down
   //
   // audioon: turn on IC, DAC to headphone out
   //          16 bit audio, master mode
   //          48 KHz
   //
   // R4   0_0001_0010  dac on
   // R5   0_0000_0110  digital demphasis 48KHz
   // R6   0_0000_0000  all on
   // R7   0_0100_0001  msb first left justified, master mode, 16 bit
   // R8   0_0000_0000  48KHz sample rate
   // R9   0_0000_0001  activate audio interface

   wire [2:0]                command;
   wire                      bitready;
   
   wire [6:0]                address;
   assign address = 7'h1a;
   
   reg                       load;
   reg [15:0]                data, datanext;
   wire                      ready;
   
   i2cgenerator dut1(.clk(clk),
                     .reset(reset),
                     .address(address),    // i2c slave address
                     .data(data),          // 16-bit data
                     .load(load),
                     .ready(ready),
                     .command(command),
                     .bitready(bitready));
   
   bitxmit dut2(.clk(clk),
                .reset(reset),
                .command(command),
                .ready(bitready),
                .sck(sck),
                .sda(sda));
   
   localparam S0 = 0, 
              LOOPBACK1  = 1, 
              LOOPBACK2  = 2, 
              AUDIOOFF1  = 3,
              AUDIOOFF2  = 4,
              AUDIOOFF3  = 5,
              AUDIOON1   = 6,
              AUDIOON2   = 7,
              AUDIOON3   = 8,
              AUDIOON4   = 9,
              AUDIOON5   = 10,
              AUDIOON6   = 11;

   reg [4:0]                 state, statenext;
   
   always @(posedge clk)
     begin
        if (reset) begin
           state   <= S0;
           data    <= 16'h0;
        end
        else begin
           state   <= statenext;
           data    <= datanext;
        end
     end
   
   always @(*)
     begin
        statenext   = state;
        load        = 1'b0;
        datanext    = data;
        case (state)
          S0: begin
             if (loopback) begin
                statenext   = LOOPBACK1;
                datanext    = {7'h04, 9'b0_0000_1010};  // enable bypass
                load        = 1'b1;
             end else if (audiooff) begin
                statenext   = AUDIOOFF1;
                datanext    = {7'h04, 9'b0_0000_0010};  // disable bypass
                load        = 1'b1;
             end else if (audioon) begin
                statenext   = AUDIOON1;
                datanext    = {7'h04, 9'b0_0001_0010};  // DAC on
                load        = 1'b1;
             end
          end
          LOOPBACK1: begin
             if (ready) begin
                statenext  = LOOPBACK2;
                datanext   = {7'h06, 9'b0_0000_0000};   // power on
                load        = 1'b1;
             end
          end
          LOOPBACK2: begin
             if (ready) begin
                statenext  = S0;
                datanext   = 16'h0;
             end
          end
          AUDIOOFF1: begin
             if (ready) begin
                statenext  = AUDIOOFF2;
                datanext   = {7'h09, 9'b0_0000_0000};   // disable audio interface
                load        = 1'b1;
             end
          end
          AUDIOOFF2: begin
             if (ready) begin
                statenext  = AUDIOOFF3;
                datanext   = {7'h06, 9'b0_1111_1111};   // power off
                load        = 1'b1;
             end
          end
          AUDIOOFF3: begin
             if (ready) begin
                statenext  = S0;
                datanext   = 16'h0;
             end
          end
          AUDIOON1: begin
             if (ready) begin
                statenext  = AUDIOON2;
                datanext   = {7'h05, 9'b0_0000_0110};   // digital demphasis 48KHz
                load        = 1'b1;
             end
          end
          AUDIOON2: begin
             if (ready) begin
                statenext  = AUDIOON3;
                datanext   = {7'h06, 9'b0_0000_0000};   // all on
                load        = 1'b1;
             end
          end
          AUDIOON3: begin
             if (ready) begin
                statenext  = AUDIOON4;
                datanext   = {7'h07, 9'b0_0100_0001};   // msb first left justified, master mode, 16 bit
                load        = 1'b1;
             end
          end
          AUDIOON4: begin
             if (ready) begin
                statenext  = AUDIOON5;
                datanext   = {7'h08, 9'b0_0000_0000};   // 48KHz sample rate
                load        = 1'b1;
             end
          end
          AUDIOON5: begin
             if (ready) begin
                statenext  = AUDIOON6;
                datanext   = {7'h09, 9'b0_0000_0001};   // activate audio interface
                load        = 1'b1;
             end
          end
          AUDIOON6: begin
             if (ready) begin
                statenext  = S0;
                datanext   = 16'h0;
             end
          end
          default:
             statenext = S0;
        endcase
     end
   
endmodule
