transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03A/P3A_0 {D:/GitHub/ECE3544/Project03A/P3A_0/hc85.v}
vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03A/P3A_0 {D:/GitHub/ECE3544/Project03A/P3A_0/proc7segdecoder.v}
vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03A/P3A_0 {D:/GitHub/ECE3544/Project03A/P3A_0/ECE3544project3a.v}

vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03A/P3A_0 {D:/GitHub/ECE3544/Project03A/P3A_0/tb_project3a.v}
vlog -vlog01compat -work work +incdir+D:/GitHub/ECE3544/Project03A/P3A_0 {D:/GitHub/ECE3544/Project03A/P3A_0/ECE3544project3a.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  tb_project3a

add wave *
view structure
view signals
run -all
