set terminal latex
set output '_region_-gnuplottex-fig1.tex'
set terminal epslatex color
set xrange [-5:5]
unset key
set xlabel "y"
set ylabel "npv"
plot 'exotic_npv.txt' with line, 'standard_npv.txt' with points pointtype 9 pointsize 0.5
