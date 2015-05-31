set xrange [0:100]
set yrange [*:*]
set xlabel "time to maturity"
set ylabel "DV01 (EUR)"
set title "100mm zero bond DV01"
set key at 50
set format x "%.0f"
set format y "%.0f"
plot -x*10000*exp(-x*0.05) title "5% yield", -x*10000*exp(-x*0.03) title "3% yield"
