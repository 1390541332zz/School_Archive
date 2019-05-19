
all: verilator

verilator: verilator.vlt XGA_testpattern.v vga_driver.v
	verilator -Iverilog --lint-only -Wall verilator.vlt XGA_testpattern.v vga_driver.v
