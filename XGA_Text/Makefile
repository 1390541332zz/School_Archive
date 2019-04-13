
ball_files :=                                                                 \
    ./ball/ball_gen.v                                                         \
    ./ball/ball_render.v                                                       

text_files :=                                                                 \
    ./text/character_gen.v                                                    \
    ./text/dual_port_ram_sync.v                                               \
    ./text/font_rom.v                                                         \
    ./text/font_render.v                                                      \
    ./text/fill_buf.v                                                         \
    ./text/screen_buf.v                                                         

io_files   :=                                                                 \
    ./io/altpll_75.v                                                          \
    ./io/keypressed.v                                                         \
    ./io/vga_driver.v                                                         \
    ./io/compositer.v                                                          


files      := $(strip ./XGA_Text.v ./const_funcs.h                            \
                      $(io_files) $(ball_files) $(text_files)                 \
               )

all: verilator

verilator: verilator.vlt $(files) 
	verilator -Iverilog --lint-only -Wall verilator.vlt $(files)
