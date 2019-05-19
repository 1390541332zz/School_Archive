transcript on
if ![file isdirectory XGA_testpattern_iputf_libs] {
	file mkdir XGA_testpattern_iputf_libs
}

if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

###### Libraries for IPUTF cores 
###### End libraries for IPUTF cores 
###### MIF file copy and HDL compilation commands for IPUTF cores 


vlog "Z:/GitHub/ECE4514/homework-7-jacoblambda/homework6/testpattern/clockgen_sim/clockgen.vo"

vlog -vlog01compat -work work +incdir+Z:/GitHub/ECE4514/homework-7-jacoblambda/homework6/testpattern {Z:/GitHub/ECE4514/homework-7-jacoblambda/homework6/testpattern/vesasync.v}
vlog -vlog01compat -work work +incdir+Z:/GitHub/ECE4514/homework-7-jacoblambda/homework6/testpattern {Z:/GitHub/ECE4514/homework-7-jacoblambda/homework6/testpattern/xga_testpattern.v}

