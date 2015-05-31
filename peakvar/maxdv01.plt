set xrange [0.10:10]
set yrange [0:100]
set format x "%.0f%%"
set format y "%.0f"
set xlabel "yield"
set ylabel "peak DV01 time to maturity (years)"
set title "zero bond peak DV01 time to maturity"
unset key
plot 1/(x/100)
