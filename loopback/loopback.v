module loopback(
	input 		          		AUD_ADCDAT,
	inout 		          		AUD_ADCLRCK,
	inout 		          		AUD_BCLK,
	output		          		AUD_DACDAT,
	inout 		          		AUD_DACLRCK,
	output		          		AUD_XCK,

	input 		          		CLOCK2_50,
	input 		          		CLOCK3_50,
	input 		          		CLOCK4_50,
	input 		          		CLOCK_50,

	output		          		FPGA_I2C_SCLK,
	inout 		          		FPGA_I2C_SDAT,

	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR,

	inout 		    [35:0]		GPIO
);

// ---- reset ----
wire reset;
assign reset = ~KEY[0];

// ---- heartbeat ----
reg [24:0] counter, counternext;

always @(posedge CLOCK_50)
counter <= (reset) ? 24'h0 : counternext;

always @(*)
counternext = counter + 24'h1;

assign LEDR[9] = counter[24];

//---------- YOUR DESIGN STARTS HERE -----------------
// You can add code to this file, or add new verilog files.
// If you add new files, put all of them in the same directory
// as this file.

wire
    clk,
    bitready,
    ready;
wire [2:0] 
    command;
wire [6:0]
    address;
reg 
    load,
    clk_125,
    clk_250;
reg [15:0] 
    data, datanext;
    
assign clk = CLOCK_50;
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
    .sck(FPGA_I2C_SCLK),
    .sda(FPGA_I2C_SDAT)
);

always @(posedge clk)     clk_250 <= (reset) ? 1'b0 : ~clk_250;
always @(posedge clk_250) clk_125 <= (reset) ? 1'b0 : ~clk_125;

localparam RESET = 0, WAIT = 1, LOOPBACK = 2, SILENCE = 3;
reg [2:0] state, statenext;

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
            datanext  = 16'h0F00;  // write 00 to control address 0F
            load      = 1'b1;
        end
        WAIT: if (ready) begin
            statenext = (KEY[0] == 1'b0) ? RESET
                      : (KEY[1] == 1'b0) ? LOOPBACK 
                      : (KEY[2] == 1'b0) ? SILENCE 
                                         : WAIT;
            datanext  = 16'hZZZZ; 
            load      = 1'b0;
        end
        LOOPBACK: if (ready) begin
            statenext = WAIT;
            datanext  = 16'h040A;  // write 0A to control address 04
            load      = 1'b1;
        end
        SILENCE: if (ready) begin
            statenext = WAIT;
            datanext  = 16'h0402;  // write 02 to control address 04
            load      = 1'b1;
        end
    endcase
end

endmodule

// quartus_sh --flow compile loopback
// quartus_pgm -m jtag -o "p;loopback.sof@2"
