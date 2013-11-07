set terminal latex
set output 'FloaterCurveRisk-gnuplottex-fig2.tex'
set terminal epslatex color
set xrange [0:1.0]
set yrange [-0.5:1.5]
unset key
set xlabel "spread s"
set ylabel "delta"
plot 'spreadex2.txt' using 1:2 with line, 'spreadex2.txt' using 1:3 with line, 'spreadex2.txt' using 1:4 with line, 'spreadex2.txt' using 1:5 with line
