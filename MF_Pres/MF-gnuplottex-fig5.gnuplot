set terminal latex
set output 'MF-gnuplottex-fig5.tex'
set terminal epslatex color
set xrange [0:0.2]
set yrange [-50:50]
unset key
set xlabel "strike"
set ylabel "density"
plot 'smile.txt' using 1:8 with line, 'smile.txt' using 1:9 with line
