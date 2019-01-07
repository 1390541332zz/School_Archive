transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03B/P3B_0 {D:/GitHub/ECE3544/Project03B/P3B_0/proc7segdecoder.v}
vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03B/P3B_0 {D:/GitHub/ECE3544/Project03B/P3B_0/project3bTop.v}
vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03B/P3B_0 {D:/GitHub/ECE3544/Project03B/P3B_0/keypressed.v}
vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03B/P3B_0 {D:/GitHub/ECE3544/Project03B/P3B_0/fsm16bit.v}

vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03B/P3B_0 {D:/GitHub/ECE3544/Project03B/P3B_0/tb_fsm16bit.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  tb_fsm16bit

add wave *
view structure
view signals
run 250 ns
