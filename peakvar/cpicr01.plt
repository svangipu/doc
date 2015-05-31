set xrange [0:20]
set yrange [*:*]
set format x "%.0f"
set format y "%.0f"
set xlabel "time shift (years)"
set ylabel "CR01 (EUR)"
set title "Time Shifted CR01"
unset key 
plot "cpi.dat" using 1:4 with lines smooth csplines
