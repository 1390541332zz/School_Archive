$num = $args[0]

vlib work
vlog "question${num}tb.v"
vlog "question${num}.v"
vsim -c "question${num}tb" -do "run -all"
