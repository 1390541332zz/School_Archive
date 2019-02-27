
all: c verilator

c: c/dds.c
	cc -lm -o ./build/dds ./c/dds.c 

verilator: ./verilog/constants.h ./verilog/cordicsine.v ./verilog/ddstop.v
	verilator -Iverilog --lint-only -Wall ./verilog/constants.h ./verilog/cordicsine.v ./verilog/ddstop.v
