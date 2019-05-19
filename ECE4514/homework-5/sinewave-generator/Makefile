
all: verilator

verilator: audio_gen.v bit_stream.h bit_stream.v codec_cfg.v constants.h cordic_sin.v i2c_gen.v sin_gen.v sinewave.v
	verilator -Iverilog --lint-only -Wall audio_gen.v bit_stream.h bit_stream.v codec_cfg.v constants.h cordic_sin.v i2c_gen.v sin_gen.v sinewave.v
