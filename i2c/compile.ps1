vlib work
vlog bitxmit.v
vlog i2cgenerator.v
vlog i2cmasterwrite.v
vlog i2ctb.v
vlog slave/i2cSlave.v
vlog slave/registerInterface.v
vlog slave/serialInterface.v
vsim -c i2ctb -do "run 4000000ns; exit"