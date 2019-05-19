module codec_cfg(
	input      	 clk,
	output     	 i2c_sclk,
	inout      	 i2c_sdat,
	input  [3:0] key,
	output       audio_ready
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

i2c_gen i2c_srv(
    .clk(clk),
    .reset(reset),
    .address(address),
    .data(data),
    .load(load),
    .ready(ready),
    .command(command),
    .bitready(bitready)
);

bit_stream i2c_cmd(
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
	SILENCE_B = 5,
	AUDIO_A = 6,
	AUDIO_B = 7,
	AUDIO_C = 8,
	AUDIO_D = 9,
	AUDIO_E = 10,
	AUDIO_F = 11,
	AUDIO_G = 12,
	AUDIO = 13,
	CUR_STATE = 14;

wire [3:0]
    state_bridge;
reg [3:0] 
    state, 
	statenext;
	
assign audio_ready = (state == AUDIO);

assign state_bridge = (key[0] == 1'b0) ? RESET
                    : (key[1] == 1'b0) ? LOOPBACK_A
                    : (key[2] == 1'b0) ? AUDIO_A
                    : (key[3] == 1'b0) ? SILENCE_A
                                       : CUR_STATE;

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
            statenext = (state_bridge == CUR_STATE) ? WAIT : state_bridge;
            datanext  = 16'h0000; 
            load      = 1'b0;
        end
        LOOPBACK_A: if (ready) begin
            statenext = LOOPBACK_B;
            datanext  = {7'h06, 9'b0_0000_1010};  // Poweron
            load      = 1'b1;
        end
        LOOPBACK_B: if (ready) begin
            statenext = WAIT;
            datanext  = {7'h04, 9'h0A};  // Analogue Audio Control
            load      = 1'b1;
        end
        SILENCE_A: if (ready) begin
            statenext = SILENCE_B;
            datanext  = {7'h04, 9'h02};  // Analogue Audio Control
            load      = 1'b1;
        end
        SILENCE_B: if (ready) begin
            statenext = WAIT;
            datanext  = {7'h06, 9'b0_1001_1111};  // Poweroff
            load      = 1'b1;
        end
        AUDIO_A: if (ready) begin
            statenext = AUDIO_B;
            datanext  = {7'h09, 9'b0_0000_0000};  // Deactivate
            load      = 1'b1;
        end
        AUDIO_B: if (ready) begin
            statenext = AUDIO_C;
            datanext  = {7'h06, 9'b0_0000_0011};  // Poweron
            load      = 1'b1;
        end
        AUDIO_C: if (ready) begin
            statenext = AUDIO_D;
            datanext  = {7'h04, 9'b0_0001_0010};  // Analogue Audio Control
            load      = 1'b1;
        end
        AUDIO_D: if (ready) begin
            statenext = AUDIO_E;
            datanext  = {7'h07, 9'b0_0100_0001};  // Digital Audio Format
            load      = 1'b1;
        end
        AUDIO_E: if (ready) begin
            statenext = AUDIO_F;
            datanext  = {7'h05, 9'b0_0000_0110};  // DAC Controls
            load      = 1'b1;
        end
        AUDIO_F: if (ready) begin
            statenext = AUDIO_G;
            datanext  = {7'h08, 9'b0_0000_0000};  // Sampling Control
            load      = 1'b1;
        end
        AUDIO_G: if (ready) begin
            statenext = AUDIO;
            datanext  = {7'h09, 9'b0_0000_0001};  // Activate
            load      = 1'b1;
        end
        AUDIO: if (ready) begin
            statenext = (state_bridge == CUR_STATE) ? AUDIO : state_bridge;
            datanext  = 16'h0000;  // Run Audio loop
            load      = 1'b0;
        end
        default: begin 
        end
    endcase
end

endmodule
