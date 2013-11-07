set terminal latex
set output '_region_-gnuplottex-fig2.tex'
set terminal epslatex color
set xrange [-3:3]
set yrange [-0:10]
unset key
set grid
set xlabel "z"
set ylabel "P(0,T)/P(t,T)"
plot 'example2.txt' using 1:2 with line, 'example2.txt' using 1:6 with line
