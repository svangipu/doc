set terminal epslatex color
set output '_region_-gnuplottex-fig2.tex'
unset key
set yrange [0.10:0.30]
plot 'ex2.txt' using 1:2 with lines, 'ex2.txt' using 1:3 with lines
