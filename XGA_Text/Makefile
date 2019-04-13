
ball_files  =                                                                 \
    ball_gen.v                                                                \
    ball_render.v

text_files  =                                                                 \
    character_gen.v                                                           \
    dual_port_ram_sync.v                                                      \
    font_rom.v                                                                \
    font_render.v                                                             \
    fill_buf.v                                                                \
    screen_buf.v   

io_files    =                                                                 \
    altpll_75.v                                                               \
    keypressed.v                                                              \
    vga_driver.v                                                              \
    compositer.v


files = ./XGA_Text.v ./const_funcs.h                                          \
        ./io/$(io_files) ./ball/$(ball_files) ./text/$(text_files)

all: verilator

verilator: verilator.vlt $(files) 
    verilator -Iverilog --lint-only -Wall verilator.vlt $(files)
