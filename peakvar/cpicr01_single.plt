set xrange [0:20]
set yrange [*:*]
set format x "%.0f"
set format y "%.0f"
set xlabel "time shift (years)"
set ylabel "CR01 (EUR)"
set title "Time Shifted CR01"
set key default
plot "cpi_single.dat" using 1:15 with lines title "IT0003745541", "cpi_single.dat" using 1:16 with lines title "IT0004243512" 
