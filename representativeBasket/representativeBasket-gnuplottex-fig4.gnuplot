set terminal latex
set output 'representativeBasket-gnuplottex-fig4.tex'
set terminal epslatex color
set xrange [-5:5]
unset key
set xlabel "y"
set ylabel "npv"
plot 'mf_cms_npv_match.dat' using 1:2 with line, 'mf_cms_npv_match.dat' using 1:3 with line lt 0
