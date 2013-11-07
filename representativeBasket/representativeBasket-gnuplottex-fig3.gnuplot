set terminal latex
set output 'representativeBasket-gnuplottex-fig3.tex'
set terminal epslatex color
set xrange [-5:5]
unset key
set xlabel "y"
set ylabel "npv"
plot 'mf_cms_npv_match.dat' using 1:4 with line, 'mf_cms_npv_match.dat' using 1:5 with line lt 0
