set terminal latex
set output 'MF-gnuplottex-fig2.tex'
set terminal epslatex color
set xrange [0:0.2]
set yrange [0:0.9]
unset key
set xlabel "strike"
set ylabel "black lognormal volatility"
plot 'smile.txt' using 1:2 with line, 'smile.txt' using 1:3 with line
