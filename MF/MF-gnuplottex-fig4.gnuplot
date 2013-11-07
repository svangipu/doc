set terminal latex
set output 'MF-gnuplottex-fig4.tex'
set terminal epslatex color
set xrange [0:0.2]
set yrange [0:1.0]
unset key
set xlabel "strike"
set ylabel "digital call"
plot 'smile.txt' using 1:6 with line, 'smile.txt' using 1:7 with line
