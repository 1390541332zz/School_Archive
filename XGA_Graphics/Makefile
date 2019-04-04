
all: verilator

verilator: verilator.vlt XGA_Graphics.v vga_driver.v ball_gen.v const_funcs.h altpll_75.v
	verilator -Iverilog --lint-only -Wall verilator.vlt XGA_Graphics.v vga_driver.v ball_gen.v const_funcs.h altpll_75.v
