set xrange [0:20]
set yrange [*:*]
set format x "%.0f"
set format y "%.0f"
set xlabel "time shift (years)"
set ylabel "DV01 (EUR)"
set title "Time Shifted DV01"
set key default
plot "cpi.dat" using 1:3 with lines title "DV01 (rates)", "cpi.dat" using 1:(-$3) with lines title "DV01 (inflation)"
