set terminal latex
set output 'representativeBasket-gnuplottex-fig2.tex'
set terminal epslatex color
set xrange [-5:5]
unset key
set xlabel "y"
set ylabel "npv"
plot 'hw_cms_npv_match.dat' using 1:2 with line, 'hw_cms_npv_match.dat' using 1:3 with line lt 0
