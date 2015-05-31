set xrange [0:21]
set yrange [*:*]
set format x "%.0f"
set format y "%.0f"
set xlabel "time shift (years)"
set ylabel "NPV (mm EUR)"
set title "Time Shifted Market Value"
set key default
plot "cpi_single.dat" using 1:($2/1000000*2+$5/1000000) with lines title "10702+10704+IT0003745541", "cpi_single.dat" using 1:($4/1000000) with lines title "10675", "cpi_single.dat" using 1:($3/1000000+$6/1000000) with lines title "10879+IT0004243512"