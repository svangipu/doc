set xrange [0:21]
set yrange [*:*]
set format x "%.0f"
set format y "%.0f"
set xlabel "time shift (years)"
set ylabel "DV01 (EUR)"
set title "Time Shifted DV01 (rates, inflation is opposite)"
set key default
plot "cpi_single.dat" using 1:(2*$7) with lines title "10702+10704", "cpi_single.dat" using 1:8 with lines title "10879", "cpi_single.dat" using 1:9 with lines title "10675", "cpi_single.dat" using 1:10 with lines title "IT0003745541", "cpi_single.dat" using 1:11 with lines title "IT0004243512"
