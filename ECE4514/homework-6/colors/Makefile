
all: verilator

verilator: verilator.vlt XGA.v vga_driver.v
	verilator -Iverilog --lint-only -Wall verilator.vlt XGA.v vga_driver.v
