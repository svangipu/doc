set terminal latex
set output 'representativeBasket-gnuplottex-fig1.tex'
set terminal epslatex color
set xrange [-5:5]
unset key
set xlabel "y"
set ylabel "npv"
plot 'exotic_npv.txt' with line, 'standard_npv.txt' with line lt 0
