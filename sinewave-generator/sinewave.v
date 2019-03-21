module sinewave(
    /* verilator lint_off UNUSED */ 
    input         AUD_ADCDAT,
    inout         AUD_ADCLRCK,
    inout         AUD_BCLK,
    output        AUD_DACDAT,
    inout         AUD_DACLRCK,
    output        AUD_XCK,
    input         CLOCK2_50,
    input         CLOCK3_50,
    input         CLOCK4_50,
    input         CLOCK_50,
    output        FPGA_I2C_SCLK,
    inout         FPGA_I2C_SDAT,
    input   [3:0] KEY,
    output  [9:0] LEDR,
    input   [9:0] SW,
    inout  [35:0] GPIO
    /* verilator lint_on UNUSED */
);

localparam
    SIN_INCR = 16'h8000;

// ---- reset ----
wire reset;
assign reset = ~KEY[0];

// ---- heartbeat ----
reg [24:0] 
    counter, 
    counternext;

always @(posedge CLOCK_50)
counter <= (reset) ? 25'h0 : counternext;

always @(*)
counternext = counter + 25'h1;

assign GPIO[1]   = FPGA_I2C_SCLK;
assign GPIO[3]   = FPGA_I2C_SDAT;
assign GPIO[11]  = AUD_ADCDAT;
assign GPIO[13]  = AUD_ADCLRCK;
assign GPIO[15]  = AUD_BCLK;
assign GPIO[17]  = AUD_DACDAT;
assign GPIO[19]  = AUD_DACLRCK;
assign LEDR[8:0] = 9'b0;
assign LEDR[9]   = counter[24];

wire
    clk,
    clk_125,
    data_en,
    audio_en;
wire [15:0]    
    a_data;
    
assign clk = CLOCK_50;
assign clk_125 = counter[1];
assign AUD_XCK = clk_125;


codec_cfg cfg(
    .clk(clk),
    .i2c_sclk(FPGA_I2C_SCLK),
    .i2c_sdat(FPGA_I2C_SDAT),
    .key(KEY),
    .audio_ready(audio_en)
);

audio_gen gen(
    .reset(reset),
    .enable(audio_en),
    .bclk(AUD_BCLK),
    .dac_lr_clk(AUD_DACLRCK),
    .freq(SW[2:0]),
    .volume(SW[4:3]),
    .data_in(a_data),
    .data_ready(data_en),
    .dac_dat(AUD_DACDAT)
);

sin_gen audio(
    .clk(clk),
    .reset(reset),
    .increment(SIN_INCR),
    .update(data_en),
    .q(a_data)
);

endmodule

// quartus_sh --flow compile tonegen
// quartus_pgm -m jtag -o "p;tonegen.sof@2"
