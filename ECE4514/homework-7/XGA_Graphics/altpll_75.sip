set_global_assignment -entity "altpll_75" -library "lib_altpll_75" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "altpll_75" -library "lib_altpll_75" -name IP_TOOL_VERSION "17.0"
set_global_assignment -entity "altpll_75" -library "lib_altpll_75" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_altpll_75" -name SPD_FILE [file join $::quartus(sip_path) "altpll_75.spd"]

set_global_assignment -library "lib_altpll_75" -name MISC_FILE [file join $::quartus(sip_path) "altpll_75_sim/altpll_75.vo"]
