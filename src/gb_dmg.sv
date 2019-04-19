module gb_dmg(
    /* CLOCKS */
    input  uwire       CLOCK_50,

    /* AUDIO */
    input   wire       AUD_ADCDAT,
    inout   wire       AUD_ADCLRCK,
    inout   wire       AUD_DACLRCK,
    inout   wire       AUD_BCLK,
    inout   wire       I2C_SDAT,
    output uwire       I2C_SCLK,
    output uwire       AUD_XCK,
    output uwire       AUD_DACDAT,

    /* VGA */
    output uwire [7:0] VGA_R,
    output uwire [7:0] VGA_G,
    output uwire [7:0] VGA_B,
    output uwire       VGA_CLK,
    output uwire       VGA_BLANK_N,
    output uwire       VGA_SYNC_N,
    output uwire       VGA_HS,
    output uwire       VGA_VS,

    /* PS/2 */
    input  uwire       PS2_DAT,
    output uwire       PS2_CLK,

    /* ONBOARD IO */
    input  uwire [1:0] KEY,
    input  uwire [9:0] SW,
    output uwire [1:0] LEDR
);


endmodule
