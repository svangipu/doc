set xrange [0:20]
set yrange [*:*]
set format x "%.0f"
set format y "%.0f"
set xlabel "time shift (years)"
set ylabel "NPV (mm EUR)"
set title "Time Shifted Market Value"
set key default
plot "cpi1.dat" using 1:($2/1000000) with lines smooth csplines title "IT0003745541+IT0004243512+10702+10704+10879+10675", "cpi2.dat" using 1:($2/1000000) with lines smooth csplines title "IT0003745541+10702+10704(+10675)"