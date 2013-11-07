set terminal latex
set output 'CallProbabilities-gnuplottex-fig1.tex'
set terminal epslatex color
set xrange [-3:3]
set yrange [-0.5:0.5]
unset key
set grid
set xlabel "z"
set ylabel "undeflated payoff"
plot 'example.txt' using 1:2 with line, 'example.txt' using 1:6 with line
