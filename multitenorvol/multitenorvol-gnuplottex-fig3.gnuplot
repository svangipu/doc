set terminal epslatex color
set output 'multitenorvol-gnuplottex-fig3.tex'
unset key
plot 'ex3.txt' using 1:2 with lines, 'ex3.txt' using 1:3 with lines
