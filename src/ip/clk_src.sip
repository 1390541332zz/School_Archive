set_global_assignment -entity "clk_src" -library "lib_clk_src" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "clk_src" -library "lib_clk_src" -name IP_TOOL_VERSION "17.0"
set_global_assignment -entity "clk_src" -library "lib_clk_src" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_clk_src" -name SPD_FILE [file join $::quartus(sip_path) "clk_src.spd"]

set_global_assignment -library "lib_clk_src" -name MISC_FILE [file join $::quartus(sip_path) "clk_src_sim/clk_src.vo"]
