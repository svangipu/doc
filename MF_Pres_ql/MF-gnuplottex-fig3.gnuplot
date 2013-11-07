set terminal latex
set output 'MF-gnuplottex-fig3.tex'
set terminal epslatex color
set xrange [0:0.2]
set yrange [0:0.035]
unset key
set xlabel "strike"
set ylabel "call"
plot 'smile.txt' using 1:4 with line, 'smile.txt' using 1:5 with line
