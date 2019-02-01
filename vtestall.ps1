$start = $args[0]
$end = $args[1]

for ($num=$start; $num -le $end; $num++) {
    cd "./question${num}"
    ../vtest.ps1 ${num}
    cd ..
}
