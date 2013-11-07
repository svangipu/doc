set terminal epslatex color
set output '_region_-gnuplottex-fig4.tex'
unset key
plot 'ex4.txt' using 1:2 with lines, 'ex4.txt' using 1:3 with lines
