module codecpgm(
	input 		          		clk,
	output		          		i2c_sclk,
	inout 		          		i2c_sdat,
	input 		     [3:0]		key
);

// ---- reset ----
wire reset;
assign reset = ~key[0];

wire
    bitready,
    ready;
wire [2:0] 
    command;
wire [6:0]
    address;
reg 
    load;
reg [15:0] 
    data, datanext;
    
assign address = 7'h1a;

i2cgenerator dut1(
    .clk(clk),
    .reset(reset),
    .address(address),
    .data(data),
    .load(load),
    .ready(ready),
    .command(command),
    .bitready(bitready)
);

bitxmit dut2(
    .clk(clk),
    .reset(reset),
    .command(command),
    .ready(bitready),
    .sck(i2c_sclk),
    .sda(i2c_sdat)
);

localparam 
	RESET = 0, 
	WAIT = 1, 
	LOOPBACK_A = 2, 
	LOOPBACK_B = 3, 
	SILENCE_A = 4,
	SILENCE_B = 5;

reg [2:0] 
	state, 
	statenext;

always @(posedge clk) begin
    if (reset) begin
        state   <= RESET;
        data    <= 16'h0;
    end
    else begin
        state   <= statenext;
        data    <= datanext;
    end
end

always @(*) begin
    statenext   = state;
    load        = 1'b0;
    datanext    = data;
    case (state)
        RESET: if (ready) begin
            statenext = WAIT;
            datanext  = {7'h0F, 9'h00};  // write 00 to control address 0F
            load      = 1'b1;
        end
        WAIT: if (ready) begin
            statenext = (key[0] == 1'b0) ? RESET
                      : (key[1] == 1'b0) ? LOOPBACK_A
                      : (key[2] == 1'b0) ? SILENCE_A
                                         : WAIT;
            datanext  = 16'hZZZZ; 
            load      = 1'b0;
        end
        LOOPBACK_A: if (ready) begin
            statenext = LOOPBACK_B;
            datanext  = {7'h06, 9'b0_0000_1110};  // Poweron
            load      = 1'b1;
        end
        LOOPBACK_B: if (ready) begin
            statenext = WAIT;
            datanext  = {7'h04, 9'b0_0000_1010};  // Analogue Audio Control
            load      = 1'b1;
        end
        SILENCE_A: if (ready) begin
            statenext = SILENCE_B;
            datanext  = {7'h04, 9'b0_0000_0010};  // Analogue Audio Control
            load      = 1'b1;
        end
        SILENCE_B: if (ready) begin
            statenext = WAIT;
            datanext  = {7'h06, 9'b0_1001_1111};  // Poweroff
            load      = 1'b1;
        end
    endcase
end

endmodule

// quartus_sh --flow compile loopback
// quartus_pgm -m jtag -o "p;loopback.sof@2"
