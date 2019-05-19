module i2cmasterwrite(input      clk,
                      input  reset,
                      input  init,
                      output sck,
                      inout  sda
                      );
   
   wire [2:0]                command;
   wire                      bitready;
   
   wire [6:0]                address;
   assign address = 7'h1a;
   
   reg                       load;
   reg [15:0]                data, datanext;
   wire                      ready;
   
   i2cgenerator dut1(.clk(clk),
                     .reset(reset),
                     .address(address),
                     .data(data),
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
   
   localparam S0 = 0, REG1 = 1, REG2 = 2, REG3 = 3, REG4 = 4;   
   reg [2:0]                 state, statenext;
   
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
             if (init) begin
                statenext   = REG1;
                datanext    = 16'h05AA;  // write AA to control address 05
                load        = 1'b1;
             end
          end
          REG1: begin
             if (ready) begin
                statenext  = REG2;
                datanext   = 16'h0112;  // write 12 to control address 01
                load        = 1'b1;
             end
          end
          REG2: begin
             if (ready) begin
                statenext  = REG3;
                datanext   = 16'h0255;  // write 55 to control address 02
                load        = 1'b1;
             end
          end
          REG3: begin
             if (ready) begin
                statenext  = REG4;
                datanext   = 16'h00DE;  // write DE to control address 00
                load        = 1'b1;
             end
          end
          REG4: begin
             if (ready) begin
                statenext  = S0;
                datanext   = 16'h0;
             end
          end
        endcase
     end
   
endmodule
