PROJECT = gb_dmg

#foo_files  :=                                                                \
    ./foo/thing0.v                                                            \
    ./foo/thing1.v                                                            \
    ./foo/thing2.v

io_files   :=                                                                 \
    ./io/altpll.v                                                             \
    ./io/altpll.v                                                             \
    ./io/vga_driver.v


files      := $(strip ./${PROJECT}.sv                                         \
                      $(io_files)                                             \
                      $(ball_files)                                           \
                      $(text_files)                                           \
               )

all: verilator

verilator: verilator.vlt $(files) 
	verilator --lint-only -Wall verilator.vlt $(files)


